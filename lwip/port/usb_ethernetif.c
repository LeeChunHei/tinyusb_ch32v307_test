/*
 * usb_ethernetif.c
 *
 *  Created on: Sep 7, 2020
 *      Author: Lee Chun Hei
 */
/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "lwip/sys.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "netif/ppp/pppoe.h"
#include "netif/ethernet.h"
#include "usb_ethernetif.h"
#include "tusb.h"

sys_mutex_t usbEthernetInputMutex;
static struct pbuf *received_frame;

/* Define those to better describe your network interface. */
#define IFNAME0 'E'
#define IFNAME1 'X'

#define ETHERNETIF_THREAD_STACKSIZE		2048
StackType_t ethernetif_thread_stack[ETHERNETIF_THREAD_STACKSIZE];
//(3*configMINIMAL_STACK_SIZE/2)
#define ETHERNETIF_THREAD_PRIO			(configMAX_PRIORITIES-3)
StaticTask_t ethernetif_task_handle;

extern const uint8_t tud_network_mac_address[6];

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become available since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t low_level_output(struct netif *netif, struct pbuf *p) {
	(void) netif;

	for (;;) {
		/* if TinyUSB isn't ready, we must signal back to lwip that there is nothing we can do */
		if (!tud_ready())
			return ERR_USE;

		/* if the network driver can accept another packet, we make it happen */
		if (tud_network_can_xmit(p->tot_len)) {
			tud_network_xmit(p, 0 /* unused for this example */);
			return ERR_OK;
		}

		/* transfer execution to TinyUSB in the hopes that it will finish transmitting the prior packet */
//		tud_task();
	}
	  vTaskDelay(pdMS_TO_TICKS(1));
	return ERR_OK;
}

bool tud_network_recv_cb(const uint8_t *src, uint16_t size) {
	/* this shouldn't happen, but if we get another packet before
	 parsing the previous, we must signal our inability to accept it */
	if (received_frame)
		return false;

	if (size) {
		struct pbuf *p = pbuf_alloc(PBUF_RAW, size, PBUF_POOL);

		if (p) {
			/* pbuf_alloc() has already initialized struct; all we need to do is copy the data */
			memcpy(p->payload, src, size);

			/* store away the pointer for service_traffic() to later handle */
			received_frame = p;
		}
	}
//	sys_mutex_unlock(&usbEthernetInputMutex);

	return true;
}

uint16_t tud_network_xmit_cb(uint8_t *dst, void *ref, uint16_t arg) {
	struct pbuf *p = (struct pbuf*) ref;

	(void) arg; /* unused for this example */

	return pbuf_copy_partial(p, dst, p->tot_len, 0);
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_task(struct netif *netif) {
	while (1) {
//		sys_mutex_lock(&usbEthernetInputMutex);
		/* if no packet could be read, silently ignore this */
		if (received_frame != NULL) {
			ethernet_input(received_frame, netif);
			pbuf_free(received_frame);
			received_frame = NULL;
			tud_network_recv_renew();
		}
		sys_check_timeouts();
//		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

void service_traffic(struct netif *netif) {
    if (received_frame != NULL) {
        ethernet_input(received_frame, netif);
        pbuf_free(received_frame);
        received_frame = NULL;
        tud_network_recv_renew();
    }
    sys_check_timeouts();
}

void tud_network_init_cb(void) {
	/* if the network is re-initializing and we have a leftover packet, we must do a cleanup */
	if (received_frame) {
		pbuf_free(received_frame);
		received_frame = NULL;
	}
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t usb_ethernetif_init(struct netif *netif) {
	/* the lwip virtual MAC address must be different from the host's; to ensure this, we toggle the LSbit */
	netif->hwaddr_len = sizeof(tud_network_mac_address);
	memcpy(netif->hwaddr, tud_network_mac_address,
			sizeof(tud_network_mac_address));
	netif->hwaddr[5] ^= 0x01;

	LWIP_ASSERT("netif != NULL", (netif != NULL));
	netif->mtu = CFG_TUD_NET_MTU;
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP
			| NETIF_FLAG_UP;
	netif->state = NULL;
	netif->name[0] = 'E';
	netif->name[1] = 'X';
	netif->linkoutput = low_level_output;
	netif->output = etharp_output;

//	sys_mutex_new(&usbEthernetInputMutex);
//	(void) xTaskCreateStatic(ethernetif_task, "usb ethernetif input",
//	ETHERNETIF_THREAD_STACKSIZE, netif, ETHERNETIF_THREAD_PRIO,
//			ethernetif_thread_stack, &ethernetif_task_handle);

	return ERR_OK;
}

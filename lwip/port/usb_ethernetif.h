/*
 * usb_ethernetif.h
 *
 *  Created on: Sep 7, 2020
 *      Author: Lee Chun Hei
 */

#ifndef PORT_USB_ETHERNETIF_H_
#define PORT_USB_ETHERNETIF_H_

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "netif/ppp/pppoe.h"

/*! @brief init information */
typedef struct ethernetifConfig
{
    uint8_t controllerId;
    void *privateData;
} ethernetifConfig_t;

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
};

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
err_t usb_ethernetif_init(struct netif *netif);

void service_traffic(struct netif *netif);

#endif /* PORT_USB_ETHERNETIF_H_ */

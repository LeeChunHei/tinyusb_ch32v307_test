/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
 task1 and task2 alternate printing
 */

#include "ch32v30x.h"
#include "ch32v30x_rng.h"

#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"

#include "tusb.h"

#include "dhserver.h"
#include "dnserver.h"
#include "httpd.h"

#include "lwip/init.h"
#include "lwip/api.h"
#include "lwip/ip.h"
//#include "lwip/apps/httpd.h"

#include "usb_ethernetif.h"

/* lwip context */
static struct netif netif_data;

const uint8_t tud_network_mac_address[6] = {0x02,0x02,0x84,0x6A,0x96,0x00};

#define INIT_IP4(a,b,c,d) { PP_HTONL(LWIP_MAKEU32(a,b,c,d)) }

static const ip_addr_t ipaddr  = INIT_IP4(192, 168, 7, 1);
static const ip_addr_t netmask = INIT_IP4(255, 255, 255, 0);
static const ip_addr_t gateway = INIT_IP4(0, 0, 0, 0);

/* database IP addresses that can be offered to the host; this must be in RAM to store assigned MAC addresses */
static dhcp_entry_t dhcp_entries[] =
{
  /* mac    ip address        subnet mask        lease time */
  { {0}, INIT_IP4(192, 168, 7, 2), 24 * 60 * 60 },
  { {0}, INIT_IP4(192, 168, 7, 3), 24 * 60 * 60 },
  { {0}, INIT_IP4(192, 168, 7, 4), 24 * 60 * 60 }
};

/* DHCP configuration parameters, leveraging "entries" above */
static const dhcp_config_t dhcp_config =
{
	.router = INIT_IP4(0, 0, 0, 0),            /* router address (if any) */
	.port = 67,                                /* listen port */
	.dns = INIT_IP4(192, 168, 7, 1),           /* dns server (if any) */
	"usb",                                     /* dns suffix */
	TU_ARRAY_SIZE(dhcp_entries),                    /* num entry */
	dhcp_entries                                    /* entries */
};

/* Global define */
#define TASK1_TASK_PRIO     5
#define TASK1_STK_SIZE      256
#define TASK2_TASK_PRIO     5
#define TASK2_STK_SIZE      256
#define USBD_STACK_SIZE    (3*configMINIMAL_STACK_SIZE/2) * (CFG_TUSB_DEBUG ? 2 : 1)
#define CDC_STACK_SZIE      configMINIMAL_STACK_SIZE

/* Global Variable */
TaskHandle_t Task1Task_Handler;
TaskHandle_t Task2Task_Handler;

StackType_t usb_device_stack[USBD_STACK_SIZE];
StaticTask_t usb_device_taskdef;

StackType_t cdc_stack[CDC_STACK_SZIE];
StaticTask_t cdc_taskdef;

void cdc_task(void *params);

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0/1
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,
			GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
					| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void board_init(void) {

	/* Disable interrupts during init */
	__disable_irq();

	RCC_USBCLK48MConfig(RCC_USBCLK48MCLKSource_USBPHY);
	RCC_USBHSPLLCLKConfig(RCC_HSBHSPLLCLKSource_HSE);
	RCC_USBHSConfig(RCC_USBPLL_Div2);
	RCC_USBHSPLLCKREFCLKConfig(RCC_USBHSPLLCKREFCLK_4M);
	RCC_USBHSPHYPLLALIVEcmd(ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_USBHS, ENABLE);

	/* Enable interrupts globally */
	__enable_irq();

//	vTaskDelay(pdMS_TO_TICKS(2));
}

/* handle any DNS requests from dns-server */
bool dns_query_proc(const char *name, ip4_addr_t *addr)
{
  if (0 == strcmp(name, "tiny.usb"))
  {
    *addr = ipaddr;
    return true;
  }
  return false;
}

void LWIPStackInit(){
//	  struct netif *netif = &netif_data;

    lwip_init();

    netif_add(&netif_data, &ipaddr, &netmask, &gateway, NULL, usb_ethernetif_init, ip_input);
    netif_set_default(&netif_data);
//    netif_set_up(&netif_data);
    while (!netif_is_up(&netif_data));
    while (dhserv_init(&dhcp_config) != ERR_OK);
    while (dnserv_init(IP_ADDR_ANY, 53, dns_query_proc) != ERR_OK);
//    httpd_init();
}



/*********************************************************************
 * @fn      task1_task
 *
 * @brief   task1 program.
 *
 * @param  *pvParameters - Parameters point of task1
 *
 * @return  none
 */
void task1_task(void *pvParameters) {
	while (1) {
		GPIO_SetBits(GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		vTaskDelay(pdMS_TO_TICKS(250));
		GPIO_ResetBits(GPIOD,
				GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

/*********************************************************************
 * @fn      task2_task
 *
 * @brief   task2 program.
 *
 * @param  *pvParameters - Parameters point of task2
 *
 * @return  none
 */
void task2_task(void *pvParameters) {
	while (1) {
		GPIO_SetBits(GPIOD, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		vTaskDelay(pdMS_TO_TICKS(500));
		GPIO_ResetBits(GPIOD,
				GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void usb_device_task(void *param) {
	(void) param;

	// init device stack on configured roothub port
	// This should be called after scheduler/kernel is started.
	// Otherwise it could cause kernel issue since USB IRQ handler does use RTOS queue API.
	tud_init(BOARD_TUD_RHPORT);

	// RTOS forever loop
	while (1) {
		// put this thread to waiting state until there is new events
		tud_task();
		service_traffic(&netif_data);

		// following code only run if tud_task() process at least 1 event
//		tud_cdc_write_flush();
	}
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {

//	uint8_t user_byte = FLASH_GetUserOptionByte() & 0xff;
//	user_byte &= ~(0xc0);
//	FLASH_Unlock();
//	FLASH_ProgramOptionByteData(0x1ffff802, user_byte);
//	FLASH_Lock();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n", SystemCoreClock);
	printf("FreeRTOS Kernel Version:%s\r\n", tskKERNEL_VERSION_NUMBER);

	GPIO_Toggle_INIT();
	/* create two task */
	xTaskCreate((TaskFunction_t) task2_task, (const char*) "task2",
			(uint16_t) TASK2_STK_SIZE, (void*) NULL,
			(UBaseType_t) TASK2_TASK_PRIO, (TaskHandle_t*) &Task2Task_Handler);

	xTaskCreate((TaskFunction_t) task1_task, (const char*) "task1",
			(uint16_t) TASK1_STK_SIZE, (void*) NULL,
			(UBaseType_t) TASK1_TASK_PRIO, (TaskHandle_t*) &Task1Task_Handler);

	board_init();

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);
    RNG_Cmd(ENABLE);

	// Create a task for tinyusb device stack
	xTaskCreateStatic(usb_device_task, "usbd", USBD_STACK_SIZE, NULL,
			configMAX_PRIORITIES - 1, usb_device_stack, &usb_device_taskdef);

    LWIPStackInit();
//	// Create CDC task
//	xTaskCreateStatic(cdc_task, "cdc", CDC_STACK_SZIE, NULL,
//			configMAX_PRIORITIES - 2, cdc_stack, &cdc_taskdef);



	vTaskStartScheduler();

	while (1) {
		printf("shouldn't run at here!!\n");
	}
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void) {
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
	(void) remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void *params) {
	(void) params;

	// RTOS forever loop
	while (1) {
		// connected() check for DTR bit
		// Most but not all terminal client set this when making connection
		// if ( tud_cdc_connected() )
		{
			// There are data available
			while (tud_cdc_available()) {
				uint8_t buf[64];

				// read and echo back
				uint32_t count = tud_cdc_read(buf, sizeof(buf));
				(void) count;

				// Echo back
				// Note: Skip echo by commenting out write() and write_flush()
				// for throughput test e.g
				//    $ dd if=/dev/zero of=/dev/ttyACM0 count=10000
				tud_cdc_write(buf, count);
			}

			tud_cdc_write_flush();
		}

		// For ESP32-Sx this delay is essential to allow idle how to run and reset watchdog
		vTaskDelay(1);
	}
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts) {
	(void) itf;
	(void) rts;

	// TODO set some indicator
	if (dtr) {
		// Terminal connected
	} else {
		// Terminal disconnected
	}
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) {
	(void) itf;
}

//--------------------------------------------------------------------+
// Forward USB interrupt events to TinyUSB IRQ Handler
//--------------------------------------------------------------------+

void USBHS_IRQHandler (void) __attribute__((naked));
void USBHS_IRQHandler (void)
{
  __asm volatile ("call USBHS_IRQHandler_impl; mret");
}

__attribute__ ((used)) void USBHS_IRQHandler_impl (void)
{
  tud_int_handler(0);
}


#include "ch32v30x_rng.h"

/*********************************************************************
 * @fn      CH30x_RNG_GENERATE
 *
 * @brief   CH30x_RNG_GENERATE api function for lwip.
 *
 * @param   None.
 *
 * @return  None.
 */
uint32_t CH30x_RNG_GENERATE()
{
    while(1)
    {
        if(RNG_GetFlagStatus(RNG_FLAG_DRDY) == SET)
        {
            break;
        }
        if(RNG_GetFlagStatus(RNG_FLAG_CECS) == SET)
        {
            /* Ê±ÖÓ´íÎó */
            RNG_ClearFlag(RNG_FLAG_CECS);
            Delay_Us(100);
        }
        if(RNG_GetFlagStatus(RNG_FLAG_SECS) == SET)
        {
            /* ÖÖ×Ó´íÎó */
            RNG_ClearFlag(RNG_FLAG_SECS);
            RNG_Cmd(DISABLE);
            Delay_Us(100);
            RNG_Cmd(ENABLE);
            Delay_Us(100);
        }
    }
    return RNG_GetRandomNumber();
}

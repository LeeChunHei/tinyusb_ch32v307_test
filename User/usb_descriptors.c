/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "tusb.h"

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]       NET | VENDOR | MIDI | HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
#define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | \
                           _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) | _PID_MAP(ECM_RNDIS, 5) | _PID_MAP(NCM, 5) )

// String Descriptor Index
enum
{
  STRID_LANGID = 0,
  STRID_MANUFACTURER,
  STRID_PRODUCT,
  STRID_SERIAL,
  STRID_INTERFACE,
  STRID_MAC
};

enum
{
  ITF_NUM_CDC = 0,
  ITF_NUM_CDC_DATA,
  ITF_NUM_TOTAL
};

enum
{
#if CFG_TUD_ECM_RNDIS
  CONFIG_ID_RNDIS = 0,
  CONFIG_ID_ECM   = 1,
#else
  CONFIG_ID_NCM   = 0,
#endif
  CONFIG_ID_COUNT
};

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,

    // Use Interface Association Descriptor (IAD) device class
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,

    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = 0xCafe,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0101,

    .iManufacturer      = STRID_MANUFACTURER,
    .iProduct           = STRID_PRODUCT,
    .iSerialNumber      = STRID_SERIAL,

    .bNumConfigurations = CONFIG_ID_COUNT // multiple configurations
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const * tud_descriptor_device_cb(void)
{
  return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+
#define MAIN_CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_RNDIS_DESC_LEN)
#define ALT_CONFIG_TOTAL_LEN     (TUD_CONFIG_DESC_LEN + TUD_CDC_ECM_DESC_LEN)
#define NCM_CONFIG_TOTAL_LEN     (TUD_CONFIG_DESC_LEN + TUD_CDC_NCM_DESC_LEN)

#if CFG_TUSB_MCU == OPT_MCU_LPC175X_6X || CFG_TUSB_MCU == OPT_MCU_LPC177X_8X || CFG_TUSB_MCU == OPT_MCU_LPC40XX
  // LPC 17xx and 40xx endpoint type (bulk/interrupt/iso) are fixed by its number
  // 0 control, 1 In, 2 Bulk, 3 Iso, 4 In etc ...
  #define EPNUM_NET_NOTIF   0x81
  #define EPNUM_NET_OUT     0x02
  #define EPNUM_NET_IN      0x82

#elif CFG_TUSB_MCU == OPT_MCU_SAMG  || CFG_TUSB_MCU ==  OPT_MCU_SAMX7X
  // SAMG & SAME70 don't support a same endpoint number with different direction IN and OUT
  //    e.g EP1 OUT & EP1 IN cannot exist together
  #define EPNUM_NET_NOTIF   0x81
  #define EPNUM_NET_OUT     0x02
  #define EPNUM_NET_IN      0x83

#else
  #define EPNUM_NET_NOTIF   0x81
  #define EPNUM_NET_OUT     0x01
  #define EPNUM_NET_IN      0x82
#endif

#if CFG_TUD_ECM_RNDIS

static uint8_t const rndis_configuration[] =
{
  // Config number (index+1), interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(CONFIG_ID_RNDIS+1, ITF_NUM_TOTAL, 0, MAIN_CONFIG_TOTAL_LEN, 0, 100),

  // Interface number, string index, EP notification address and size, EP data address (out, in) and size.
  TUD_RNDIS_DESCRIPTOR(ITF_NUM_CDC, STRID_INTERFACE, EPNUM_NET_NOTIF, 8, EPNUM_NET_OUT, EPNUM_NET_IN, CFG_TUD_NET_ENDPOINT_SIZE),
};

static uint8_t const ecm_configuration[] =
{
  // Config number (index+1), interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(CONFIG_ID_ECM+1, ITF_NUM_TOTAL, 0, ALT_CONFIG_TOTAL_LEN, 0, 100),

  // Interface number, description string index, MAC address string index, EP notification address and size, EP data address (out, in), and size, max segment size.
  TUD_CDC_ECM_DESCRIPTOR(ITF_NUM_CDC, STRID_INTERFACE, STRID_MAC, EPNUM_NET_NOTIF, 64, EPNUM_NET_OUT, EPNUM_NET_IN, CFG_TUD_NET_ENDPOINT_SIZE, CFG_TUD_NET_MTU),
};

#else

static uint8_t const ncm_configuration[] =
{
  // Config number (index+1), interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(CONFIG_ID_NCM+1, ITF_NUM_TOTAL, 0, NCM_CONFIG_TOTAL_LEN, 0, 100),

  // Interface number, description string index, MAC address string index, EP notification address and size, EP data address (out, in), and size, max segment size.
  TUD_CDC_NCM_DESCRIPTOR(ITF_NUM_CDC, STRID_INTERFACE, STRID_MAC, EPNUM_NET_NOTIF, 64, EPNUM_NET_OUT, EPNUM_NET_IN, CFG_TUD_NET_ENDPOINT_SIZE, CFG_TUD_NET_MTU),
};

#endif

// Configuration array: RNDIS and CDC-ECM
// - Windows only works with RNDIS
// - MacOS only works with CDC-ECM
// - Linux will work on both
static uint8_t const * const configuration_arr[2] =
{
#if CFG_TUD_ECM_RNDIS
  [CONFIG_ID_RNDIS] = rndis_configuration,
  [CONFIG_ID_ECM  ] = ecm_configuration
#else
  [CONFIG_ID_NCM  ] = ncm_configuration
#endif
};

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
  return (index < CONFIG_ID_COUNT) ? configuration_arr[index] : NULL;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
static char const* string_desc_arr [] =
{
  [STRID_LANGID]       = (const char[]) { 0x09, 0x04 }, // supported language is English (0x0409)
  [STRID_MANUFACTURER] = "TinyUSB",                     // Manufacturer
  [STRID_PRODUCT]      = "TinyUSB Device",              // Product
  [STRID_SERIAL]       = "123456",                      // Serial
  [STRID_INTERFACE]    = "TinyUSB Network Interface"    // Interface Description

  // STRID_MAC index is handled separately
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
  (void) langid;

  unsigned int chr_count = 0;

  if (STRID_LANGID == index)
  {
    memcpy(&_desc_str[1], string_desc_arr[STRID_LANGID], 2);
    chr_count = 1;
  }
  else if (STRID_MAC == index)
  {
    // Convert MAC address into UTF-16

    for (unsigned i=0; i<sizeof(tud_network_mac_address); i++)
    {
      _desc_str[1+chr_count++] = "0123456789ABCDEF"[(tud_network_mac_address[i] >> 4) & 0xf];
      _desc_str[1+chr_count++] = "0123456789ABCDEF"[(tud_network_mac_address[i] >> 0) & 0xf];
    }
  }
  else
  {
    // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

    if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;

    const char* str = string_desc_arr[index];

    // Cap at max char
    chr_count = (uint8_t) strlen(str);
    if ( chr_count > (TU_ARRAY_SIZE(_desc_str) - 1)) chr_count = TU_ARRAY_SIZE(_desc_str) - 1;

    // Convert ASCII string into UTF-16
    for (unsigned int i=0; i<chr_count; i++)
    {
      _desc_str[1+i] = str[i];
    }
  }

  // first byte is length (including header), second byte is string type
  _desc_str[0] = (uint16_t) ((TUSB_DESC_STRING << 8 ) | (2*chr_count + 2));

  return _desc_str;
}



///*
// * The MIT License (MIT)
// *
// * Copyright (c) 2019 Ha Thach (tinyusb.org)
// *
// * Permission is hereby granted, free of charge, to any person obtaining a copy
// * of this software and associated documentation files (the "Software"), to deal
// * in the Software without restriction, including without limitation the rights
// * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// * copies of the Software, and to permit persons to whom the Software is
// * furnished to do so, subject to the following conditions:
// *
// * The above copyright notice and this permission notice shall be included in
// * all copies or substantial portions of the Software.
// *
// * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// * THE SOFTWARE.
// *
// */
//
//#include "tusb.h"
//
///* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
// * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
// *
// * Auto ProductID layout's Bitmap:
// *   [MSB]         HID | MSC | CDC          [LSB]
// */
//#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
//#define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | \
//                           _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) )
//
//#define USB_VID   0xCafe
//#define USB_BCD   0x0200
//
////--------------------------------------------------------------------+
//// Device Descriptors
////--------------------------------------------------------------------+
//tusb_desc_device_t const desc_device =
//{
//    .bLength            = sizeof(tusb_desc_device_t),
//    .bDescriptorType    = TUSB_DESC_DEVICE,
//    .bcdUSB             = USB_BCD,
//
//    // Use Interface Association Descriptor (IAD) for CDC
//    // As required by USB Specs IAD's subclass must be common class (2) and protocol must be IAD (1)
//    .bDeviceClass       = TUSB_CLASS_MISC,
//    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
//    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
//
//    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
//
//    .idVendor           = USB_VID,
//    .idProduct          = USB_PID,
//    .bcdDevice          = 0x0100,
//
//    .iManufacturer      = 0x01,
//    .iProduct           = 0x02,
//    .iSerialNumber      = 0x03,
//
//    .bNumConfigurations = 0x01
//};
//
//// Invoked when received GET DEVICE DESCRIPTOR
//// Application return pointer to descriptor
//uint8_t const * tud_descriptor_device_cb(void)
//{
//  return (uint8_t const *) &desc_device;
//}
//
////--------------------------------------------------------------------+
//// Configuration Descriptor
////--------------------------------------------------------------------+
//
//enum
//{
//  ITF_NUM_CDC = 0,
//  ITF_NUM_CDC_DATA,
//  ITF_NUM_MSC,
//  ITF_NUM_TOTAL
//};
//
//#if CFG_TUSB_MCU == OPT_MCU_LPC175X_6X || CFG_TUSB_MCU == OPT_MCU_LPC177X_8X || CFG_TUSB_MCU == OPT_MCU_LPC40XX
//  // LPC 17xx and 40xx endpoint type (bulk/interrupt/iso) are fixed by its number
//  // 0 control, 1 In, 2 Bulk, 3 Iso, 4 In, 5 Bulk etc ...
//  #define EPNUM_CDC_NOTIF   0x81
//  #define EPNUM_CDC_OUT     0x02
//  #define EPNUM_CDC_IN      0x82
//
//  #define EPNUM_MSC_OUT     0x05
//  #define EPNUM_MSC_IN      0x85
//
//#elif CFG_TUSB_MCU == OPT_MCU_SAMG
//  // SAMG doesn't support a same endpoint number with different direction IN and OUT
//  //    e.g EP1 OUT & EP1 IN cannot exist together
//  #define EPNUM_CDC_NOTIF   0x81
//  #define EPNUM_CDC_OUT     0x02
//  #define EPNUM_CDC_IN      0x83
//
//  #define EPNUM_MSC_OUT     0x04
//  #define EPNUM_MSC_IN      0x85
//
//#else
//  #define EPNUM_CDC_NOTIF   0x81
//  #define EPNUM_CDC_OUT     0x02
//  #define EPNUM_CDC_IN      0x82
//
//  #define EPNUM_MSC_OUT     0x03
//  #define EPNUM_MSC_IN      0x83
//
//#endif
//
//#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN + TUD_MSC_DESC_LEN)
//
//uint8_t const desc_fs_configuration[] =
//{
//  // Config number, interface count, string index, total length, attribute, power in mA
//  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),
//
//  // Interface number, string index, EP notification address and size, EP data address (out, in) and size.
//  TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
//
//  // Interface number, string index, EP Out & EP In address, EP size
//  TUD_MSC_DESCRIPTOR(ITF_NUM_MSC, 5, EPNUM_MSC_OUT, EPNUM_MSC_IN, 64),
//};
//
//#if TUD_OPT_HIGH_SPEED
//// Per USB specs: high speed capable device must report device_qualifier and other_speed_configuration
//
//// high speed configuration
//uint8_t const desc_hs_configuration[] =
//{
//  // Config number, interface count, string index, total length, attribute, power in mA
//  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),
//
//  // Interface number, string index, EP notification address and size, EP data address (out, in) and size.
//  TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 512),
//
//  // Interface number, string index, EP Out & EP In address, EP size
//  TUD_MSC_DESCRIPTOR(ITF_NUM_MSC, 5, EPNUM_MSC_OUT, EPNUM_MSC_IN, 512),
//};
//
//// other speed configuration
//uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];
//
//// device qualifier is mostly similar to device descriptor since we don't change configuration based on speed
//tusb_desc_device_qualifier_t const desc_device_qualifier =
//{
//  .bLength            = sizeof(tusb_desc_device_qualifier_t),
//  .bDescriptorType    = TUSB_DESC_DEVICE_QUALIFIER,
//  .bcdUSB             = USB_BCD,
//
//  .bDeviceClass       = TUSB_CLASS_MISC,
//  .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
//  .bDeviceProtocol    = MISC_PROTOCOL_IAD,
//
//  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
//  .bNumConfigurations = 0x01,
//  .bReserved          = 0x00
//};
//
//// Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
//// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete.
//// device_qualifier descriptor describes information about a high-speed capable device that would
//// change if the device were operating at the other speed. If not highspeed capable stall this request.
//uint8_t const* tud_descriptor_device_qualifier_cb(void)
//{
//  return (uint8_t const*) &desc_device_qualifier;
//}
//
//// Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
//// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
//// Configuration descriptor in the other speed e.g if high speed then this is for full speed and vice versa
//uint8_t const* tud_descriptor_other_speed_configuration_cb(uint8_t index)
//{
//  (void) index; // for multiple configurations
//
//  // if link speed is high return fullspeed config, and vice versa
//  // Note: the descriptor type is OHER_SPEED_CONFIG instead of CONFIG
//  memcpy(desc_other_speed_config,
//         (tud_speed_get() == TUSB_SPEED_HIGH) ? desc_fs_configuration : desc_hs_configuration,
//         CONFIG_TOTAL_LEN);
//
//  desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;
//
//  return desc_other_speed_config;
//}
//
//#endif // highspeed
//
//// Invoked when received GET CONFIGURATION DESCRIPTOR
//// Application return pointer to descriptor
//// Descriptor contents must exist long enough for transfer to complete
//uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
//{
//  (void) index; // for multiple configurations
//
//#if TUD_OPT_HIGH_SPEED
//  // Although we are highspeed, host may be fullspeed.
//  return (tud_speed_get() == TUSB_SPEED_HIGH) ?  desc_hs_configuration : desc_fs_configuration;
//#else
//  return desc_fs_configuration;
//#endif
//}
//
////--------------------------------------------------------------------+
//// String Descriptors
////--------------------------------------------------------------------+
//
//// array of pointer to string descriptors
//char const* string_desc_arr [] =
//{
//  (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
//  "TinyUSB",                     // 1: Manufacturer
//  "TinyUSB Device",              // 2: Product
//  "123456789012",                // 3: Serials, should use chip ID
//  "TinyUSB CDC",                 // 4: CDC Interface
//  "TinyUSB MSC",                 // 5: MSC Interface
//};
//
//static uint16_t _desc_str[32];
//
//// Invoked when received GET STRING DESCRIPTOR request
//// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
//uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
//{
//  (void) langid;
//
//  uint8_t chr_count;
//
//  if ( index == 0)
//  {
//    memcpy(&_desc_str[1], string_desc_arr[0], 2);
//    chr_count = 1;
//  }else
//  {
//    // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
//    // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors
//
//    if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;
//
//    const char* str = string_desc_arr[index];
//
//    // Cap at max char
//    chr_count = (uint8_t) strlen(str);
//    if ( chr_count > 31 ) chr_count = 31;
//
//    // Convert ASCII string into UTF-16
//    for(uint8_t i=0; i<chr_count; i++)
//    {
//      _desc_str[1+i] = str[i];
//    }
//  }
//
//  // first byte is length (including header), second byte is string type
//  _desc_str[0] = (uint16_t) ((TUSB_DESC_STRING << 8 ) | (2*chr_count + 2));
//
//  return _desc_str;
//}

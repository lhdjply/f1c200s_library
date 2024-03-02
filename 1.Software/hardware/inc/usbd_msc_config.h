#ifndef USBD_MSC_CONFIG_H
#define USBD_MSC_CONFIG_H

#include <rtthread.h>
#include <rthw.h>
#include "interrupt.h"
#include "stdbool.h"
#include "usb_phy.h"
#include "usbd_core.h"
#include "usbd_msc.h"
#include "sdcard.h"

#define USBD_BASE 0x01c13000

#define MSC_IN_EP 0x81
#define MSC_OUT_EP 0x02

#define USBD_VID 0x8136
#define USBD_PID 0xd497
#define USBD_MAX_POWER 100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + MSC_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
  #define MSC_MAX_MPS 512
#else
  #define MSC_MAX_MPS 64
#endif

extern void usbd_msc_init(void);

#endif

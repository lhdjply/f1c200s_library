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

extern void usbd_msc_init(void);

#endif

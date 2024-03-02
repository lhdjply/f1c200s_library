#ifndef USBH_MSC_CONFIG_H
#define USBH_MSC_CONFIG_H

#include <rtthread.h>
#include <rthw.h>
#include "interrupt.h"
#include "stdbool.h"
#include "usb_phy.h"
#include "usbh_core.h"
#include "usbh_msc.h"

#define USBH_BASE 0x01c13000

extern volatile bool mounted_flag;

#endif

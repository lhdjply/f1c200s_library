#include "usbh_msc_config.h"

volatile bool mounted_flag;
USB_NOCACHE_RAM_SECTION struct usbh_msc * active_msc_class;

extern void USBH_IRQHandler();

void usb_hc_low_level_init(void)
{
  usb_phy_open_clock();
  USBC_PhyConfig();
  USBC_ConfigFIFO_Base();
  USBC_EnableDpDmPullUp();
  USBC_EnableIdPullUp();
  USBC_ForceId(USBC_ID_TYPE_HOST);
  USBC_ForceVbusValid(USBC_VBUS_TYPE_HIGH);

  rt_hw_interrupt_install(USB_OTG_INTERRUPT, (rt_isr_handler_t)USBH_IRQHandler, NULL, "musb_irq");
  rt_hw_interrupt_umask(USB_OTG_INTERRUPT);
}

void usb_disk_set_active_msc_class(void * ptr)
{
  active_msc_class = (struct usbh_msc *)ptr;
}

void usbh_msc_run(struct usbh_msc * msc_class)
{
  if(msc_class != NULL)
  {
    usb_disk_set_active_msc_class((void *)msc_class);
    mounted_flag = true;
  }
}

void usbh_msc_stop(struct usbh_msc * msc_class)
{
  mounted_flag = false;
}

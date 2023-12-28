#include "usbd_msc_config.h"

extern void USBD_IRQHandler();

struct usbd_interface intf0;
extern SD_CardInfo SDCardInfo;

#define MSC_IN_EP  0x81
#define MSC_OUT_EP 0x02

#define USBD_VID           0x8136
#define USBD_PID           0xd497
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + MSC_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
  #define MSC_MAX_MPS 512
#else
  #define MSC_MAX_MPS 64
#endif

void usb_dc_low_level_init(void)
{
  usb_phy_open_clock();
  USBC_PhyConfig();
  USBC_ConfigFIFO_Base();
  USBC_EnableDpDmPullUp();
  USBC_EnableIdPullUp();
  USBC_ForceId(USBC_ID_TYPE_DEVICE);
  USBC_ForceVbusValid(USBC_VBUS_TYPE_HIGH);

  rt_hw_interrupt_install(USB_OTG_INTERRUPT, (rt_isr_handler_t)USBD_IRQHandler, NULL, "musb_irq");
  rt_hw_interrupt_umask(USB_OTG_INTERRUPT);
}

const uint8_t msc_storage_descriptor[] =
{
  USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0200, 0x01),
  USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
  MSC_DESCRIPTOR_INIT(0x00, MSC_OUT_EP, MSC_IN_EP, MSC_MAX_MPS, 0x02),
  ///////////////////////////////////////
  /// string0 descriptor
  ///////////////////////////////////////
  USB_LANGID_INIT(USBD_LANGID_STRING),
  ///////////////////////////////////////
  /// string1 descriptor
  ///////////////////////////////////////
  0x14,                       /* bLength */
  USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
  'C', 0x00,                  /* wcChar0 */
  'h', 0x00,                  /* wcChar1 */
  'e', 0x00,                  /* wcChar2 */
  'r', 0x00,                  /* wcChar3 */
  'r', 0x00,                  /* wcChar4 */
  'y', 0x00,                  /* wcChar5 */
  'U', 0x00,                  /* wcChar6 */
  'S', 0x00,                  /* wcChar7 */
  'B', 0x00,                  /* wcChar8 */
  ///////////////////////////////////////
  /// string2 descriptor
  ///////////////////////////////////////
  0x26,                       /* bLength */
  USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
  'C', 0x00,                  /* wcChar0 */
  'h', 0x00,                  /* wcChar1 */
  'e', 0x00,                  /* wcChar2 */
  'r', 0x00,                  /* wcChar3 */
  'r', 0x00,                  /* wcChar4 */
  'y', 0x00,                  /* wcChar5 */
  'U', 0x00,                  /* wcChar6 */
  'S', 0x00,                  /* wcChar7 */
  'B', 0x00,                  /* wcChar8 */
  ' ', 0x00,                  /* wcChar9 */
  'M', 0x00,                  /* wcChar10 */
  'S', 0x00,                  /* wcChar11 */
  'C', 0x00,                  /* wcChar12 */
  ' ', 0x00,                  /* wcChar13 */
  'D', 0x00,                  /* wcChar14 */
  'E', 0x00,                  /* wcChar15 */
  'M', 0x00,                  /* wcChar16 */
  'O', 0x00,                  /* wcChar17 */
  ///////////////////////////////////////
  /// string3 descriptor
  ///////////////////////////////////////
  0x16,                       /* bLength */
  USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
  '2', 0x00,                  /* wcChar0 */
  '0', 0x00,                  /* wcChar1 */
  '2', 0x00,                  /* wcChar2 */
  '3', 0x00,                  /* wcChar3 */
  '1', 0x00,                  /* wcChar4 */
  '2', 0x00,                  /* wcChar5 */
  '3', 0x00,                  /* wcChar6 */
  '4', 0x00,                  /* wcChar7 */
  '5', 0x00,                  /* wcChar8 */
  '6', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
  ///////////////////////////////////////
  /// device qualifier descriptor
  ///////////////////////////////////////
  0x0a,
  USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
#endif
  0x00
};

void usbd_event_handler(uint8_t event)
{
  switch(event)
  {
    case USBD_EVENT_RESET:
      break;
    case USBD_EVENT_CONNECTED:
      break;
    case USBD_EVENT_DISCONNECTED:
      break;
    case USBD_EVENT_RESUME:
      break;
    case USBD_EVENT_SUSPEND:
      break;
    case USBD_EVENT_CONFIGURED:
      break;
    case USBD_EVENT_SET_REMOTE_WAKEUP:
      break;
    case USBD_EVENT_CLR_REMOTE_WAKEUP:
      break;

    default:
      break;
  }
}

void usbd_msc_get_cap(uint8_t lun, uint32_t * block_num, uint16_t * block_size)
{
  *block_size = 512;
  *block_num = SDCardInfo.CardCapacity / 512;
}

int usbd_msc_sector_read(uint32_t sector, uint8_t * buffer, uint32_t length)
{
  SD_ReadDisk(SDIO0, buffer, sector, length / 512);
  return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t * buffer, uint32_t length)
{
  SD_WriteDisk(SDIO0, buffer, sector, length / 512);
  return 0;
}

void usbd_msc_init(void)
{
  SD_Init(SDIO0);

  usbd_desc_register(msc_storage_descriptor);
  usbd_add_interface(usbd_msc_init_intf(&intf0, MSC_OUT_EP, MSC_IN_EP));

  usbd_initialize();
}

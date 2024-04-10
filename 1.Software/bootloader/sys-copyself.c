#include <stdint.h>
#include <string.h>

extern unsigned char __image_start;
extern unsigned char __image_end;
extern void return_to_fel(void);
extern void sys_mmu_init(void);

extern void sys_spi_flash_init(void);
extern void sys_spi_flash_exit(void);
extern uint16_t sys_spinor_read_id(void);
extern uint16_t sys_spinand_read_id(void);
extern void sys_spinor_read(int addr, void * buf, int count);
extern void sys_spinand_read(int addr, void * buf, int count);

enum
{
  BOOT_DEVICE_FEL = 0,
  BOOT_DEVICE_SPINOR = 1,
  BOOT_DEVICE_SPINAND = 2,
  BOOT_DEVICE_MMC = 3,
};

static uint8_t get_boot_device(void)
{
  uint32_t * t = (void *)0x00000058;
  uint32_t value = 1;
  uint16_t read_id = 0;
  if(memcmp(t, &value, 4) == 0)
  {
    return BOOT_DEVICE_FEL;
  }
  else
  {
    sys_spi_flash_init();
    read_id = sys_spinor_read_id();
    if(read_id != 0x0000 && read_id != 0xffff)
    {
      sys_spi_flash_exit();
      return BOOT_DEVICE_SPINOR;
    }

    read_id = sys_spinand_read_id();
    if(read_id != 0x0000 && read_id != 0xffff)
    {
      sys_spi_flash_exit();
      return BOOT_DEVICE_SPINAND;
    }
    sys_spi_flash_exit();
  }
  return BOOT_DEVICE_FEL;
}

void sys_copyself(void)
{
  int d = get_boot_device();
  uint32_t size;
  if(d == BOOT_DEVICE_FEL)
  {
    // Boot to FEL mode
    return_to_fel();
  }
  else if(d == BOOT_DEVICE_SPINOR)
  {
    // Boot to SPI mode
    sys_mmu_init();
    size = (uint32_t)(&__image_end) - (uint32_t)(&__image_start);

    sys_spi_flash_init();
    sys_spinor_read(0, (void *)&__image_start, size);
    sys_spi_flash_exit();
  }
  else if(d == BOOT_DEVICE_SPINAND)
  {
    // Boot to SPI mode
    sys_mmu_init();
    size = (uint32_t)(&__image_end) - (uint32_t)(&__image_start);

    sys_spi_flash_init();
    sys_spinand_read(0x40000, (void *)&__image_start, size);
    sys_spi_flash_exit();
  }
}

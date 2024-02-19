#include <stdint.h>
#include <string.h>

extern unsigned char __image_start;
extern unsigned char __image_end;
extern void return_to_fel(void);
extern void sys_mmu_init(void);
extern void sys_spi_flash_init(void);
extern void sys_spi_flash_exit(void);
extern void sys_spi_flash_read(int addr, void * buf, int count);

enum
{
  BOOT_DEVICE_FEL = 0,
  BOOT_DEVICE_SPI = 1,
  BOOT_DEVICE_MMC = 2,
};

static int get_boot_device(void)
{
  uint32_t * t = (void *)0x00000058;
  uint32_t value = 1;
  if(memcmp(t, &value, 4) == 0)
  {
    return BOOT_DEVICE_FEL;
  }
  return BOOT_DEVICE_SPI;
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
  else if(d == BOOT_DEVICE_SPI)
  {
    // Boot to SPI mode
    sys_mmu_init();
    sys_spi_flash_init();
    size = (uint32_t)(&__image_end) - (uint32_t)(&__image_start);
    sys_spi_flash_read(0, (void *)&__image_start, size);
    sys_spi_flash_exit();
  }
}

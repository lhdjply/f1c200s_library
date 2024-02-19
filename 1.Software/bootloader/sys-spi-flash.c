#include <stdint.h>
#include <string.h>
#include <f1cx00s.h>

void sys_spi_flash_init(void)
{
  uint32_t val;
  uint8_t i;

  /* Config GPIOC0, GPIOC1, GPIOC2 and GPIOC3 */
  for(i = 0; i < 4; i++)
  {
    val = GPIOC->CFG0;
    val &= ~(0xf << ((i & 0x7) << 2));
    val |= ((0x2 & 0x7) << ((i & 0x7) << 2));
    GPIOC->CFG0 = val;
  }

  /* Deassert spi0 reset */
  CCU->BUS_SOFT_RST0 |= (1 << 20);

  /* Open the spi0 bus gate */
  CCU->BUS_CLK_GATING0 |= (1 << 20);

  /* Set spi clock rate control register, divided by 2 */
  SPI0->CCR = 0x00001000;

  /* Enable spi0 and do a soft reset */
  val = SPI0->GCR;
  val |= (1 << 31) | (1 << 7) | (1 << 1) | (1 << 0);
  SPI0->GCR = val;
  while(SPI0->GCR & (1 << 31));

  val = SPI0->TCR;
  val &= ~(0x3 << 0);
  val |= (1 << 6) | (1 << 2);
  SPI0->TCR = val;

  SPI0->FCR |= (1 << 31) | (1 << 15);
}

void sys_spi_flash_exit(void)
{
  /* Disable the spi0 controller */
  SPI0->GCR &= ~((1 << 1) | (1 << 0));
}

static void sys_spi_select(void)
{
  uint32_t val;

  val = SPI0->TCR;
  val &= ~((0x3 << 4) | (0x1 << 7));
  val |= ((0 & 0x3) << 4) | (0x0 << 7);
  SPI0->TCR = val;
}

static void sys_spi_deselect(void)
{
  uint32_t val;

  val = SPI0->TCR;
  val &= ~((0x3 << 4) | (0x1 << 7));
  val |= ((0 & 0x3) << 4) | (0x1 << 7);
  SPI0->TCR = val;
}

static void sys_spi_write_txbuf(uint8_t * buf, int len)
{
  int i;

  if(!buf)
    len = 0;

  SPI0->MTC = len & 0xffffff;
  SPI0->BCC = len & 0xffffff;
  for(i = 0; i < len; ++i)
    *((volatile uint8_t *)(&SPI0->TXD_DATA)) = *buf++;
}

static int sys_spi_transfer(void * txbuf, void * rxbuf, int len)
{
  int count = len;
  uint8_t * tx = txbuf;
  uint8_t * rx = rxbuf;
  uint8_t val;
  int n, i;

  while(count > 0)
  {
    n = (count <= 64) ? count : 64;
    SPI0->MBC = n;
    sys_spi_write_txbuf(tx, n);
    SPI0->TCR |= (1 << 31);

    while((SPI0->FSR & 0xff) < n);
    for(i = 0; i < n; i++)
    {
      val = *((volatile uint8_t *)(&SPI0->RXD_DATA));
      if(rx)
        *rx++ = val;
    }

    if(tx)
      tx += n;
    count -= n;
  }
  return len;
}

static int sys_spi_write_then_read(void * txbuf, int txlen, void * rxbuf, int rxlen)
{
  if(sys_spi_transfer(txbuf, NULL, txlen) != txlen)
    return -1;
  if(sys_spi_transfer(NULL, rxbuf, rxlen) != rxlen)
    return -1;
  return 0;
}

void sys_spi_flash_read(int addr, void * buf, int count)
{
  uint8_t tx[4];

  tx[0] = 0x03;
  tx[1] = (uint8_t)(addr >> 16);
  tx[2] = (uint8_t)(addr >> 8);
  tx[3] = (uint8_t)(addr >> 0);
  sys_spi_select();
  sys_spi_write_then_read(tx, 4, buf, count);
  sys_spi_deselect();
}

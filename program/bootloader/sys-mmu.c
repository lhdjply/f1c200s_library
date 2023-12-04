#include <stdint.h>
#include <io.h>
#include <sizes.h>
#include <arm32.h>

static void map_l1_section(uint32_t * ttb, uint32_t virt, uint32_t phys, uint32_t size, int type)
{
  uint32_t i;

  virt >>= 20;
  phys >>= 20;
  size >>= 20;
  type &= 0x3;

  for(i = size; i > 0; i--, virt++, phys++)
    ttb[virt] = (phys << 20) | (0x3 << 10) | (0x0 << 5) | (type << 2) | (0x2 << 0);
}

void sys_mmu_init(void)
{
  uint32_t * ttb = (uint32_t *)(0x80000000 + SZ_1M * 63);

  map_l1_section(ttb, 0x00000000, 0x00000000, SZ_2G, 0);
  map_l1_section(ttb, 0x80000000, 0x80000000, SZ_2G, 0);
  map_l1_section(ttb, 0x80000000, 0x80000000, SZ_1M * 64, 3);

  arm32_ttb_set((uint32_t)(ttb));
  arm32_tlb_invalidate();
  arm32_domain_set(0x3);
  arm32_mmu_enable();
  arm32_icache_enable();
  arm32_dcache_enable();
}

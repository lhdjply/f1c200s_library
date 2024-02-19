#include <stdio.h>
#include <arm32.h>
//#include <interrupt/interrupt.h>

struct arm_regs_t
{
  uint32_t r[13];
  uint32_t sp;
  uint32_t lr;
  uint32_t pc;
  uint32_t cpsr;
};

static void show_regs(struct arm_regs_t * regs)
{
  while(1);
}

void arm32_do_undefined_instruction(struct arm_regs_t * regs)
{

}

void arm32_do_software_interrupt(struct arm_regs_t * regs)
{
  show_regs(regs);
  regs->pc += 4;
}

void arm32_do_prefetch_abort(struct arm_regs_t * regs)
{
  show_regs(regs);
  regs->pc += 4;
}

void arm32_do_data_abort(struct arm_regs_t * regs)
{
  show_regs(regs);
  regs->pc += 4;
}
extern void interrupt_handle_exception(void * regs);
void arm32_do_irq(struct arm_regs_t * regs)
{
  //interrupt_handle_exception(regs);
}

void arm32_do_fiq(struct arm_regs_t * regs)
{
  //interrupt_handle_exception(regs);
}

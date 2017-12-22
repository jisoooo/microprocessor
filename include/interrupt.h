#ifndef INTERRUPT
#define INTERRUPT

#include <stdio.h>

#include "s3c_uart.h"
#include "s3c6410.h"
#include "vic.h"

#define VIC0IRQSTATUS_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x0)
#define VIC0INTSELECT_REG __REG(ELFIN_VIC0_BASE_ADDR + 0xc)
#define VIC0INTENABLE_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x10)
#define VIC0INTENCLEAR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x14)

#define VIC0VECTADDR9 __REG(ELFIN_VIC0_BASE_ADDR + 0x124)
#define VIC0VECTADDR11 __REG(ELFIN_VIC0_BASE_ADDR + 0x12C)
#define VIC0VECTADDR24 __REG(ELFIN_VIC0_BASE_ADDR + 0x160)
#define VIC0VECTADDR29 __REG(ELFIN_VIC0_BASE_ADDR + 0x174)
#define VIC0VECTADDR30 __REG(ELFIN_VIC0_BASE_ADDR + 0x178)
#define VIC0VECTADDR31 __REG(ELFIN_VIC0_BASE_ADDR + 0x17C)

#define VIC1IRQSTATUS_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x0)
#define VIC1RAWINTR_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x8)
#define VIC1INTSELECT_REG __REG(ELFIN_VIC1_BASE_ADDR + 0xc)
#define VIC1INTENABLE_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x10)
#define VIC1INTENCLEAR_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x14)

#define VIC1VECTADDR30 __REG(ELFIN_VIC1_BASE_ADDR + 0x178)
#define VIC1VECTADDR31 __REG(ELFIN_VIC1_BASE_ADDR + 0x17c)

#define BIT_TIMER1 (1<<24)

#define TINT_CSTAT_REG __REG(0x7f006044)
#define BIT_TIMER1_STAT (1<<6)
#define BIT_TIMER1_EN (1<<1)

//Global variable

//end of global var

void enable_interrupts(void);

void disable_interrupts(void);

//unsigned int timer1_isr_call_count = 0;

void timer1InterruptServiceRoutine(void);

void mango_timer_init(void);

void touchInterruptServiceRoutine(void);

void touchInterruptServiceRoutine2(void);

void mango_interrupt_init(void);

void mango_hw_init(void);

void interrupt_reset(void);

void mango_menu_main(void);

#endif

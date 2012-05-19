/**
 * File: isr.h
 * Author: Guilherme Gonçalves Schardong
 * Declares the handler registration function and the registers struct.
 * File created on 20 July 2011, 11:37
 */

#ifndef __ISR_H__
#define __ISR_H__

#include <stdint.h>

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct registers {
  uint32 ds;
  uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32 int_no, err_code;
  uint32 eip, cs, eflags, useresp, ss;
};
typedef struct registers registers_t;
typedef void (*isr_t)(registers_t);

/**
 * init_handlers - Initializes the handlers array to zero.
 */
void k_init_handlers();

/**
 * register_handler - Registers a callback for an IRQ.
 * @index: The index of the handler.
 * @handler: The function pointer to the handler callback.
 */
void register_interrupt_handler(uint8 index, isr_t handler);

/**
 * reset_handler - Removes the custom handler for an IRQ.
 * @index: The index of the handler to be removed.
 */
void reset_interrupt_handler(uint8 index);

/**
 * ISRs and IRQs implemented on isr.asm.
 */
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif /* __ISR_H__ */

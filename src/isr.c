/**
 * File: isr.c
 * Author: Guilherme Gonçalves Schardong
 * Implements the handler registration and the basic isr/irq handlers
 * File created on 20 July 2011, 11:37
 */

#include <isr.h>
#include <asm.h>
#include <k_null.h>
#include <k_write.h>
#include <k_string.h>

isr_t interrupt_handlers[256];

void k_init_handlers() {
  memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);
}

void register_interrupt_handler(uint8 index, isr_t handler) {
  interrupt_handlers[index] = handler;
}

void reset_interrupt_handler(uint8 index) {
  interrupt_handlers[index] = NULL;
}

/**
 * isr_handler - Handles any of the first 32 exceptions.
 * @r: Values of the registers at the exception time.
 */
void isr_handler(registers_t r) {
  if(r.int_no != 0x40) {
    /* color_t fg, bg; */
    /* k_printf("Received interrupt: %d\n", r.int_no); */
    /* k_printf("Register dump.\n"); */
    /* get_color(&fg, &bg); */
    /* set_color(LIGHT_BROWN, RED); */
    /* k_printf("EAX: %X  EBX: %X  ECX: %X  EDX: %X  ESI: %X  EDI: %X\n", r.eax, r.ebx, r.ecx, r.edx, r.esi, r.edi); */
    /* k_printf("ESP: %X  EBP: %X  EIP: %X  CS: %X  DS: %X  SS: %X\n", r.esp, r.ebp, r.eip, r.cs, r.ds, r.ss); */
    /* set_color(fg, bg); */
  }
  if(interrupt_handlers[r.int_no] != 0) {
    isr_t handler = interrupt_handlers[r.int_no];
    handler(r);
  }
  else
    while(1) nop();
}

/**
 * irq_handler - Handles any of the 16 hardware interrupts.
 * @r: Values of the registers at the exception time.
  */
void irq_handler(registers_t r) {
  if(r.int_no >= 40)
    outb(0xA0, 0x20);
  outb(0x20, 0x20);
  if(interrupt_handlers[r.int_no] != 0) {
    isr_t handler = interrupt_handlers[r.int_no];
    handler(r);
  }
}

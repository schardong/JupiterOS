/**
 * File: pit.c
 * Author: Guilherme Gonçalves Schardong
 * Implementation of Programmable Interrupt Timer.
 * File created on 20 July 2011, 11:37
 */

#include <pit.h>
#include <asm.h>
#include <isr.h>
/* #include <task.h> */

static uint32 tick = 0;

/**
 * timer_cb - PIT callback.
 * @r: Current state of the processor.
 */
static void timer_cb(registers_t r) {
  tick++;
  /* task_switch(); */
}

void k_init_timer(uint32 frequency) {
  uint32 divisor = 1193180 / frequency;
  register_interrupt_handler(IRQ0, &timer_cb);
  outb(0x43, 0x36);
  outb(0x40, (uint8)(divisor & 0xFF));
  outb(0x40, (uint8)((divisor >> 8) & 0xFF));
}

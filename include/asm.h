/**
 * File: asm.h
 * Author: Guilherme Gonçalves Schardong
 * Implements the basic port io functions used by the kernel.
 * File created on 28 June 2011, 00:07
 */

#ifndef __ASM_H__
#define __ASM_H__

/**
 * inX - Receives a byte/word/dword from an I/O port.
 * @port: The port to read data from.
 * @returns: The data read from the given port.
 */
static inline unsigned char inb(unsigned short port) {
  unsigned char data;
  asm volatile("inb %%dx, %%al" : "=a"(data) : "d"(port));
  return data;
}

static inline unsigned short inw(unsigned short port) {
  unsigned short data;
  asm volatile("inw %%dx, %%al" : "=a"(data) : "d"(port));
  return data;
}

static inline unsigned int inl(unsigned short port) {
  unsigned int data;
  asm volatile("inl %%dx, %%al" : "=a"(data) : "d"(port));
  return data;
}

/**
 * outX - Sends a byte/word/dword to an I/O port.
 * @port: The port to send data to.
 * @data: The data to send.
 */
static inline void outb(unsigned short port, unsigned char data) {
  asm volatile("outb %%al, %%dx" :: "a"(data), "d"(port));
}

static inline void outw(unsigned short port, unsigned short data) {
  asm volatile("outw %%al, %%dx" :: "a"(data), "d"(port));
}

static inline void outl(unsigned short port, unsigned int data) {
  asm volatile("outl %%al, %%dx" :: "a"(data), "d"(port));
}

static inline void lidt(void* base, unsigned short size) {
  struct {
    unsigned short size;
    unsigned int base;
  } __attribute__((packed)) IDTR = {size, (unsigned int) base};
  asm volatile("lidt %0" : : "m"(IDTR));
}

/**
 * irq_enabled - Retuns true if the IRQs are enabled for the CPU.
 */
static inline int irq_enabled() {
  int en;
  asm volatile ("pushf\n\t"
                "popl %0"
                : "=g"(en));
  return en & ( 1 << 9 );
}

/**
 * cli - Stops all interrupts.
 */
static inline void cli() {
  asm volatile("cli");
}

/**
 * sti - Allows interrupts again.
 */
static inline void sti() {
  asm volatile("sti");
}

/**
 * halt - Halts the CPU.
 */
static inline void halt() {
  asm volatile("hlt");
}

/**
 * nop - Does nothing for one CPU cycle.
 */
static inline void nop() {
  asm volatile("nop");
}

#endif /* __ASM_H__ */

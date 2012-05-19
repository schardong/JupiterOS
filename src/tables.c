/**
 * File: tables.c
 * Author: Guilherme Gonçalves Schardong
 * Implementation of the GDT and IDT structs.
 * File created on 20 July 2011, 03:35
 */

#include <tables.h>
#include <asm.h>
#include <string.h>
#include <isr.h>

#define GDT_SIZE 5
#define IDT_SIZE 256

/**
 * gdt_flush - Load the new GDT to the GDTR register. Implemented on gdt.asm.
 */
extern void gdt_flush(uint32);

/**
 * Internal function prototypes.
 */
static void k_init_gdt();
static void k_init_idt();

/**
 * gdt_set_gate - Sets the value of one GDT entry.
 * @index: Index of the entry.
 * @base: Base value of the entry.
 * @limit: Limit value of the entry.
 * @access: Access ring of the segment.
 * @granularity: Granularity of the segment.
 */
static void gdt_set_gate(uint32, uint32 ,uint32, uint8, uint8);

/**
 * idt_set_gate - Set the value of one IDT entry.
 * @index - Index of the entry to set.
 * @base - Base address of the entry.
 * @selector - Selector word.
 * @flags - Attribute byte.
 */
static void idt_set_gate(uint8, uint32, uint16, uint8);

/**
 * Global variables. GDT, IDT and it's pointers.
 */
uint64 gdt_entries[GDT_SIZE];
uint64 idt_entries[IDT_SIZE];
dt_t gdt_ptr;

void k_init_tables() {
  k_init_gdt();
  k_init_idt();
  k_init_handlers();
}

static void k_init_gdt() {
  gdt_ptr.size = (sizeof(uint64) * GDT_SIZE) - 1;
  gdt_ptr.base  = (uint32) &gdt_entries;
  gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
  gdt_flush((uint32) &gdt_ptr);
}

static void k_init_idt() {
  memset(&idt_entries, 0, sizeof(uint64) * IDT_SIZE);
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);
  idt_set_gate(0, (uint32) isr0 , 0x08, 0x8E);
  idt_set_gate(1, (uint32) isr1 , 0x08, 0x8E);
  idt_set_gate(2, (uint32) isr2 , 0x08, 0x8E);
  idt_set_gate(3, (uint32) isr3 , 0x08, 0x8E);
  idt_set_gate(4, (uint32) isr4 , 0x08, 0x8E);
  idt_set_gate(5, (uint32) isr5 , 0x08, 0x8E);
  idt_set_gate(6, (uint32) isr6 , 0x08, 0x8E);
  idt_set_gate(7, (uint32) isr7 , 0x08, 0x8E);
  idt_set_gate(8, (uint32) isr8 , 0x08, 0x8E);
  idt_set_gate(9, (uint32) isr9 , 0x08, 0x8E);
  idt_set_gate(10, (uint32) isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32) isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32) isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32) isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32) isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32) isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32) isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32) isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32) isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32) isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32) isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32) isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32) isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32) isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32) isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32) isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32) isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32) isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32) isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32) isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32) isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32) isr31, 0x08, 0x8E);
  idt_set_gate(IRQ0, (uint32) irq0, 0x08, 0x8E);
  idt_set_gate(IRQ1, (uint32) irq1, 0x08, 0x8E);
  idt_set_gate(IRQ2, (uint32) irq2, 0x08, 0x8E);
  idt_set_gate(IRQ3, (uint32) irq3, 0x08, 0x8E);
  idt_set_gate(IRQ4, (uint32) irq4, 0x08, 0x8E);
  idt_set_gate(IRQ5, (uint32) irq5, 0x08, 0x8E);
  idt_set_gate(IRQ6, (uint32) irq6, 0x08, 0x8E);
  idt_set_gate(IRQ7, (uint32) irq7, 0x08, 0x8E);
  idt_set_gate(IRQ8, (uint32) irq8, 0x08, 0x8E);
  idt_set_gate(IRQ9, (uint32) irq9, 0x08, 0x8E);
  idt_set_gate(IRQ10, (uint32) irq10, 0x08, 0x8E);
  idt_set_gate(IRQ11, (uint32) irq11, 0x08, 0x8E);
  idt_set_gate(IRQ12, (uint32) irq12, 0x08, 0x8E);
  idt_set_gate(IRQ13, (uint32) irq13, 0x08, 0x8E);
  idt_set_gate(IRQ14, (uint32) irq14, 0x08, 0x8E);
  idt_set_gate(IRQ15, (uint32) irq15, 0x08, 0x8E);
  lidt(&idt_entries, sizeof(uint64) * IDT_SIZE - 1);
}

static void gdt_set_gate(uint32 index, uint32 base, uint32 limit, uint8 access, uint8 granularity) {
  uint64 mask = 0;
  /*Lower 16 bits of the limit.*/
  gdt_entries[index] = limit & 0xFFFF;
  /*Lower 16 bits of the base.*/
  mask = base & 0xFFFF;
  gdt_entries[index] |= mask << 16;
  /*Middle 8 bits of the base.*/
  mask = (base >> 16) & 0xFF;
  gdt_entries[index] |= mask << 32;
  /*Access byte.*/
  mask = access & 0xFF;
  gdt_entries[index] |= mask << 40;
  /*Granularity byte.*/
  mask = (granularity & 0xF0) | ((limit >> 16) & 0x0F);
  gdt_entries[index] |= mask << 48;
  /*Higher 8 bits of the base.*/
  mask = (base >> 24) & 0xFF;
  gdt_entries[index] |= mask << 56;
}

static void idt_set_gate(uint8 index, uint32 base, uint16 selector, uint8 flags) {
  uint64 mask = 0;
  /*Lower 16 bits of the base.*/
  idt_entries[index] = base & 0xFFFF;
  /*Selector word (16 bits).*/
  mask = selector;
  idt_entries[index] |= mask << 16;
  /*31-39 byte is always zero.*/
  mask = 0;
  idt_entries[index] |= mask << 32;
  /*Access flags.*/
  /*The or below must be uncommented when we get to using user-mode.*/
  /*It sets the interrupt gate's privilege level to 3.*/
  mask = flags | 0x60;
  idt_entries[index] |= mask << 40;
  /*Higher 16 bits of the base.*/
  mask = (base >> 16) & 0xFFFF;
  idt_entries[index] |= mask << 48;
}

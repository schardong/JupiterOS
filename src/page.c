#include <page.h>
#include <k_null.h>
#include <k_string.h>
#include <k_pmmngr.h>
#include <k_malloc.h>
#include <k_stdio.h>
#include <asm.h>
#include <isr.h>

page_dir_t* kernel_dir;
page_dir_t* curr_dir;

static void page_fault_handler(registers_t r);

void k_init_paging(uint32 mem_size) {
  uint32 i;
  k_init_pmmngr(BYTE(0x1000000 / 0x1000));

  kernel_dir = (page_dir_t*) k_malloc(sizeof(page_dir_t), true, NULL);
  memset(kernel_dir, 0, sizeof(page_dir_t));
  kernel_dir->phys_addr = (uint32) &kernel_dir->tables_phys_addr;
  curr_dir = kernel_dir;

  for(i = 0; i < get_placement_addr() + 0x1000; i += 0x1000)
    alloc_frame(get_page(i, true, kernel_dir), false, false);

  register_interrupt_handler(14, &page_fault_handler);
  load_page_dir(kernel_dir);
}

void load_page_dir(page_dir_t* new_dir) {
  curr_dir = new_dir;
  asm volatile("mov %0, %%cr3" :: "r"(&new_dir->tables_phys_addr));
  unsigned int cr0;
  asm volatile("mov %%cr0, %0" : "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

page_t* get_page(uint32 addr, bool make, page_dir_t* page_dir) {
  addr /= 0x1000;
  uint32 table_idx = addr / 1024;
  if(page_dir->tables[table_idx] != 0)
    return &page_dir->tables[table_idx]->pages[addr % 1024];
  else if(make == true) {
    uint32 tmp_addr;
    page_dir->tables[table_idx] = (page_table_t*) k_malloc(sizeof(page_table_t), 1, &tmp_addr);
    memset(page_dir->tables[table_idx], 0, 0x1000);
    page_dir->tables_phys_addr[table_idx] = tmp_addr | 0x7;
    return &page_dir->tables[table_idx]->pages[addr % 1024];
  }
  return NULL;
}

static void page_fault_handler(registers_t r) {
  uint32 fault_addr;
  asm volatile("mov %%cr2, %0" : "=r"(fault_addr));
  uint8 present = !(r.err_code & 0x1);
  uint8 read_write = r.err_code & 0x2;
  uint8 user_mode = r.err_code & 0x4;
  uint8 reserved_bits = r.err_code & 0x8;
  uint8 instruction = r.err_code & 0x10;
  k_printf("Page fault (");
  if(present) k_printf("present");
  if(read_write) k_printf(" read-only");
  if(user_mode) k_printf(" user-mode");
  if(reserved_bits) k_printf(" reserved");
  if(instruction) k_printf(" instruction");
  k_printf(") at 0x%X\n", fault_addr);
  halt();
}

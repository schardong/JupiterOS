#include <k_write.h>
#include <tables.h>
#include <k_stdio.h>
#include <k_string.h>
#include <asm.h>
#include <pit.h>
#include <keyboard.h>
#include <multiboot.h>
#include <page.h>

int main(int esp, multiboot_t* mboot) {
  k_init_screen();

  cli();
  k_init_tables();
  k_init_timer(100);
  k_init_keyboard();
  sti();
  k_init_paging(mboot->mem_lower + mboot->mem_upper);

  k_printf("Stack address: %X\n", esp);
  k_printf("Multiboot flags: %X\n", mboot->flags);
  k_printf("Multiboot mem_lower: %d\n", mboot->mem_lower);
  k_printf("Multiboot mem_upper: %d\n", mboot->mem_upper);
  k_printf("Multiboot mods_count: %d\n", mboot->mods_count);
  k_printf("Total system memory: %d Kb\n", mboot->mem_lower + mboot->mem_upper);

  return 0x668;
}

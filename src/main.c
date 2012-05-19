#include <k_write.h>
#include <tables.h>
#include <k_printf.h>
#include <asm.h>
#include <pit.h>

int main() {
  k_init_screen();

  cli();
  k_init_tables();
  k_init_timer(100);
  sti();

  char hw[39] = "ABCDEFGHIJKLMNOPQRSTUVVWXYZ_0123456789";
  k_printf("Testing the k_printf function.\n");
  k_printf("%s\n", hw);

  return 0x668;
}

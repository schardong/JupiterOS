#include <k_write.h>
#include <tables.h>
#include <asm.h>
#include <pit.h>

int main() {
  k_init_screen();

  cli();
  k_init_tables();
  k_init_timer(100);
  sti();

  return 0x668;
}

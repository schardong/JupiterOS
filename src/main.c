#include <k_write.h>
#include <tables.h>
#include <k_stdio.h>
#include <k_string.h>
#include <asm.h>
#include <pit.h>
#include <keyboard.h>

int main() {
  k_init_screen();

  cli();
  k_init_tables();
  k_init_timer(100);
  k_init_keyboard();
  sti();

  return 0x668;
}

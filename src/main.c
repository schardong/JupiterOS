#include <k_write.h>

int main() {
  k_init_screen();
  k_writes("Screen initialized.\n");
  k_set_color(LIGHT_BROWN, RED);
  k_writes("TODO:\n");
  k_writes("\tGDT, IDT, ISR, IRQ\n");
  k_writes("\tTimer, Keyboard input, Memory manager, VFS, Multitasking.\n");
  return 0x668;
}

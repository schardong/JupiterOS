#include <k_write.h>
#include <asm.h>

#define VGA_ADDR 0xB8000
#define MAX_LINES 25
#define MAX_COLUMNS 80
#define ADDR(x,y) (y * 80 + x)
#define MAX_SIZE (MAX_LINES * MAX_COLUMNS * 2)
#define TAB_SIZE 8

uint8 curr_color;
uint16* vga_addr;
uint16 x, y;

void move_cursor();
void scroll(int32 lines);

void k_init_screen() {
  vga_addr = (uint16*) VGA_ADDR;
  curr_color = 0x0F;
  x = y = 0;
  k_clear_screen();
}

void k_clear_screen() {
  int i;
  for(i = 0; i < MAX_SIZE; i++)
    vga_addr[i] = curr_color << 8 | 0x20;
  x = y = 0;
  move_cursor();
}

void k_writec(int8 c) {
  uint32 index;
  switch(c) {
  case '\b':
    if(x != 0)
      x--;
    vga_addr[ADDR(x, y)] = (curr_color << 8) | 0x20;
    break;
  case '\t':
    x = (x + TAB_SIZE) & ~(TAB_SIZE - 1);
    break;
  case '\n':
    x = 0;
    y++;
    break;
  case '\r':
    x = 0;
    break;
  default:
    index = ADDR(x, y);
    vga_addr[index] = (curr_color << 8) | c;
    x++;
    break;
  }
  if(x >= 80) {
    x = 0;
    y++;
  }
  if(y >= 25) {
    scroll(1);
    y = 24;
  }
  move_cursor();
}

void k_writes(int8* s) {
  int8* c;
  for(c = s; *c != '\0'; c++)
    k_writec(*c);
}

void k_set_color(color_t fg, color_t bg) {
  curr_color = (uint8) bg << 4 | fg;
}

void k_get_color(color_t* fg, color_t* bg) {
  *fg = curr_color & 0xF;
  *bg = (curr_color >> 4) & 0xF;
}

void move_cursor() {
  uint32 cursor = ADDR(x, y);
  outb(0x3D4, 14);
  outb(0x3D5, cursor >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, cursor);
}

void scroll(int32 lines) {
  int32 i;
  for(i = 0; i < MAX_SIZE - (lines * MAX_COLUMNS); i++)
    vga_addr[i] = vga_addr[i + (lines * MAX_COLUMNS)];
  for(; i < MAX_SIZE; i++)
    vga_addr[i] = (curr_color << 8) | 0x20;
}

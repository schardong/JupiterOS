#ifndef __KERNEL_K_WRITE_H__
#define __KERNEL_K_WRITE_H__

#include <k_stdint.h>

enum color {
  BLACK,           //0
  BLUE,            //1
  GREEN,           //2
  CYAN,            //3
  RED,             //4
  MAGENTA,         //5
  BROWN,           //6
  LIGHT_GRAY,      //7
  DARK_GRAY,       //8
  LIGHT_BLUE,      //9
  LIGHT_GREEN,     //10
  LIGHT_CYAN,      //11
  LIGHT_RED,       //12
  LIGHT_MAGENTA,   //13
  LIGHT_BROWN,     //14
  WHITE            //15
};
typedef enum color color_t;

void k_init_screen();
void k_clear_screen();
void k_writec(int8 c);
void k_writes(int8* s);
void k_set_color(color_t fg, color_t bg);
void k_get_color(color_t* fg, color_t* bg);

#endif /* __KERNEL_K_WRITE_H__ */

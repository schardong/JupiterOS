/**
 * File: keyboard.c
 * Author: Guilherme Gonçalves Schardong
 * Description of the keyboard interrupt
 * File created on 22 July 2011, 18:41
 */

#include <keyboard.h>
#include <isr.h>
#include <asm.h>
#include <stdint.h>
#include <string.h>
#include <k_printf.h>


/**
 * Determines wheter any of the control keys were pressed or released.
 * Its value is 1 if a control key is pressed or 0 otherwise.
 */
static uint8 alt_pressed = 0;
static uint8 ctrl_pressed = 0;
static uint8 shift_pressed = 0;

/**
 * Some keys have two byte scancodes. The first byte is always
 * 0xE0. When this byte is read escaped will be 1 and we will
 * wait for the next scancode, then we will set it to 0 again.
 */
uint32 escaped = 0;

/**
 * pln - Prints the character given a scancode.
 * @scancode: The scancode given by the keyboard.
 */
static void pln(uint8 scancode) {
  uint8 print_key_map[0x3A][2] = {
    {0x0, 0x0}, {0x0, 0x0}, {'1', '!'}, {'2', '@'},
    {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'},
    {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
    {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'},
    {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
    {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
    {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
    {'\n', '\n'}, {0x0, 0x0}, {'a', 'A'}, {'s', 'S'},
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
    {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
    {'\'', '\"'}, {'`', '~'}, {0x0, 0x0}, {'\\', '|'},
    {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'},
    {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
    {'.', '>'}, {'/', '?'}, {0x0, 0x0}, {'*', '*'},
    {0x0, 0x0}, {' ', ' '}
  };
  uint8 c = print_key_map[scancode & 0x7F][shift_pressed];
  /* if(c != '\b') */
  /*   *in_buff_ptr++ = c; */
  /* else */
  /*   *(--in_buff_ptr) = 0; */
  /* if(in_buff_ptr - in_buffer >= BUFFER_SIZE) */
  /*   in_buff_ptr = in_buffer; */
  k_printf("%c", c);
}

static void unp(uint8 scancode) {
}

static void fun(uint8 scancode) {
}

static void nul(uint8 scancode) {
}

static void keyboard_handler(registers_t r) {
  uint8 scancode = inb(0x60);
  void (*key_way[0x80])(uint8) = {
    /*00*/unp, unp, pln, pln, pln, pln, pln, pln,
    /*08*/pln, pln, pln, pln, pln, pln, pln, pln,
    /*10*/pln, pln, pln, pln, pln, pln, pln, pln,
    /*18*/pln, pln, pln, pln, pln, nul, pln, pln,
    /*20*/pln, pln, pln, pln, pln, pln, pln, pln,
    /*28*/pln, pln, nul, pln, pln, pln, pln, pln,
    /*30*/pln, pln, pln, pln, pln, pln, nul, pln,
    /*38*/nul, pln, unp, fun, fun, fun, fun, fun,
    /*40*/fun, fun, fun, fun, fun, unp, unp, unp,
    /*48*/unp, unp, unp, unp, unp, unp, unp, unp,
    /*50*/unp, unp, unp, unp, unp, unp, unp, fun,
    /*58*/fun, unp, unp, unp, unp, unp, unp, unp,
    /*60*/unp, unp, unp, unp, unp, unp, unp, unp,
    /*68*/unp, unp, unp, unp, unp, unp, unp, unp,
    /*70*/unp, unp, unp, unp, unp, unp, unp, unp,
    /*78*/unp, unp, unp, unp, unp, unp, unp, unp,
  };
  switch(scancode) {
  case 0x2A:
    shift_pressed = 1; escaped = 0; break;
  case 0xAA:
    shift_pressed = 0; escaped = 0; break;
  case 0x1D:
    ctrl_pressed = 1; escaped = 0; break;
  case 0x9D:
    ctrl_pressed = 0; escaped = 0; break;
  case 0x38:
    alt_pressed = 1; escaped = 0; break;
  case 0xB8:
    alt_pressed = 0; escaped = 0; break;
  case 0xE0:
    escaped = 1; break;
  default:
    if (scancode & 0x80) {
      /* break code: the user released a key.*/
    }
    else
      (*key_way[scancode & 0x7F])(scancode);
    escaped = 0;
    break;
  }
}

void k_init_keyboard() {
  register_interrupt_handler(IRQ1, &keyboard_handler);
  outb(0x21, inb(0x21) & 0xFD);
}

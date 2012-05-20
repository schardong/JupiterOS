#include <k_ctype.h>

/* int isalnum(int c) */
/* int isalpha(int c) */
/* int isascii(int c) */
/* int isblank(int c) */
/* int iscntrl(int c) */
/* int isdigit(int c) */
/* int isgraph(int c) */
/* int islower(int c) */
/* int isprint(int c) */
/* int ispunct(int c) */
/* int isspace(int c) */
/* int isupper(int c) */
/* int isxdigit(int c) */

int toupper(int c) {
  if(c >= 97 && c <= 122)
    c -= 32;
  return c;
}

int tolower(int c) {
  if(c >= 65 && c <= 90)
    c += 32;
  return c;
}

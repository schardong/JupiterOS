#include <k_itoa.h>

void k_itoa(int val, char* s, int radix) { 
  char* c = s;
  char aux;
  if(val < 0) {
    val *= -1;
    *c++ = '-';
  }
  do {
    *c = (char) (val % radix);
    if(*c >= 10)
      *c += 87;
    else
      *c += 48;
    val /= radix;
    c++;
  } while(val > 0);
  *c-- = '\0';
  while(c >= s) {
    aux = *s;
    *s = *c;
    *c = aux;
    c--;
    s++;
  }
}

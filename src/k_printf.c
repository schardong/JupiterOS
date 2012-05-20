#include <k_stdio.h>
#include <k_write.h>
#include <k_itoa.h>
#include <k_string.h>
#include <k_ctype.h>

void k_printf(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  k_vprintf(fmt, ap);

  va_end(ap);
}

void k_vprintf(const char* fmt, va_list ap) {
  uint32 i;
  char num[12];
  for(i = 0; i < strlen(fmt); i++) {
    if(fmt[i] != '%' && fmt[i] != '\\') {
      k_writec(fmt[i]);
      continue;
    } else if(fmt[i] == '\\') {
      switch(fmt[++i]) {
      case 'a':
	k_writec('\a');
	break;
      case 'b':
	k_writec('\b');
	break;
      case 't':
	k_writec('\t');
	break;
      case 'n':
	k_writec('\n');
	break;
      case 'r':
	k_writec('\r');
	break;
      case '\\':
	k_writec('\a');
	break;
      }
      continue;
    }
    switch(fmt[++i]) {
    case 's':
      k_writes((char*) va_arg(ap, char*));
      break;
    case 'c':
      k_writec((char) va_arg(ap, char));
      break;
    case 'd':
      k_itoa((int) va_arg(ap, int), num, 10);
      k_writes(num);
      break;
    case 'o':
      k_itoa((int) va_arg(ap, int), num, 8);
      k_writes(num);
      break;
    case 'x':
      k_itoa((int) va_arg(ap, int), num, 16);
      k_writes("0x");
      k_writes(num);
      break;
    case 'X':
      k_itoa((int) va_arg(ap, int), num, 16);
      k_writes("0x");
      uint32 idx;
      for(idx = 0; idx < strlen(num); idx++)
	num[idx] = (char) toupper((char) num[idx]);
      k_writes(num);
      break;
    case '%':
      k_writec('%');
      break;
    default:
      k_writec(fmt[i]);
      break;
    }
  }
}

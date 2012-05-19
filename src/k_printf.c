#include <k_printf.h>
#include <k_write.h>
#include <string.h>

void k_printf(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  k_vprintf(fmt, ap);

  va_end(ap);
}

void k_sprintf(char* str, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  k_vsprintf(str, fmt, ap);

  va_end(ap);
}

void k_vprintf(const char* fmt, va_list ap) {
  uint32 i;
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
    case 'o':
    case 'x':
    case 'X':
    case '%':
      k_writec('%');
      break;
    default:
      k_writec(fmt[i]);
      break;
    }
  }
}

void k_vsprintf(char* str, const char* fmt, va_list ap) {
}

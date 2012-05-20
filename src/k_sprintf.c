#include <k_stdio.h>
#include <k_itoa.h>
#include <k_string.h>
#include <k_ctype.h>
#include <k_null.h>

void k_sprintf(char* str, const char* fmt, ...) {
  va_list ap;

  if(str == NULL || fmt == NULL || strlen(fmt) == 0)
    return;

  va_start(ap, fmt);

  k_vsprintf(str, fmt, ap);

  va_end(ap);
}

void k_vsprintf(char* str, const char* fmt, va_list ap) {
  uint32 i, idx, a;
  char num[12], *s;
  for(i = 0, idx = 0; i < strlen(fmt); i++) {
    if(fmt[i] == '%') {
      switch(fmt[++i]) {
      case 's':
	s = (char*) va_arg(ap, char*);
	strcpy(&str[idx], s);
	idx += strlen(s);
	break;
      case 'c':
	str[idx++] = (char) va_arg(ap, char);
	break;
      case 'd':
	k_itoa((int) va_arg(ap, int), num, 10);
	strcpy(&str[idx], num);
	idx += strlen(num);
	break;
      case 'x':
	k_itoa((int) va_arg(ap, int), num, 16);
	strcpy(&str[idx], num);
	idx += strlen(num);
	break;
      case 'X':
	k_itoa((int) va_arg(ap, int), num, 16);
	uint32 j;
	for(j = 0; j < strlen(num); j++)
	  num[j] = toupper(num[j]);
	strcpy(&str[idx], num);
	idx += strlen(num);
	break;
      case 'o':
	k_itoa((int) va_arg(ap, int), num, 8);
	strcpy(&str[idx], num);
	idx += strlen(num);
	break;
      default:
	str[idx++] = fmt[i];
	break;
      }
      continue;
    }
    str[idx++] = fmt[i];
  }
}

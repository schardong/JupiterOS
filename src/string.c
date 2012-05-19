/**
 * File: string.c
 * Author: Guilherme Gonçalves Schardong
 * Implements the basic libcc string functions.
 * File created on 28 June 2011, 09:44
 */

#include <string.h>

void bcopy(const void* src, void* dest, size_t count) {
  const char* s = src;
  char* d = dest;
  if(s <= d)
    for(; count > 0; --count)
      d[count - 1] = s[count - 1];
  else
    for(; count > 0; --count)
      *d++ = *s++;
}

void bzero(void* dest, size_t count) {
  memset(dest, 0, count);
}

void* memcpy(void* dest, const void* src, size_t count) {
  char* ptr_dest = (char*) dest;
  const char* ptr_src = (const char*) src;
  while(count--)
    *ptr_dest++ = *ptr_src++;
  return dest;
}

void* memset(void* dest, char val, size_t count) {
  char* ptr_dest = (char*) dest;
  while(count--)
    *ptr_dest++ = val;
  return dest;
}

int memcmp(const void* cs, const void* ct, size_t count) {
  const char *ps, *pt;
  int result = 0;
  for(ps = cs, pt = ct; count > 0; ps++, pt++, count--)
    if((result = *ps - *pt) != 0)
      break;
  return result;
}

char* strcpy(char* dest, const char* src) {
  char* ptr_dest = dest;
  const char* ptr_src = src;
  while((*ptr_dest++ = *ptr_src++));
  return dest;
}

int strcmp(const char* s1, const char* s2) {
  const char *p, *q;
  int result = 0;
  for(p = s1, q = s2; *p && *q; p++, q++)
    if((result = *p - *q) != 0)
      break;
  return result;
}

size_t strlen(const char* s) {
  const char* ptr_str;
  for(ptr_str = s; *ptr_str; ptr_str++);
  return (size_t) (ptr_str - s);
}

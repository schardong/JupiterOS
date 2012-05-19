#ifndef __KERNEL_K_PRINTF_H__
#define __KERNEL_K_PRINTF_H__

#include <stdarg.h>

void k_printf(const char* fmt, ...);

void k_sprintf(char* str, const char* fmt, ...);

void k_vprintf(const char* fmt, va_list ap);

void k_vsprintf(char* str, const char* fmt, va_list ap);

#endif /* __KERNEL_K_PRINTF_H__ */

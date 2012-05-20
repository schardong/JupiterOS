#ifndef __KERNEL_K_STDIO_H__
#define __KERNEL_K_STDIO_H__

#include <k_stdarg.h>

void k_printf(const char* fmt, ...);

void k_vprintf(const char* fmt, va_list ap);

#endif /* __KERNEL_K_STDIO_H__ */

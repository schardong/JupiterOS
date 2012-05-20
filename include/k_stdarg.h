#ifndef __KERNEL_STDARG_H__
#define __KERNEL_STDARG_H__

#include <k_va_list.h>
#include <k_stdint.h>

#define _va_size(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(ap, fmt) (ap = ((va_list) &fmt + _va_size(&fmt)))

#define va_end(ap)

#define va_arg(ap, type) (ap += _va_size(type), *((type*) (ap - _va_size(type))))

#endif /* __KERNEL_STDARG_H__ */

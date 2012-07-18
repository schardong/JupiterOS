#ifndef __KERNEL_MALLOC_H__
#define __KERNEL_MALLOC_H__

#include <k_size_t.h>
#include <k_stdbool.h>
#include <k_stdint.h>

uint32 k_malloc(size_t num_bytes, bool page_aligned, uint32* phys_addr);

void k_free(void* ptr);

uint32 get_placement_addr();

void set_placement_addr(uint32 addr);

#endif /* __KERNEL_MALLOC_H__ */

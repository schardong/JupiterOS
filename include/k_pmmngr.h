#ifndef __KERNEL_PMMGR_H__
#define __KERNEL_PMMGR_H__

#include <bitset.h>
#include <page.h>
#include <k_stdint.h>

void k_init_pmmngr(uint32 num_bytes);

void alloc_frame(page_t* pg, bool is_kernel_pg, bool write_allowed);

void free_frame(page_t* pg);

#endif /* __KERNEL_PMMGR_H__ */

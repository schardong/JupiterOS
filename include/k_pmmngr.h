#ifndef __KERNEL_PMMGR_H__
#define __KERNEL_PMMGR_H__

#include <bitset.h>
#include <k_page.h>
#include <k_stdint.h>
#include <k_stdbool.h>

void k_init_pmmngr(uint32 num_bytes);

void alloc_frame(k_page* pg, bool is_kernel_pg, bool write_allowed);

void free_frame(k_page* pg);

/**
 * get_num_frames: Returns the number of frames.
 * @state: If set then the function returns the number of occupied frames.
 * If unset, it returns the number of free frames.
 * @returns: The number of frames given the state.
 */
uint32 get_num_frames(bool state);

#endif /* __KERNEL_PMMGR_H__ */

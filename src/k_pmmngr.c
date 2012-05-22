#include <k_pmmngr.h>

bitset_t* frames;

uint32 first_frame() {
  uint32 i, j;
  for(i = 0; i < frames->num_bytes; i++)
    if(frames->set[i] != 0xFF)
      for(j = 0; j < 8; j++)
	if(test_bit(frames, i * 8 + j) == 0)
	  return i * 8 + j;
  return 0;
}

void k_init_pmmngr(uint32 num_bytes) {
  frames = create_bitset(num_bytes);
}

void alloc_frame(page_t* pg, bool is_kernel_pg, bool write_allowed) {
  if((*pg & 0xFFFFF000) != 0)
    return;
  uint32 idx = first_frame();
  if(idx == (uint32) - 1)
    return;
  set_bit(frames, idx);
  *pg = (idx << 12) | (is_kernel_pg << 2) | (write_allowed << 1) | 0x1;
}

void free_frame(page_t* pg) {
  if((*pg & 0xFFFFF000) == 0)
    return;
  clear_bit(frames, ((*pg & 0xFFFFF000) / 4096) / 8);
  *pg = 0x0;
}

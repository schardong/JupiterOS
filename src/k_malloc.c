#include <k_malloc.h>
#include <k_null.h>

extern uint32 end;
static uint32 placement_addr = (uint32) &end;

uint32 k_malloc(size_t num_bytes, bool page_aligned, uint32* phys_addr) {
  if(page_aligned == true && (placement_addr & 0xFFFFF000) != 0) {
    placement_addr &= 0xFFFFF000;
    placement_addr += 0x1000;
  }
  if(phys_addr != NULL)
    *phys_addr = placement_addr;
  uint32 result = placement_addr;
  placement_addr += num_bytes;
  return result;
}

void k_free(void* ptr) {
}

uint32 get_placement_addr() {
  return placement_addr;
}
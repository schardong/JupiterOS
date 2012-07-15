#ifndef __KERNEL_HEAP_H__
#define __KERNEL_HEAP_H__

#include <k_ordered_arr.h>

#define K_HEAP_START_ADDR 0xC0000000
#define K_HEAP_INIT_SIZE 0x100000
#define K_HEAP_INDEX_SIZE 0x20000
#define K_HEAP_MAGIC 0x08031211
#define K_HEAP_MIN_SIZE 0x7000

struct _header {
  struct _header* next;
  struct _header* prev;
  uint32 size;
  uint32 magic;
  bool is_hole;
};
typedef struct _header k_heap_header;

struct _k_heap {
  k_ordered_arr index_arr;
  uint32 start_addr;
  uint32 end_addr;
  uint32 max_addr;
  bool super;
  bool writeable;
};
typedef struct _k_heap k_heap;

k_heap* k_init_heap(uint32 start, uint32 end, uint32 max, bool super, bool write);

void k_destroy_heap(k_heap* hp);

void* allocate(k_heap* hp, size_t sz, bool align);

void free(k_heap* hp, void* ptr);

#endif /* __KERNEL_HEAP_H__ */

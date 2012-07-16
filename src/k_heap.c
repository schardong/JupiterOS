#include <k_heap.h>
#include <k_malloc.h>
#include <k_size_t.h>
#include <k_page.h>
#include <k_pmmngr.h>

void expand_heap(k_heap* hp, size_t new_size);
size_t contract_heap(k_heap* hp, size_t new_size);
bool cb_header(void* a, void* b);
int32 find_smallest_hole(k_heap* hp, size_t size, bool page_align);

k_heap* k_init_heap(uint32 start, uint32 end, uint32 max, bool super, bool write) {
  k_heap* hp = (k_heap*) k_malloc(sizeof(k_heap), false, NULL);

  if(start % 0x1000 || end % 0x1000)
    return NULL;

  hp->index_arr = place_ordered_arr((void*) start, K_HEAP_INDEX_SIZE, &cb_header);

  start += sizeof(type_t) * K_HEAP_INDEX_SIZE;

  if((start & 0xFFFFF000) != 0) {
    start &= 0xFFFFF000;
    start += 0x1000;
  }

  hp->start_addr = start;
  hp->end_addr = end;
  hp->max_addr = max;
  hp->super = super;
  hp->writeable = write;

  k_heap_header* h = (k_heap_header*) start;
  h->size = end - start;
  h->magic = K_HEAP_MAGIC;
  h->is_hole = true;

  return hp;
}

void k_destroy_heap(k_heap* hp) {
  if(hp != NULL) {
    destroy_ordered_arr(&hp->index_arr);
    k_free(hp);
  }
}

void* allocate(k_heap* hp, size_t sz, bool align) {
  size_t new_size = sizeof(k_heap_header) + sizeof(k_heap_footer) + sz;
  int32 it = find_smallest_hole(hp, new_size, align);

  if(it == -1) {
    //TODO: Handle errors.
  }

  k_heap_header* orig_hole_header = (k_heap_header*) search_ordered_arr(&hp->index_arr, it);

  uint32 orig_hole_header_loc = (uint32) orig_hole_header;
  uint32 orig_hole_header_size = orig_hole_header->size;
  if(orig_hole_header_size - new_size < sizeof(k_heap_header) + sizeof(k_heap_footer)) {
    sz += orig_hole_header_size - new_size;
    new_size = orig_hole_header_size;
  }

  if(align == true && (orig_hole_header_loc & 0xFFFFF000) != 0) {
    uint32 new_loc = orig_hole_header_loc + 0x1000 - (orig_hole_header_loc & 0xFFF) - sizeof(k_heap_header);

    k_heap_header* hole_header = (k_heap_header*) orig_hole_header_loc;
    hole_header->size = 0x1000 - (orig_hole_header_loc & 0xFFF)- sizeof(k_heap_header);
    hole_header->magic = K_HEAP_MAGIC;
    hole_header->is_hole = true;
    
    k_heap_footer* hole_footer = (k_heap_footer*) ((uint32) new_loc - sizeof(k_heap_footer));
    hole_footer->magic = K_HEAP_MAGIC;
    hole_footer->header = hole_header;
    orig_hole_header_loc = new_loc;
    orig_hole_header_size -= hole_header->size;
  }
  else
    remove_ordered_arr(&hp->index_arr, it);

  k_heap_header* blck_header = (k_heap_header*) orig_hole_header_loc;
  blck_header->magic = K_HEAP_MAGIC;
  blck_header->size = new_size;
  blck_header->is_hole = false;

  k_heap_footer* blck_footer = (k_heap_footer*) (orig_hole_header_loc + sizeof(k_heap_header) + sz);
  blck_footer->magic = K_HEAP_MAGIC;
  blck_footer->header = blck_header;

  if(orig_hole_header_size - new_size > 0) {
    k_heap_header* hole_header = (k_heap_header*) (orig_hole_header_loc + sizeof(k_heap_header) + sz + sizeof(k_heap_footer));
    hole_header->magic = K_HEAP_MAGIC;
    hole_header->is_hole = true;
    hole_header->size = orig_hole_header_size - new_size;

    k_heap_footer* hole_footer = (k_heap_footer*) ((uint32) hole_header + orig_hole_header_size - new_size - sizeof(k_heap_footer));
    if((uint32) hole_footer < hp->end_addr) {
      hole_footer->magic = K_HEAP_MAGIC;
      hole_footer->header = hole_header;
    }
    insert_ordered_arr(&hp->index_arr, (void*) hole_header);
  }

  return (void*) ( (uint32) blck_header + sizeof(k_heap_header));
}

void free(k_heap* hp, void* ptr) {
  //TODO: Do the free function (k_heap.c)
}

void expand_heap(k_heap* hp, size_t new_size) {
  if(new_size <= hp->end_addr - hp->start_addr)
    return;

  if((new_size & 0xFFFFF000) != 0) {
    new_size &= 0xFFFFF000;
    new_size += 0x1000;
  }

  if(hp->start_addr + new_size > hp->max_addr)
    return;

  size_t old_size = hp->end_addr - hp->start_addr;
  size_t i = old_size;
  while(i < new_size) {
    alloc_frame(get_page(hp->start_addr + i, true, get_kernel_dir()), hp->super, hp->writeable);
    i += 0x1000;
  }

  hp->end_addr = hp->start_addr + new_size;
}

size_t contract_heap(k_heap* hp, size_t new_size) {
  if(new_size >= hp->end_addr - hp->start_addr)
    return new_size;

  if((new_size & 0x1000) != 0) {
    new_size &= 0x1000;
    new_size += 0x1000;
  }

  if(new_size < K_HEAP_MIN_SIZE)
    new_size = K_HEAP_MIN_SIZE;

  size_t old_size = hp->end_addr - hp->start_addr;
  size_t i = old_size - 0x1000;
  while(i > new_size) {
    free_frame(get_page(hp->start_addr + i, false, get_kernel_dir()));
    i -= 0x1000;
  }

  hp->end_addr = hp->start_addr + new_size;
  return new_size;
}

bool cb_header(void* a, void* b) {
  return (((k_heap_header*) a)->size < ((k_heap_header*) b)->size)? 1:0;
}

int32 find_smallest_hole(k_heap* hp, size_t size, bool page_align) {
  uint32 it = 0;
  while(it < hp->index_arr.size) {
    k_heap_header* h = (k_heap_header*) search_ordered_arr(&hp->index_arr, it);
    if(page_align == true) {
      uint32 h_addr = (uint32) h;
      int32 off = 0;
      if(((h_addr + sizeof(k_heap_header)) & 0xFFFFF000) != 0)
	off = 0x1000 - (h_addr + sizeof(k_heap_header)) % 0x1000;
      int32 hole_size = (int32) h->size - off;
    }
    else if(h->size >= size)
      break;

    it++;
  }

  if(it == hp->index_arr.size)
    return -1;
  return it;
}

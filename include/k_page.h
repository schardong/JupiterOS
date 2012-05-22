#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include <k_stdint.h>
#include <k_stdbool.h>

typedef uint32 k_page;

struct page_table {
  k_page pages[1024];
};
typedef struct page_table k_page_tab;

struct page_directory {
  k_page_tab* tables[1024];
  uint32 tables_phys_addr[1024];
  uint32 phys_addr;
};
typedef struct page_directory k_page_dir;

void k_init_paging(uint32 mem_size);

void load_page_dir(k_page_dir* new_dir);

k_page* get_page(uint32 addr, bool make, k_page_dir* page_dir);

#endif /* __KERNEL_PAGE_H__ */

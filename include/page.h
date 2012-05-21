#ifndef __KERNEL_PAGE_H__
#define __KERNEL_PAGE_H__

#include <k_stdint.h>
#include <k_stdbool.h>

typedef uint32 page_t;

struct page_table {
  page_t pages[1024];
};
typedef struct page_table page_table_t;

struct page_directory {
  page_table_t* tables[1024];
  uint32 tables_phys_addr[1024];
  uint32 phys_addr;
};
typedef struct page_directory page_dir_t;

void k_init_paging();

void load_page_dir(page_dir_t* new_dir);

page_t* get_page(uint32 addr, bool make, page_dir_t* page_dir);

#endif /* __KERNEL_PAGE_H__ */

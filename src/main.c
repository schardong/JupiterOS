#include <k_write.h>
#include <tables.h>
#include <k_stdio.h>
#include <k_string.h>
#include <asm.h>
#include <pit.h>
#include <keyboard.h>
#include <multiboot.h>
#include <k_page.h>
#include <k_malloc.h>
#include <vfs.h>
#include <initrd.h>
#include <k_null.h>

void list_root(fs_node* node);

int main(int esp, multiboot_t* mboot) {
  k_init_screen();

  cli();
  k_init_tables();
  k_init_timer(100);
  k_init_keyboard();
  sti();

  uint32 initrd_addr = *((uint32*) mboot->mods_addr);
  uint32 initrd_end = *(uint32*) (mboot->mods_addr + 4);
  set_placement_addr(initrd_end);

  k_init_paging((mboot->mem_lower + mboot->mem_upper) * 1024);
  /* fs_node* root = k_init_initrd(initrd_addr); */

  k_printf("Stack address: %X\n", esp);
  k_printf("Multiboot flags: %X\n", mboot->flags);
  k_printf("Multiboot mem_lower: %d\n", mboot->mem_lower);
  k_printf("Multiboot mem_upper: %d\n", mboot->mem_upper);
  k_printf("Multiboot mods_count: %d\n", mboot->mods_count);
  k_printf("Total system memory: %d Kb\n", mboot->mem_lower + mboot->mem_upper);
  /* list_root(root); */

  return 0x668;
}

void list_root(fs_node* root) {
  int i = 0;
  struct dirent* dir = NULL;
  while((dir = std_read_dir(root, i)) != NULL) {
    k_printf("Found file: %s\n", dir->name);
    fs_node* fsnode = std_find_dir(root, dir->name);
    if((fsnode->flags & 0x7) == FS_DIRECTORY)
      k_printf("\t(directory)\n");
    else {
      uint8 buf[256];
      uint32 sz = std_read_node(fsnode, 0, 256, buf);
      k_printf("\tsize: %d\n\tcontents: %s\n", sz, buf);
    }
    i++;
  }
}

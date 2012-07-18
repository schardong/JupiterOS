#ifndef __INITRD_H__
#define __INITRD_H__

#include <k_stdint.h>
#include <k_size_t.h>
#include <vfs.h>

struct _initrd_header {
  uint32 n_files;
};
typedef struct _initrd_header initrd_header;

struct _initrd_file_header {
  uint32 magic;
  uint8 name[64];
  uint32 offset;
  size_t size;
};
typedef struct _initrd_file_header initrd_file_header;

/**
 * k_init_initrd: Initializes the initrd and returns its filesystem node.
 * @loc: The address of the multiboot module that contains the initrd.
 * @returns: The initrd filesystem node.
 */
fs_node* k_init_initrd(uint32 loc);

#endif /* __INITRD_H__ */

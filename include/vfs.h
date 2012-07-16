#ifndef __KERNEL_VFS_H__
#define __KERNEL_VFS_H__

#include <k_stdint.h>
#include <k_size_t.h>
#include <k_stdbool.h>

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct dirent {
  uint8 name[128];
  uint32 ino;
};

struct _fs_node {
  uint8 name[128];
  uint32 mask;
  uint32 uid;
  uint32 gid;
  uint32 flags;
  uint32 inode;
  size_t size;
  void (*vfs_open_node)(struct _fs_node*, bool, bool);
  void (*vfs_close_node)(struct _fs_node*);
  uint32 (*vfs_read_node)(struct _fs_node*, uint32, uint32, uint8*);
  uint32 (*vfs_write_node)(struct _fs_node*, uint32, uint32, uint8*);
  struct dirent* (*vfs_read_dir)(struct _fs_node*, uint32);
  struct _fs_node* (*vfs_find_dir)(struct _fs_node*, uint8*);
  struct _fs_node* ptr;
};
typedef struct _fs_node fs_node;

void std_open_node(fs_node* node, bool read, bool write);
void std_close_node(fs_node* node);
uint32 std_read_node(fs_node* node, uint32 offset, uint32 size, uint8* buff);
uint32 std_write_node(fs_node* node, uint32 offset, uint32 size, uint8* buff);
struct dirent* std_read_dir(fs_node* node, uint32 idx);
fs_node* std_find_dir(fs_node* node, uint8* name);

#endif /* __KERNEL_VFS_H__ */

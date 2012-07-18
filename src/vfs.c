#include <vfs.h>
#include <k_null.h>

fs_node* vfs_root = NULL;

void std_open_node(fs_node* node, bool read, bool write) {
  if(node != NULL && node->vfs_open_node != NULL)
    node->vfs_open_node(node, read, write);
}

void std_close_node(fs_node* node) {
  if(node != NULL && node->vfs_close_node != NULL)
    node->vfs_close_node(node);
}

uint32 std_read_node(fs_node* node, uint32 offset, uint32 size, uint8* buff) {
  if(node != NULL && node->vfs_read_node != NULL)
    return node->vfs_read_node(node, offset, size, buff);
  return 0;
}

uint32 std_write_node(fs_node* node, uint32 offset, uint32 size, uint8* buff) {
  if(node != NULL && node->vfs_write_node != NULL)
    return node->vfs_write_node(node, offset, size, buff);
  return 0;
}

struct dirent* std_read_dir(fs_node* node, uint32 idx) {
  if(node != NULL && node->vfs_read_dir != NULL && (node->flags & 0x7) == FS_DIRECTORY)
    return node->vfs_read_dir(node, idx);
  return NULL;
}

fs_node* std_find_dir(fs_node* node, uint8* name) {
  if(node != NULL && node->vfs_find_dir != NULL && (node->flags & 0x7) == FS_DIRECTORY)
    return node->vfs_find_dir(node, name);
  return NULL;
}

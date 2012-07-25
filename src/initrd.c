#include <initrd.h>
#include <k_null.h>
#include <k_malloc.h>
#include <k_string.h>

initrd_header* header = NULL;
initrd_file_header* files = NULL;
fs_node* initrd_root = NULL;
fs_node* initrd_dev = NULL;
fs_node* root_nodes = NULL;
struct dirent dir;

uint32 initrd_read_node(fs_node* node, uint32 offset, uint32 size, uint8* buff);
struct dirent* initrd_read_dir(fs_node* node, uint32 idx);
fs_node* initrd_find_dir(fs_node* node, uint8* name);

fs_node* k_init_initrd(uint32 loc) {
  header = (initrd_header*) loc;
  files = (initrd_file_header*) (loc + sizeof(initrd_header));

  initrd_root = (fs_node*) k_malloc(sizeof(fs_node), false, NULL);
  strcpy((char*) initrd_root->name, "initrd");
  initrd_root->name[6] = '\0';
  initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->size = 0;
  initrd_root->flags = FS_DIRECTORY;
  initrd_root->impl = 0;
  initrd_root->vfs_open_node = NULL;
  initrd_root->vfs_close_node = NULL;
  initrd_root->vfs_read_node = NULL;
  initrd_root->vfs_write_node = NULL;
  initrd_root->vfs_read_dir = &initrd_read_dir;
  initrd_root->vfs_find_dir = &initrd_find_dir;
  initrd_root->ptr = NULL;

  initrd_dev = (fs_node*) k_malloc(sizeof(fs_node), false, NULL);
  strcpy((char*) initrd_dev->name, "dev");
  initrd_dev->name[3] = '\0';
  initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->size = 0;
  initrd_dev->flags = FS_DIRECTORY;
  initrd_dev->impl = 0;
  initrd_dev->vfs_open_node = NULL;
  initrd_dev->vfs_close_node = NULL;
  initrd_dev->vfs_read_node = NULL;
  initrd_dev->vfs_write_node = NULL;
  initrd_dev->vfs_read_dir = &initrd_read_dir;
  initrd_dev->vfs_find_dir = &initrd_find_dir;
  initrd_dev->ptr = NULL;

  root_nodes = (fs_node*) k_malloc(sizeof(fs_node) * header->n_files, false, NULL);

  uint32 i;
  for(i = 0; i < header->n_files; i++) {
    files[i].offset += loc + sizeof(initrd_file_header) * header->n_files;
    strcpy((char*) root_nodes[i].name, (const char*) files[i].name);
    root_nodes[i].uid = root_nodes[i].gid = root_nodes[i].mask = 0;
    root_nodes[i].size = files[i].size;
    root_nodes[i].inode = i;
    root_nodes[i].flags = FS_FILE;
    root_nodes[i].vfs_open_node = NULL;
    root_nodes[i].vfs_close_node = NULL;
    root_nodes[i].vfs_read_node = &initrd_read_node;
    root_nodes[i].vfs_write_node = NULL;
    root_nodes[i].vfs_read_dir = NULL;
    root_nodes[i].vfs_find_dir = NULL;
  }

  return initrd_root;
}

uint32 initrd_read_node(fs_node* node, uint32 offset, uint32 size, uint8* buff) {
  if(node == NULL || buff == NULL || offset > files[node->inode].size)
    return 0;
  if(offset + size > node->size)
    size = files[node->inode].size - offset;
  memcpy(buff, (uint8*) (files[node->inode].offset + offset), size);
  buff[size] = '\0';
  return size;
}

struct dirent* initrd_read_dir(fs_node* node, uint32 idx) {
  if(node == initrd_root && idx == 0) {
    strcpy((char*) dir.name, "dev");
    dir.name[3] = '\0';
    dir.ino = 0;
    return &dir;
  }
  if(idx - 1 >= header->n_files)
    return 0;
  strcpy((char*) dir.name, (const char*) root_nodes[idx - 1].name);
  dir.name[strlen((const char*) root_nodes[idx - 1].name)] = '\0';
  dir.ino = root_nodes[idx - 1].inode;
  return NULL;
}

fs_node* initrd_find_dir(fs_node* node, uint8* name) {
  if(node == initrd_root && !strcmp((const char*) node->name, "dev"))
    return initrd_dev;
  uint32 i;
  for(i = 0; i < header->n_files; i++)
    if(!strcmp((const char*) name, (const char*) root_nodes[i].name))
      return &root_nodes[i];
  return NULL;
}

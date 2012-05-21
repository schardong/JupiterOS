/**
 * File: multiboot.h
 * Author: Guilherme Gonçalves Schardong
 * Implementation of the multiboot struct.
 * File created on 08 January 2012, 18:35
 */

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400

struct multiboot
{
  unsigned int flags;
  unsigned int mem_lower;
  unsigned int mem_upper;
  unsigned int boot_device;
  unsigned int cmdline;
  unsigned int mods_count;
  unsigned int mods_addr;
  unsigned int num;
  unsigned int size;
  unsigned int addr;
  unsigned int shndx;
  unsigned int mmap_length;
  unsigned int mmap_addr;
  unsigned int drives_length;
  unsigned int drives_addr;
  unsigned int config_table;
  unsigned int boot_loader_name;
  unsigned int apm_table;
  unsigned int vbe_control_info;
  unsigned int vbe_mode_info;
  unsigned int vbe_mode;
  unsigned int vbe_interface_seg;
  unsigned int vbe_interface_off;
  unsigned int vbe_interface_len;
} __attribute__((packed));
typedef struct multiboot multiboot_t;

#endif /* __MULTIBOOT_H__ */

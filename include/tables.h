/**
 * File: tables.h
 * Author: Guilherme Gonçalves Schardong
 * Describe the GDT and IDT.
 * File created on 20 July 2011, 03:35
 */

#ifndef __KERNEL_TABLES_H__
#define __KERNEL_TABLES_H__

#include <stdint.h>

/**
 * struct descr_tab_ptr: Describes the pointer to a desctiptor table (GDT, IDT).
 */
struct descr_tab_ptr {
  uint16 size;
  uint32 base;
}__attribute__((packed));
typedef struct descr_tab_ptr dt_t;

/**
 * init_tables: Initializes the GDT and the IDT.
 */
void k_init_tables();

#endif /* __KERNEL_TABLES_H__ */

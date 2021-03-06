#ifndef __KERNEL_ORDERED_ARR_H__
#define __KERNEL_ORDERED_ARR_H__

#include <k_stdbool.h>
#include <k_stdint.h>
#include <k_size_t.h>
#include <k_null.h>

typedef void* type_t;

/**
 * The callback returns true if the first arg is less than the second
 * or true otherwise.
 */
typedef bool (*cb_less_than)(type_t, type_t);

struct _ordered_arr {
  type_t* arr;
  size_t size;
  size_t max_size;
  cb_less_than cb;
};
typedef struct _ordered_arr ordered_arr;

ordered_arr create_ordered_arr(size_t max_size, cb_less_than cb);
ordered_arr place_ordered_arr(void* addr, size_t max_size, cb_less_than cb);
void destroy_ordered_arr(ordered_arr* arr);
void remove_ordered_arr(ordered_arr* arr, uint32 idx);
type_t search_ordered_arr(ordered_arr* arr, uint32 idx);
void insert_ordered_arr(ordered_arr* arr, type_t item);
bool std_callback(type_t a, type_t b);
void print_arr(ordered_arr* arr);

#endif /* __KERNEL_ORDERED_ARR_H__ */

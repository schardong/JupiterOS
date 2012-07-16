#include <ordered_arr.h>
#include <k_stdio.h>
#include <k_string.h>
#include <k_malloc.h>

ordered_arr create_ordered_arr(size_t max_size, cb_less_than cb) {
  ordered_arr arr;
  arr.arr = (type_t*) k_malloc(sizeof(type_t) * max_size, false, NULL);
  memset(arr.arr, 0, sizeof(type_t) * max_size);
  arr.size = 0;
  arr.max_size = max_size;
  arr.cb = cb;
  return arr;
}

ordered_arr place_ordered_arr(void* addr, size_t max_size, cb_less_than cb) {
  ordered_arr arr;
  arr.arr = addr;
  memset(arr.arr, 0, sizeof(type_t) * max_size);
  arr.size = 0;
  arr.max_size = max_size;
  arr.cb = cb;
  return arr;
}

void destroy_ordered_arr(ordered_arr* arr) {
  k_free(arr->arr);
  k_free(arr);
}

void remove_ordered_arr(ordered_arr* arr, uint32 idx) {
  while(idx < arr->size) {
    arr->arr[idx] = arr->arr[idx];
    idx++;
  }
  arr->size--;
}

type_t search_ordered_arr(ordered_arr* arr, uint32 idx) {
  if(arr->size < idx)
    return NULL;
  return arr->arr[idx];
}

void insert_ordered_arr(ordered_arr* arr, type_t item) {
  if(arr->cb == NULL)
    return;
  uint32 it = 0;
  while(it < arr->size && arr->cb(arr->arr[it], item) == true)
    it++;
  if(it == arr->size)
    arr->arr[arr->size++] = item;
  else {
    type_t tmp = arr->arr[it];
    arr->arr[it] = item;
    while(it < arr->size) {
      it++;
      type_t tmp2 = arr->arr[it];
      arr->arr[it] = tmp;
      tmp = tmp2;
    }
    arr->size++;
  }
}

bool std_callback(type_t a, type_t b) {
  return (a < b)? true:false;
}

void print_arr(ordered_arr* arr) {
  if(arr == NULL) {
    k_printf("Invalid array. Is null\n");
    return;
  }
  uint32 i;
  for(i = 0; i < arr->size; i++)
    k_printf("%d ", arr->arr[i]);
  k_printf("\nsize = %d\t max_size = %d\n", arr->size, arr->max_size);
}

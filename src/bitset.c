/**
 * File: bitset.c
 * Author: Guilherme Gonçalves Schardong
 * Implementation of the bitset structure and related functions.
 * File created on 11 January 2012, 22:14
 */

#include <bitset.h>
#include <k_malloc.h>
#include <k_string.h>
#include <k_null.h>

bitset_t* create_bitset(unsigned int num_bytes) {
  bitset_t* bit = (bitset_t*) k_malloc(sizeof(bitset_t), 0, NULL);
  bit->set = (unsigned char*) k_malloc(sizeof(unsigned char) * num_bytes, 0, NULL);
  bit->num_bytes = num_bytes;
  memset(bit->set, 0, sizeof(unsigned char) * num_bytes);
  return bit;
}

void set_bit(bitset_t* bitset, unsigned int position) {
  if(bitset == NULL)
    return;
  bitset->set[BYTE(position)] |= (1 << BIT(position));
}

void clear_bit(bitset_t* bitset, unsigned int position) {
  if(bitset == NULL)
    return;
  bitset->set[BYTE(position)] &= ~(1 << BIT(position));
}

int test_bit(bitset_t* bitset, unsigned int position) {
  if(bitset == NULL)
    return -1;
  return bitset->set[BYTE(position)] >> BIT(position);
}

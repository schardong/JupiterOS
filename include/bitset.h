/**
 * File: bitset.h
 * Author: Guilherme Gonçalves Schardong
 * Definition of the bitset structure and related functions.
 * File created on 11 January 2012, 22:14
 */
 
#ifndef __BITSET_H__
#define __BITSET_H__

#include <k_stdint.h>
#include <k_stdbool.h>

/**
 * BYTE - Returns the desired byte on the bitset.
 */
#define BYTE(a) (a / (8 * sizeof(uint8)))

/**
 * BIT - Returns the desired bit on the bitset.
 */
#define BIT(a) (a % (8 * sizeof(uint8)))

struct bitset {
  uint8* set;
  uint32 num_bytes;
};
typedef struct bitset bitset_t;

/**
 * create_bitset - Creates a bitset and returns it to the user.
 * @num_bytes: The number of bytes in the bitset.
 * @returns: A pointer to the allocated bitset.
 */
bitset_t* create_bitset(uint32 num_bytes);

/**
 * set_bit - Sets a bit in the bitset.
 * @bitset: The target bitset.
 * @position: The index of the bit in the bitset.
 */
void set_bit(bitset_t* bitset, uint32 position);

/**
 * clear_bit - Clears a bit in the bitset.
 * @bitset: The target bitset.
 * @position: The index of the bit in the bitset.
 */
void clear_bit(bitset_t* bitset, uint32 position);

/**
 * test_bit - Tests the value of a bit in the bitset.
 * @bitset: The target bitset.
 * @position: The index of the bit in the bitset.
 * @returns: true if the bit is set or false otherwise.
 */
bool test_bit(bitset_t* bitset, uint32 position);

#endif /* __BITSET_H__ */

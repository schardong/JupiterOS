/**
 * File: string.h
 * Author: Guilherme Gonçalves Schardong
 * Defines the basic libcc string functions.
 * File created on 28 June 2011, 09:44
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <size_t.h>

/**
 * bcopy: Copies the content from an region of memory to another.
 * The regions may overlap.
 * @src: The source.
 * @dest: The destination
 * @count: How many bytes will be copied.
 */
void bcopy(const void* src, void* dest, size_t count);

/**
 * bzero: Fills a region of memory with zeroes.
 * @dest: The rgion of memory to be filled.
 * @count: How many bytes will be filled.
 */
void bzero(void* dest, size_t count);

/**
 * memcpy: Copies the content from an region of memory to another.
 * @dest: The destination.
 * @src: The source.
 * @count: How many bytes will be copied.
 * @returns: A pointer to the destination memory region.
 */
void* memcpy(void* dest, const void* src, size_t count);

/**
 * memset: Sets a whole region of memory to a certain value.
 * @dest: The region of memory to be set.
 * @val: The value to fill the memory region.
 * @count: How many bytes will be filled.
 * @returns: The pointer to the memory region.
 */
void* memset(void* dest, char val, size_t count);

/**
 * memcmp: Compares two separate regions of memory.
 * @cs: The first region.
 * @ct: The second region.
 * @count: How many bytes will be compared.
 * @returns: A number less than, equal to or greater than 0 if the
 * first region is less than, equal to or greater than the second
 * region.
 */
int memcmp(const void* cs, const void* ct, size_t count);

/**
 * strcpy: Copies the content of one string to another.
 * @dest: The destination string.
 * @src: The source string.
 * @returns: The destination string.
 */
char* strcpy(char* dest, const char* src);

/**
 * strcmp: Compares two strings and returns if they are equal.
 * @s1: The first string.
 * @s2: The second string.
 * @returns: A number less than, equal to or larger than 0 if s1 is
 * found to be less than, equal to or larger than s2 respectively.
 */
int strcmp(const char* s1, const char* s2);

/**
 * strlen: Calculates the length of a given string.
 * @s: The target string.
 * @returns: The length of the string.
 */
size_t strlen(const char* s);

#endif /* __STRING_H__ */

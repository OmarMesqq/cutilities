#ifndef CUTE_MEMORY_H
#define CUTE_MEMORY_H

#include <stdio.h>
#include <string.h>

/**
 * Returns 1 if machine is Little Endian,
 * 0 if Big Endian (fallback).
 */
int is_little(void);

/**
 * Does a byte-by-byte dump of the value pointed by `p`
 * showing `<address> - <value of byte>`
 * 
 * The amount of bytes to dump is ruled by `n` (usually
 * the `sizeof` of the data type)
 */
void dump(const void* p, int n);

/**
 * Dumps `n` bytes of the value pointed by `p`
 * displaying the high and low nibbles of that byte
 * and their binary representation below.
 * 
 * Example:
```
  04    0d
0100  1101
```
 */
void dump_nibbles(const void* p, int n);

/**
 * Dumps the eight bits that represent the
 * byte `x` in a single line, separating
 * bits of the high nibble from the low one
 * with a whitespace.
 */
void dump_bits(unsigned char x);

/**
 * Does a character-by-character dump of a string (as character, decimal, and hex).
 */
void dump_string(const char* s);

/**
 * Writes a signed integer's bytes in Little Endian ordering
 * in a buffer at the offset pointed by `pos`.
 *
 * @param buf byte array
 * @param pos pointer to an integer marking the desired offset to write at
 * @param integer whole number whose bytes will be written
 *
 * SIDE-EFFECT: increments `pos` as the buffer is traversed
 */
void write_integer_le(unsigned char buf[], int* pos, int integer);

#endif

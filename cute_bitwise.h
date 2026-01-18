#ifndef CUTE_BITWISE_H
#define CUTE_BITWISE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Classic swap implementation with XOR.
 * Nowadays this is pendantic and a little useless
 * for most cases, as CPUs are optimized for swapping elements.
 * This is merely an educational tool implemented following
 * the theory at
 * https://www.inf.puc-rio.br/~inf1018/docs/bitwise.pdf
 */
void inplace_swap(int* x, int* y);

/**
 * Returns 1 if count of ON bits in 
 * the number `x` is odd. Otherwise,
 * returns 0.
 */
int odd_ones(unsigned int x);

/**
 * Swaps the high and low nibbles of a byte
 * (8 bits).
 */
unsigned char switch_byte(unsigned char x);

/**
 * Does a **circular left shift** on
 * byte `x` by `n` bits.
 */
unsigned char rotate_left(unsigned char x, int n);

/**
 * Extracts the value of the byte at index `bytenum`
 * on the whole number `word` using bitwise math.
 * Returns it implicitly cast to 32-bit signed integer.
 */
int xbyte_math(unsigned int word, int bytenum);

/**
 * Extracts the value of the byte at index `bytenum`
 * on the whole number `word` leveraging unions
 * and Little Endian memory layout.
 * 
 * Returns the value implicitly cast to 32-bit signed integer.
 * 
 * WARNING: Portability note: this will only work
 * on Little Endian machines.
 */
int xbyte_endianess(unsigned int word, int bytenum);

#endif

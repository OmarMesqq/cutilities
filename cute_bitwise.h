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
 * 
 */
void inplace_swap(int* x, int* y);

int odd_ones(unsigned int x);

unsigned char switch_byte(unsigned char x);

/**
 * Circular left shift
 */
unsigned char rotate_left(unsigned char x, int n);

/**
 * extrai byte indicado e retorna valor
 * inteiro correspondente (32 bits) com sinal
 */
int xbyte(unsigned int word, int bytenum);

int xbyte2(unsigned int word, int bytenum);

#endif

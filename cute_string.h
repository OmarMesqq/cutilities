#ifndef CUTE_STRING_H
#define CUTE_STRING_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int stoi_1(char* s, int base);

/**
 * Base 36 é a máxima que podemos
 * ter com esta quantidade de simbolos
 */
int stoi_2(char* s, int b);

void itos(char* s, int num, int base);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string.
 */
char* ultos(unsigned long ul, unsigned long width);

/**
 * Converts the null-terminated string to an integer in a single pass.
 *
 * Runs in O(n)
 *
 * WARNING: Doesn't correctly handle broken inputs such as those with space, letters
 * and overflowing integers
 *
 * @param s null-terminated string representing a whole number (`int`)
 */
int stoi(const char* s);

#endif

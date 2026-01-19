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

void itos(char* s, int num, int base);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string.
 */
char* ultos(unsigned long ul, unsigned long width);

/**
 * Takes an Unix absolute or relative file path and
 * returns the its basename as a heap allocated string.
 *
 * This function truncates the returned string to `maxBaseNameLength - 1` characters
 * of the basename as it has to include the null terminator.
 *
 * Runs in O(N^2)
 *
 * @param filepath string representing a file's path
 * @param maxBaseNameLength maximal size for basename string INCLUDING the null terminator
 */
char* get_basename(const char* filepath, unsigned maxBaseNameLength);

/**
 * Trims leading spaces (' ')/ 32 (dec)/ 0x20 (hex).
 *
 * Runs in O(n)
 *
 * SIDE-EFFECT: modifies `line` in-place
 */
void trim_leading_spaces(char* line);

#endif

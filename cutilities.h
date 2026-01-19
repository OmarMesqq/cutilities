#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>
#include <stdlib.h>

#include "cute_bitwise.h"
#include "cute_floating_point.h"
#include "cute_memory.h"
#include "cute_string.h"

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
int string_to_int(const char* s);

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

/**
 * Returns the "width" (amount of digits) of a
 * non-negative whole number `ul`.
 */
unsigned long get_number_width(unsigned long ul);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string.
 */
char* utos(unsigned long ul, unsigned long width);

/**
 * On success, returns the size in bytes of a file in persistent storage.
 * On failure, `-1`
 *
 * SIDE-EFFECT: resets the file position indicator to the beginning.
 *
 * @param f ALREADY OPEN file stream in BINARY READ mode
 */
long get_filesize(FILE* f);

#endif

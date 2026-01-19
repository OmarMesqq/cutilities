#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>
#include <stdlib.h>

#include "cute_bitwise.h"
#include "cute_floating_point.h"
#include "cute_memory.h"
#include "cute_string.h"

/**
 * TODO: move this to `cute_string`
 * 
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
 * On success, returns the size in bytes of a file in persistent storage.
 * On failure, `-1`
 *
 * SIDE-EFFECT: resets the file position indicator to the beginning.
 *
 * @param f ALREADY OPEN file stream in BINARY READ mode
 */
long get_filesize(FILE* f);

#endif

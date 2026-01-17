#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>

/**
 * Takes an Unix absolute or relative file path and
 * returns the its basename as a heap allocated string.
 * 
 * This function truncates the returned string to `maxBaseNameLength - 1` characters
 * of the basename as it has to include the null terminator.
 * 
 * Currently, this runs at `O(N^2)`
 * 
 * @param filepath string representing a file's path
 * @param maxBaseNameLength maximal size for basename string INCLUDING the null terminator
 */
char* get_basename(const char* filepath, unsigned maxBaseNameLength);

/**
 * Trims leading spaces (' ')/ 32 (dec)/ 0x20 (hex),
 * modifying `lineBuffer` in-place.
 * Runs in O(n)
 */
void trim_leading_spaces(char* lineBuffer);

/**
 * Prints the entire string `s`, followed by a character-by-character
 * dump of its contents (as character, decimal, and hex).
 */
void dump_string(char* s);

/**
 * Converts the null-terminated string `str` to an integer.
 * Runs in O(n) - single pass.
 * Doesn't correctly handle broken inputs such as those with space, letters
 * and overflowing integers
 */
int string_to_int(char* str);

/**
 * Writes in the buffer `code` at offset `pos` a base 10 signed `integer`
 * (32 bits on x86-64) in Little Endian hexadecimal.
 * Used for immediate values and jump offsets.
 * SIDE-EFFECT: modifies `pos` as the buffer is traversed
 */
void write_integer_le(unsigned char code[], int* pos, int integer);

/**
 * Returns the "width" (amount of digits) of a
 * non-negative whole number `ul`.
 */
unsigned long get_number_width(unsigned long ul);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string. 
 */
char* numtoi(unsigned long ul, unsigned long width);

long get_filesize(FILE* f);

#endif

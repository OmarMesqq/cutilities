#ifndef CUTE_MEMORY_H
#define CUTE_MEMORY_H

#include <stdio.h>
#include <string.h>

/**
 * Returns 1 if machine is Little Endian,
 * 0 if Big Endian (fallback).
 */
int is_little(void);

void dump(const void* p, int n);

void dump_nibbles(const void* p, int n);

void dump_bits(unsigned char x);

/**
 * Does a character-by-character dump of a string (as character, decimal, and hex).
 */
void dump_string(const char* s);

#endif

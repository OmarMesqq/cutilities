#ifndef CUTE_MEMORY_H
#define CUTE_MEMORY_H

#include <stdio.h>
#include <string.h>

int is_little(void);

void dump(const void* p, int n);

void print_bytes(const void* p, int n);

void print_byte(unsigned char x);

/**
 * Does a character-by-character dump of a string (as character, decimal, and hex).
 */
void dump_string(const char* s);

#endif

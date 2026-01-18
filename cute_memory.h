#ifndef CUTE_MEMORY_H
#define CUTE_MEMORY_H

#include <stdio.h>

int is_little(void);
void dump(const void* p, int n);
void print_bytes(const void* p, int n);
void print_byte(unsigned char x);

#endif

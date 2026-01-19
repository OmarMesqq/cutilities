#ifndef CUTE_STRING_H
#define CUTE_STRING_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int stonum_1(char* s, int base);

/**
 * Base 36 é a máxima que podemos
 * ter com esta quantidade de simbolos
 */
int stonum_2(char* s, int b);

void num2string(char* s, int num, int base);

/**
 * Takes a non-negative whole number `ul` and its `width`
 * and returns the former as a heap-allocated string.
 */
char* utos(unsigned long ul, unsigned long width);

#endif

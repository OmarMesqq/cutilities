#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>

char* get_basename(const char* filepath, unsigned maxBaseNameLength);
long get_filesize(FILE* f);
void trimLeadingSpaces(char* lineBuffer);
void dumpString(char* s);
int stringToInt(char* str);
void emitIntegerInHex(unsigned char code[], int* pos, int integer);
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


#endif

#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>

char* get_basename(const char* filepath, unsigned maxBaseNameLength);
long get_filesize(FILE* f);
void trimLeadingSpaces(char* lineBuffer);
void dumpString(char* s);
int stringToInt(char* str);
void emitIntegerInHex(unsigned char code[], int* pos, int integer);

#endif

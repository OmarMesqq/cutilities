#ifndef CUTILITIES_H
#define CUTILITIES_H

#include <stdio.h>

char* get_basename(const char* filepath, unsigned maxBaseNameLength);
long get_filesize(FILE* f);

#endif

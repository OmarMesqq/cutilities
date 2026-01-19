#ifndef CUTE_IO_H
#define CUTE_IO_H
#include <stdio.h>

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

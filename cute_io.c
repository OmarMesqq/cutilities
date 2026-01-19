#include "cute_io.h"

long get_filesize(FILE* f) {
  fseek(f, 0, SEEK_END);
  long length = ftell(f);
  rewind(f);

  if (length == -1L) {
    fprintf(stderr, "get_filesize: failed to read file size using 'ftell'\n");
    return -1;
  }
  return length;
}
#include "cutilities.h"

char* get_basename(const char* filepath, unsigned maxBaseNameLength) {
  if (!filepath) {
    fprintf(stderr, "get_basename: no filepath provided to extract a file basename!\n");
    return NULL;
  }
  if (maxBaseNameLength == 0) {
    fprintf(stderr, "get_basename: the maximum basename length cannot be zero!\n");
    return NULL;
  }
  char* basename = calloc(maxBaseNameLength, sizeof(char));
  if (!basename) {
    fprintf(stderr, "get_basename: failed to create array for basename\n");
    return NULL;
  }

  unsigned int i = 0;
  const char* ptr = filepath;

  while (*ptr != '\0') {
    char current = *ptr;
    char next = *(ptr + 1);

    if (current == '/') {
      /**
       * LOOK-AHEAD:
       * Check if the current slash is at the end of the string (trailing slash)
       * or followed by another slash.
       */
      if ((next == '\0') || (next == '/')) {
        /**
         * Edge case: The Root Path ("/")
         * If the buffer is empty, this slash is actually the basename.
         */
        if (basename[0] == 0) {
          basename[0] = '/';
          ++i;
        }

        /**
         * Otherwise, it's just a trailing/redundant slash.
         * Skip it so we don't overwrite the valid basename we already found.
         */
        ptr++;
        continue;
      }

      /**
       * We reset `basename`
       * with `i = 0` , move to the next char (`ptr++`),
       * and skip the current iteration as to NOT include
       * the current slash in the buffer (`continue`)
       */
      i = 0;
      ptr++;
      continue;
    }

    if (i >= (maxBaseNameLength - 1)) {
      /**
       * The folder names may be larger than the user provided
       * `maxBaseNameLength`. If that's the case, I gotta
       * check if we are truly at the string's end and the
       * basename shall be truncated (happy path) OR
       * if we are in an intermediate folder
       */
      const char* remainingStr = ptr;
      unsigned char isStrOver = 1;  // assume the string is indeed over
      for (; *remainingStr != '\0'; remainingStr++) {
        if (*remainingStr == '/') isStrOver = 0;
      }

      if (isStrOver) {
        fprintf(stderr, "get_basename: basename buffer exceeded, truncating string\n");
        break;
      }
      // string isn't over, discard whatever was parsed until basename is found
      i = 0;
    }

    basename[i] = current;
    ++i;
    ptr++;
  }

  basename[i] = '\0';
  return basename;
}

void trim_leading_spaces(char* line) {
  char* p = line;
  // early return if string doesn't have leading whitespace
  if (*p != ' ') {
    return;
  }

  // count spaces
  unsigned spaces = 0;
  while (*p == ' ') {
    spaces++;
    p++;
  }

  char* aux = p;  // helper pointer with whitespace already consumed
  unsigned i = 0;
  while (*aux != '\0') {
    // shifts the entire string to beginning, eliminating spaces
    line[i] = line[spaces + i];
    i++;
    aux++;
  }

  // "discard" remaining bytes at end of string
  line[i] = '\0';
}

void write_integer_le(unsigned char buf[], int* pos, int integer) {
  buf[*pos] = integer & 0xFF;
  (*pos)++;
  buf[*pos] = (integer >> 8) & 0xFF;
  (*pos)++;
  buf[*pos] = (integer >> 16) & 0xFF;
  (*pos)++;
  buf[*pos] = (integer >> 24) & 0xFF;
  (*pos)++;
}

unsigned long get_number_width(unsigned long ul) {
  unsigned long width = 0;
  unsigned long q = 0;   // quotient
  unsigned long d = ul;  // dividend: starts as the given number

  /**
   * Every whole number >= 0, has at least one digit,
   * so a `do...while` seems appropriate as
   * the width should be 1 at the minimum.
   *
   * Loop termination condition is whether the dividend reaches zero.
   * As such, right after considering that a number has at least one digit (`++width`),
   * we get the quotient of the first or previous number by 10, and set
   * the next dividend as it.
   *
   * The number 10 has this cool feature that allows breaking down the number in its digits
   * as we count in decimal. To get a number's width we simply count how many iterations
   * it takes to "walk through" all the digits - eventually we'll get a single digit
   * number that divided by 10 yields 0, thus breaking the loop.
   */
  do {
    ++width;
    q = d / 10;
    d = q;
  } while (d != 0);

  return width;
}

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

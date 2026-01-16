#include "cutilities.h"

#include <stdlib.h>

char* get_basename(const char* filepath, unsigned maxBaseNameLength) {
  if (!filepath) {
    fprintf(stderr, "get_basename: no filepath provided to extract a file basename!\n");
    return NULL;
  }
  char* basename = malloc(maxBaseNameLength * sizeof(char));
  if (!basename) {
    fprintf(stderr, "get_basename: failed to create array for basename\n");
    return NULL;
  }

  unsigned int i = 0;
  char* ptr = (char*)filepath;
  while (*ptr != '\0') {
    if (*ptr == '/') {
      i = 0;
      ptr++;
      continue;
    }
    if (i >= maxBaseNameLength) {
      printf("get_basename: basename buffer exceeded, truncating string\n");
      break;
    }
    basename[i] = *ptr;
    ++i;
    ptr++;
  }
  basename[i] = '\0';
  return basename;
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

/**
 * Trims leading spaces (' ')/ 32 (dec)/ 0x20 (hex),
 * modifying `lineBuffer` in-place.
 * Runs in O(n)
 */
void trimLeadingSpaces(char* lineBuffer) {
  char* p = lineBuffer;
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
#ifdef DEBUG
    printf("trimLeadingSpaces: setting lineBuffer[i = %d] (%c) to lineBuffer[spaces + i = %d] (%c)\n", i, lineBuffer[i], spaces + i, lineBuffer[spaces + i]);
#endif
    // shifts the entire string to beginning, eliminating spaces
    lineBuffer[i] = lineBuffer[spaces + i];
    i++;
    aux++;
  }

  // "discard" remaining bytes at end of string
  lineBuffer[i] = '\0';
}

/**
 * Prints the entire string `s`, followed by a character-by-character
 * dump of its contents (as character, decimal, and hex).
 */
void dumpString(char* s) {
  printf("%s", s);
  printf("dumpString: dumping string above...\n");
  char* p = s;
  while (*p != '\0') {
    printf("char: %c, %d (dec), %02x (hex)\n", *p, *p, *p);
    p++;
  }
  printf("\n");
}

/**
 * Converts the null-terminated string `str` to an integer.
 * Runs in O(n) - single pass.
 * Doesn't correctly handle broken inputs such as those with space, letters
 * and overflowing integers
 */
int stringToInt(char* str) {
  int num = 0;
  int digit = 0;
  int isNegative = 0;
  // is first char a minus sign?
  if (*str == '-') {
    isNegative = 1;
    str++;
  }
  while (*str != '\0') {
    // subtract the value of the digit char from 0 in ASCII table, getting its true value
    digit = *str - '0';
    // each new digit "adds" another power of 10 to the overall number
    num *= 10;
    num += digit;
    str++;
  }
  if (isNegative) {
    num *= -1;
  }

  return num;
}

/**
 * Writes in the buffer `code` at offset `pos` a base 10 signed `integer`
 * (32 bits on x86-64) in Little Endian hexadecimal.
 * Used for immediate values and jump offsets.
 * SIDE-EFFECT: modifies `pos` as the buffer is traversed
 */
void emitIntegerInHex(unsigned char code[], int* pos, int integer) {
  code[*pos] = integer & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 8) & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 16) & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 24) & 0xFF;
  (*pos)++;
}
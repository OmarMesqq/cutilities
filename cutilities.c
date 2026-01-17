#include "cutilities.h"

#include <stdlib.h>

char* get_basename(const char* filepath, unsigned maxBaseNameLength) {
  if (!filepath) {
    fprintf(stderr, "get_basename: no filepath provided to extract a file basename!\n");
    return NULL;
  }
  if (maxBaseNameLength == 0) {
    fprintf(stderr, "get_basename: the maximum basename length cannot be zero!\n");
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
      char next = *(ptr + 1);  // look-ahead
      if (next == '\0') {
        ptr++;
        continue;
      }
      i = 0;
      ptr++;
      continue;
    }
    if (i >= maxBaseNameLength) {
      fprintf(stderr, "get_basename: basename buffer exceeded, truncating string\n");
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
void trim_leading_spaces(char* lineBuffer) {
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
void dump_string(char* s) {
  printf("%s", s);
  printf("dump_string: dumping string above...\n");
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
int string_to_int(char* str) {
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
void write_integer_le(unsigned char code[], int* pos, int integer) {
  code[*pos] = integer & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 8) & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 16) & 0xFF;
  (*pos)++;
  code[*pos] = (integer >> 24) & 0xFF;
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

char* numtoi(unsigned long ul, unsigned long width) {
  unsigned long d = ul;  // dividend: starts as the given number
  unsigned long r = 0;   // remainder

  char* str = (char*)malloc((width + 1) * sizeof(char));
  if (!str) {
    fprintf(stderr, "numtoi: failed to allocate string to represent number!\n");
    return NULL;
  }

  int i = width - 1;

  /**
   * Once again, every number has at least one digit, so do...while is the way to go.
   * Loop terminates when number is entirely "chopped down" i.e dividend is zero.
   *
   * Using the fact that numbers are represented in base 10, we extract the individual digits
   * by getting the remainders of divisions of the first/previous dividends by 10.
   *
   * The digits are obtained right to left (least to most significant). Therefore,
   * we write to this string in the reverse order of the divisions.
   */
  do {
    r = d % 10;
    str[i] = r + '0';  // get higher digits as chars by summing the value of the digit itself to zero's ASCII
    --i;               // start at the string's end, keep traversing backwards
    d = d / 10;
  } while (d != 0);

  str[width] = '\0';
  return str;
}

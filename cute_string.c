#include "cute_string.h"

static unsigned long get_number_width(unsigned long ul);

int stoi_1(char* s, int base) {
  int a = 0;
  for (; *s; s++) {
    if (isdigit(*s))
      a = a * base + (*s - '0');
    else if ((*s >= 'A') && (*s < (base - 10 + 'A')))
      a = a * base + ((*s - 'A') + 10);
    else if ((*s >= 'a') && (*s < (base - 10 + 'a')))
      a = a * base + ((*s - 'a') + 10);
    else {
      printf("pane: numero invalido! \n");
      exit(1);
    }
  }
  return a;
}

int stoi_2(char* s, int b) {
  int a = 0;
  for (; *s; s++) {
    if (isdigit(*s)) {
      a = a * b + (*s - '0');
    } else {
      // somamos 10 porque A vale 10, B 11, ... e seguimos a sequencia a partir deste numero
      a = a * b + 10 + (*s - 'a');
    }
  }
  return a;
}

int stoi(const char* s) {
  int isNegative = 0;
  // is first char a minus sign?
  if (*s == '-') {
    isNegative = 1;
    s++;
  }

  int num = 0;
  int digit = 0;

  while (*s != '\0') {
    // subtract the value of the digit char from 0 in ASCII table, getting its true value
    digit = *s - '0';
    // each new digit "adds" another power of 10 to the overall number
    num *= 10;
    num += digit;
    s++;
  }

  if (isNegative) {
    num *= -1;
  }

  return num;
}

void itos(char* s, int num, int base) {
  if (base == 10) {
    int tempNum = num;
    int i = 0;
    while ((tempNum % 10) != 0) {
      tempNum = tempNum / 10;
      i++;
    }
    printf("num %d has %d digitis.\n", num, i);
    int j = 0;
    tempNum = num;
    while (j < i) {
      int d = tempNum % 10;
      tempNum = tempNum / 10;
      // add digit to 48 ('0' in ASCII table) to get the corresponding char
      s[i - j - 1] = d + 48;
      j++;
    }
    s[i] = '\0';
  }
}

char* ultos(unsigned long ul, unsigned long width) {
  unsigned long d = ul;  // dividend: starts as the given number
  unsigned long r = 0;   // remainder

  char* str = (char*)malloc((width + 1) * sizeof(char));
  if (!str) {
    fprintf(stderr, "ultos: failed to allocate string to represent number!\n");
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

/**
 * TODO: turn this static
 * Returns the "width" (amount of digits) of a
 * non-negative whole number `ul`.
 */
static unsigned long get_number_width(unsigned long ul) {
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
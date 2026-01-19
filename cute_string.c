#include "cute_string.h"

int stonum_1(char* s, int base) {
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

int stonum_2(char* s, int b) {
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

void num2string(char* s, int num, int base) {
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

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

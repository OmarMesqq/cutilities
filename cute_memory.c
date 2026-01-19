#include "cute_memory.h"

int is_little(void) {
  unsigned short s = 43981;  // 0xABCD
  const unsigned char* ps = (const unsigned char*)&s;

  if (*ps == 0xCD) {
    // least significant byte comes first -> Little Endian
    return 1;
  }

  // Big Endian
  return 0;
}

void dump(const void* p, int n) {
  const unsigned char* p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

void dump_nibbles(const void* p, int n) {
  const unsigned char* p1 = p;

  for (int i = 0; i < n; i++) {
    // Print nibbles
    printf(" %02x   %02x\n", ((*p1 >> 4) & 0x0F), (*p1 & 0x0F));

    // Print bits of that nibble
    for (int j = 7; j >= 0; j--) {
      if (j == 3) printf(" ");
      printf("%d", (*p1 >> j) & 1);
    }
    p1++;
    printf("\n\n");
  }
}

void dump_bits(unsigned char x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
    if (i == 4) printf(" ");
  }
  printf("\n");
}

void dump_string(const char* s) {
  // Left align text for readability
  printf("%-10s | %-7s | %-11s\n", "CHARACTER", "DECIMAL", "HEXADECIMAL");
  printf("-------------------------------------\n");

  while (*s != '\0') {
    char display_str[8];

    switch (*s) {
      case '\n':
        strcpy(display_str, "\\n");
        break;
      case '\t':
        strcpy(display_str, "\\t");
        break;
      case '\r':
        strcpy(display_str, "\\r");
        break;
      case '\b':
        strcpy(display_str, "\\b");
        break;
      case ' ':
        strcpy(display_str, "' '");
        break;
      default:
        sprintf(display_str, "%c", *s);
        break;
    }

    // %-10s : Left-align string within 10 spaces
    // %7d   : Right-align integer within 7 spaces
    // %02x  : Print at least 2 digits of hex (e.g., 0A instead of A)
    printf("%-10s | %7d | 0x%x\n", display_str, (unsigned char)*s, (unsigned char)*s);

    s++;
  }
  printf("\n");
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

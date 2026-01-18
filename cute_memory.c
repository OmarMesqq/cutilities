#include "cute_memory.h"

int is_little(void) {
  unsigned short s = 256;  // 0x0100
  unsigned char* ptr = (unsigned char*)&s;

  // least significant byte first?
  if (ptr[0] == 0x00) {
    // Little Endian
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

void print_bytes(const void* p, int n) {
  const unsigned char* p1 = p;

  for (int i = 0; i < n; i++) {
    // High nibble: shift right by 4 (since its unsigned, it safely does logical shift instead of arithmetic one)
    // Low nibble: mask with 0x0F.
    printf(" %02x   %02x  \n", *p1 >> 4, *p1 & 0x0F);
    for (int i = 7; i >= 0; i--) {
      if (i == 3) {
        printf(" ");
      }
      printf("%d", (*p1 >> i) & 1);
    }
    p1++;
    printf("\n\n");
  }
}

void print_byte(unsigned char x) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (x >> i) & 1);
    if (i == 4) printf(" ");
  }
  printf("\n");
}

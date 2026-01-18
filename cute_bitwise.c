#include "cute_bitwise.h"

void inplace_swap(int* x, int* y) {
  *x = *x ^ *y;
  *y = *x ^ *y;
  *x = *x ^ *y;
}

int odd_ones(unsigned int x) {
  unsigned parity = 0;
  for (int i = 31; i >= 0; i--) {
    if ((x >> i & 1) == 1) {
      // tracks parity of ON bits using XOR as a "light switch"
      parity ^= 1;
    }
  }

  if (parity == 0) {
    // even
    return 0;
  }
  // odd
  return 1;
}

unsigned char switch_byte(unsigned char x) {
  return ((x << 4 ) & 0xF0) | ((x >> 4) & 0x0F);
}

unsigned char rotate_left(unsigned char x, int n) {
  unsigned char c1, c2;
  c1 = x << n;
  c2 = x >> (8 - n);
  return c1 | c2;
}

int xbyte_math(unsigned int word, int bytenum) {
  signed char byte = 0;  // "packed" values are signed and are at most 1-byte wide
  unsigned int mask = 0x000000FF;

  switch (bytenum) {
    case 0:
      byte = word & mask;
      break;
    case 1:
      word = word >> 8;
      byte = word & mask;
      break;
    case 2:
      word = word >> 16;
      byte = word & mask;
      break;
    case 3:
      word = word >> 24;
      byte = word & mask;
      break;
    default:
      fprintf(stderr, "Valid indexes for bytes of an integer are 0 through 3 only. Got: %d\n", bytenum);
      exit(1);
  }
  printf("%08x  %d\n", byte, byte);
  return byte;
}

int xbyte_endianess(unsigned int word, int bytenum) {
  /**
   * Anonymous union for extracting
   * bytes from an unsigned integer
   */
  typedef union {
    unsigned i;
    char v[4];
  } PackedUnion;

  signed char byte = 0;  // "packed" values are signed and are at most 1-byte wide
  PackedUnion pu;
  pu.i = word;

  switch (bytenum) {
    case 0:
      byte = pu.v[0];
      break;
    case 1:
      byte = pu.v[1];
      break;
    case 2:
      byte = pu.v[2];
      break;
    case 3:
      byte = pu.v[3];
      break;
    default:
      fprintf(stderr, "Valid indexes for bytes of an integer are 0 through 3 only. Got: %d\n", bytenum);
      exit(1);
  }
  printf("%08x  %d\n", byte, byte);
  return byte;
}

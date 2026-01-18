#include "cute_bitwise.h"

void inplace_swap(int* x, int* y) {
  *x = *x ^ *y;
  *y = *x ^ *y;
  *x = *x ^ *y;
}

int odd_ones(unsigned int x) {
  unsigned bitAccumulator = 0;
  for (int i = 31; i >= 0; i--) {
    if ((x >> i & 1) == 1) {
      // rastreia a paridade da quantidade de bits 1 usando XOR como "liga-desliga"
      bitAccumulator ^= 1;
    }
  }

  if (bitAccumulator == 0) {
    // x tem quantidade par de bits 1
    return 0;
  }
  // x tem quantidade impar de bits 1
  return 1;
}

unsigned char switch_byte(unsigned char x) {
  unsigned char msHalf, lsHalf;
  // empurra os 4 bits mais significativos (msHalf) para os 4 inferiores
  msHalf = x >> 4;
  // zera os 4 bits superiores e empurra os menos significativos (lsHalf) para os superiores
  lsHalf = x << 4;
  unsigned char joined = msHalf | lsHalf;
  return joined;
}

unsigned char rotate_left(unsigned char x, int n) {
  unsigned char c1, c2;
  c1 = x << n;
  c2 = x >> (8 - n);
  return c1 | c2;
}

int xbyte(unsigned int word, int bytenum) {
  signed char byte = 0;  // os valores empacotados ocupam no máximo 1 byte e tem sinal
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
      printf("Bytes vão de 0 a 3!\n");
      exit(1);
  }
  printf("%08x  %d\n", byte, byte);
  return byte;
}

int xbyte2(unsigned int word, int bytenum) {
  /**
   * Anonymous union for extracting
   * bytes from an unsigned integer
   */
  typedef union {
    unsigned i;
    char v[4];
  } PackedUnion;

  signed char byte = 0;  // os valores empacotados ocupam no máximo 1 byte e tem sinal
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
      printf("Bytes vão de 0 a 3!\n");
      exit(1);
  }
  printf("%08x  %d\n", byte, byte);
  return byte;
}

#include "cute_floating_point.h"

#define FLOAT_EXPONENT_BIAS 127
#define DOUBLE_EXPONENT_BIAS 1023

typedef union {
  float f;
  unsigned int i;
} FloatRepresentation;

typedef union {
  double d;
  unsigned long i;
} DoubleRepresentation;

float float2(float f) {
  FloatRepresentation u;
  unsigned int u1;

  // Store float in memory and get its bit representation
  u.f = f;
  u1 = u.i;

  /**
   * Discard mantissa bits (0-22) and mask bits beyond bit 7,
   * effectively attaining the exponent bits
   * */
  unsigned int exp = (u.i >> 23) & 0xff;

  /**
   * Multiply number by 2
   */
  exp += 1;

  /**
   * Shift 0xff to start at bit 23 (exponent start) and NOT it.
   * After ANDing, we clear the previous exponent
   */
  u1 &= ~(0xff << 23);

  /**
   * Update our exponent by ORing 
   * our new exponent shifted to its position (bit 23)
   */
  u1 |= (exp << 23);

  /**
   * Return the modified bits
   * "interpreted" (casted) as `float`
   */
  u.i = u1;
  return u.f;
}

int float2int(float f) {
  if (f == 0) {
    return 0;
  }

  FloatRepresentation u;
  u.f = f;

  /**
   * Use numbers very close to INT_MAX and INT_MIN
   * so that the guards below capture overflow cases
   */
  if (f > 2147483520.0f) {
    printf("float2int: float exceeds maximum integer size. Returning INT_MAX!\n");
    return INT_MAX;
  }
  if (f < INT_MIN) {
    printf("float2int: float exceeds minimum integer size. Returning INT_MIN!\n");
    return INT_MIN;
  }

  uint8_t s = 0;
  uint8_t e = 0;
  uint32_t m = 0;

  s = (u.i >> 31) & 1;
  e = (u.i >> 23) & 0xff;
  m = u.i & 0x7fffff;

  uint32_t mantissaBits = 0;
  mantissaBits |= (1 << 23);  // adds implicit 1 (IEEE 754)
  mantissaBits |= m;

  // TODO: stop using math.h here

  // Divide by 2^23 as we treat mantissaBits as an integer right shifted by 23 bits
  float trueMantissa = mantissaBits / (float)pow(2, 23);

  int trueExponent = e - FLOAT_EXPONENT_BIAS;

  return (int)(pow(-1, s) * trueMantissa * pow(2, trueExponent));
}

float int2float(int i) {
  if (i == 0) {
    return 0.0;
  }

  FloatRepresentation u;
  int s;
  unsigned mantissa = 0;
  unsigned convertedInt = 0;

  if (i < 0) {
    s = 1;
    i = -i;  // get absolute value of negative number
  } else {
    s = 0;
  }

  char foundFirstBit1 = 0;
  int mantissaPosition = 22;
  int exp = 0;

  for (int count = 31; count >= 0; count--) {
    char currentBit = (i >> count) & 1;
    if (currentBit == 1 && !foundFirstBit1) {
      foundFirstBit1 = 1;
      // the exponent without bias is really the position of the first 1 bit
      exp = count;
      // skip current iteration as first 1 bit is implicit in IEEE 754
      continue;
    }

    if (foundFirstBit1) {
      /**
       * Discard bits of large numbers (more than 23 mantissa bits), ensuring
       * maximum float size in IEEE 754
       */
      if (mantissaPosition >= 0) {
        mantissa |= (currentBit << mantissaPosition);
        mantissaPosition--;
      }
    }
  }

  exp += FLOAT_EXPONENT_BIAS;
  convertedInt |= (s << 31);
  convertedInt |= (exp << 23);
  convertedInt |= mantissa;

  u.i = convertedInt;
  return u.f;
}

double maxdouble(double a, double b) {
  DoubleRepresentation ua;
  DoubleRepresentation ub;

  ua.d = a;
  ub.d = b;

  uint8_t sa, sb;
  sa = (ua.i >> 63) & 1;
  sb = (ub.i >> 63) & 1;

  if (sa > sb) {
    return b;
  }
  if (sb > sa) {
    return a;
  }

  // From this point on, we must compare `m` and `e` and the numbers have same signedness
  uint16_t ea, eb;
  uint64_t ma, mb;

  ea = (ua.i >> 52) & 0x7ff;
  eb = (ub.i >> 52) & 0x7ff;

  ma = ua.i & 0xFFFFFFFFFFFFF;
  mb = ub.i & 0xFFFFFFFFFFFFF;

  uint64_t mantissaBitsA = 0;
  uint64_t mantissaBitsB = 0;

  // Use 64-bit "1" to avoid compiler overflow warnings
  mantissaBitsA |= 1ULL << 52;
  mantissaBitsB |= 1ULL << 52;

  mantissaBitsA |= ma;
  mantissaBitsB |= mb;

  // Remove bias from the `double`s to get their true exponent
  int expA = ea - DOUBLE_EXPONENT_BIAS;
  int expB = eb - DOUBLE_EXPONENT_BIAS;

  /**
   * Compare the exponents first:
   * 
   * As the mantissa (1.M) is in [1.0, 2.0), if their exponents
   * are distinct, the number with the biggest exponent
   * is the biggest (if both are positive). If they are negative,
   * the biggest exponent is the smallest number.
   */
  if (expA != expB) {
    // Both numbers have same signedness, check either one
    if (sa == 0) {
      // They are positive: biggest exponent is the largest number
      return (expA > expB) ? a : b;
    } else {
      // They are negative: biggest exponent is the smallest number
      return (expA < expB) ? a : b;
    }
  }

  /**
   * Signedness and exponents are the same, compare the mantissas:
   */
  if (mantissaBitsA != mantissaBitsB) {
    if (sa == 0) {
      // Positive: larger mantissa means larger value
      return (mantissaBitsA > mantissaBitsB) ? a : b;
    } else {
      // Negative: larger mantissa means more negative (smaller)
      return (mantissaBitsA < mantissaBitsB) ? a : b;
    }
  }

  /**
   * Worst case: the numbers are the same, return either one.
   * I picked the first one for no reason
   */
  return a;
}

void dump_mantissa_bits(uint32_t mantissa) {
  for (int i = 22; i >= 0; i--) {
    printf("%d", (mantissa >> i) & 1);
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

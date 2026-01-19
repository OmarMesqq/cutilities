#ifndef CUTE_FLOATING_POINT_H
#define CUTE_FLOATING_POINT_H

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

/**
 * Small value to check whether
 * two floating point numbers
 * are "equal" within a tolerance
 * range
 */
#define EPSILON 1e-12

/**
 * Returns 1 two floating point numbers are "equal" i.e.
 * if their difference is smaller than 
 * the `EPSILON` threshold
 */
#define FEQUAL(a, b) (fabs((a) - (b)) < EPSILON)

float float2(float f);
int float2int(float f);
float int2float(int i);
double maxdouble(double a, double b);
void dump_mantissa_bits(uint32_t mantissa);

#endif

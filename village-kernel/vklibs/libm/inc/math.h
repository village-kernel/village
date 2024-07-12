//###########################################################################
// math.h
// Header file for math classes
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MATH_H__
#define __MATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "stdarg.h"

typedef float float_t;

#ifndef PI
  #define PI               3.14159265358979f
#endif

double sqrt(double i);
double cos(double angle);
double sin(double angle);
double floor(double x);
double ceil(double x);

#ifdef __cplusplus
}
#endif

#endif //!__MATH_H__

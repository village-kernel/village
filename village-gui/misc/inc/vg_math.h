//###########################################################################
// vg_math.h
// Declarations of the functions that manage math
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_MATH_H__
#define __VG_MATH_H__

#include "stdint.h"
#include "stddef.h"


/// @brief VgMath
class VgMath
{
public:
	//Methods
	int Max(int a, int b);
	int Min(int a, int b);
	int Sat(int a, int min, int max);
	bool IsInRange(int a, int min, int max);
};

#endif //!__VG_MATH_H__

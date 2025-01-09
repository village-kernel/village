//###########################################################################
// vg_math.cpp
// Definitions of the functions that manage math
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_math.h"


/// @brief Max
/// @param a 
/// @param b 
/// @return 
int VgMath::Max(int a, int b)
{
	return (a > b) ? a : b;
}


/// @brief Min
/// @param a 
/// @param b 
/// @return 
int VgMath::Min(int a, int b)
{
	return (a < b) ? a : b;
}


/// @brief Sat
/// @param a 
/// @param max 
/// @param min 
/// @return 
int VgMath::Sat(int a, int min, int max)
{
	if (a < min)
		a = min;
	else if (a > max)
		a = max;

	return a;
}


/// @brief IsInRange
/// @param a 
/// @param min 
/// @param max 
/// @return 
bool VgMath::IsInRange(int a, int min, int max)
{
	return ((a >= min) && (a <= max));
}

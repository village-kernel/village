//###########################################################################
// vg_input_data.h
// Declarations of the functions that manage input data
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INPUT_DATA_H__
#define __VG_INPUT_DATA_H__

#include "stdint.h"

/// @brief VgWedget
class VgWedget;

/// @brief IData
template<typename Object>
class IData
{
public:
	//Destructor
	virtual ~IData() {}

	//Methods
	virtual void Binding(VgWedget* wedget) = 0;
	virtual void Set(Object value) = 0;
	virtual Object Get() = 0;
};

#endif //!__VG_INPUT_DATA_H__

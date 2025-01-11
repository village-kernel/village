//###########################################################################
// vg_data_interface.h
// Declarations of the functions that manage data interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DATA_INTERFACE_H__
#define __VG_DATA_INTERFACE_H__

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

#endif //!__VG_DATA_INTERFACE_H__

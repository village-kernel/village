//###########################################################################
// vg_relay_data.h
// Declarations of the functions that manage relay data
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_RELAY_DATA_H__
#define __VG_RELAY_DATA_H__

#include "vg_input_data.h"
#include "vg_wedget.h"


/// @brief IData
template<typename Object>
class RelayData : public IData<Object>
{
private:
	//Members
	Object object;
	VgWedget* wedget;
public:
	/// @brief Constructor
	/// @param object 
	RelayData(Object object)
		:object(object)
	{
	}

	/// @brief Binding wedget
	/// @param wedget 
	void Binding(VgWedget* wedget)
	{
		this->wedget = wedget;
	}

	/// @brief Set value
	/// @param value 
	void Set(Object value)
	{
		object = value;
		if (wedget) wedget->UpdateRequest(true);
	}

	/// @brief Get value
	/// @return 
	Object Get()
	{
		return object;
	}
};

#endif //!__VG_RELAY_DATA_H__

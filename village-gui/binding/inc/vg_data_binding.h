//###########################################################################
// vg_data_binding.h
// Declarations of the functions that manage data binding
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DATA_BINDING_H__
#define __VG_DATA_BINDING_H__

#include "vg_data_interface.h"
#include "vg_wedget.h"


/// @brief BindingData
template<typename Object>
class BindingData : public IData<Object>
{
private:
	//Members
	Object object;
	VgWedget* wedget;
public:
	/// @brief Constructor
	/// @param object 
	BindingData(Object object)
		:object(object),
		wedget(NULL)
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

#endif //!__VG_DATA_BINDING_H__

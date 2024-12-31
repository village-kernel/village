//###########################################################################
// vg_context.h
// Declarations of the functions that manage context
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_CONTEXT_H__
#define __VG_CONTEXT_H__

#include "vg_wedget.h"


/// @brief Context
class Context : public Wedget
{
private:
	//Members
	DrawArea oldArea;

	//Methods
	bool UpdateActive(bool active);
public:
	//Methods
	Context();
	~Context();

	//Area methods
	DrawAreas GetUpdateAreas();

	//Methods
	void Execute(IndevData input);
};

#endif //!__VG_CONTEXT_H__

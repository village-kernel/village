//###########################################################################
// vg_group.h
// Declarations of the functions that manage group
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_GROUP_H__
#define __VG_GROUP_H__

#include "vg_data.h"
#include "vg_window.h"
#include "vk_list.h"


/// @brief GraphicsGroup
class GraphicsGroup
{
private:
	//Members
	GraphicsData&  data;
	List<Window*>  mainwins;
	Window*        activedwin;
private:
	//Methods
	void SelectWindow(IndevData& input);
public:
	//Methods
	GraphicsGroup(GraphicsData& data);
	~GraphicsGroup();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Window* Create();
	bool Destroy(Window* win);
};

#endif //!__VG_GROUP_H__

//###########################################################################
// vg_object.h
// Declarations of the functions that manage object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_OBJECT_H__
#define __VG_OBJECT_H__

#include "vg_devices.h"
#include "vg_layer.h"
#include "vg_wedget.h"
#include "vg_list.h"


/// @brief GraphicsObject
class GraphicsObject
{
private:
	//Members
	GraphicsDevices&   devices;
	VgList<Wedget*>    wedgets;
	Wedget*            defWedget;
	Wedget*            actWedget;
	Layer              layer;
	IndevData          input;
	IndevData          axis;
private:
	//Focus Methods
	bool IsActWedgetChange();
	VgList<DrawArea> GetActWedgetUpperAreas();
	void RedrawActWedgetOverlapAreas();
	void SwapActWedgetListNode();

	//Move Methods
	void UpdataInput();
	bool IsCurWedgetMove();
	bool IsActWedgetMove();
	VgList<DrawArea> GetMoveWedgetOverlapAreas(Wedget* movWedget);
	void RedrawMoveWedgetArea(Wedget* movWedget, VgList<DrawArea> areas);
	void RedrawMoveWedgetOverlapAreas(Wedget* movWedget);
public:
	//Methods
	GraphicsObject(GraphicsDevices& devices);
	~GraphicsObject();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	Wedget* Create();
	bool Destroy(Wedget* win);
};

#endif //!__VG_GROUP_H__

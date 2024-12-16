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
	Wedget*            curWedget;
	Layer              layer;
	IndevData          input;
	IndevData          axis;
private:
	//Methods
	void UpdataInput();
	bool IsCurWedgetMove();
	bool IsActWedgetMove();
	bool IsActWedgetChange();
	
	//Focus Methods
	DrawAreas GetWedgetUpperAreas(Wedget* selWedget);
	DrawAreas GetSelWedgetOverlapAreas(Wedget* selWedget);
	void RedrawSelWedgetOverlapAreas(Wedget* selWedget);
	void SwapActWedgetListNode(Wedget* selWedget);
	void AlwaysFocusWedgetExecute(Wedget* selWedget);

	//Move Methods
	DrawAreas GetMoveWedgetOverlapAreas(Wedget* movWedget);
	void RedrawOtherWedgetAreas(Wedget* movWedget);
	void RedrawMoveWedgetAreas(Wedget* movWedget);
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

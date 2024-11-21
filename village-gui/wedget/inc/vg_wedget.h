//###########################################################################
// vg_wedget.h
// Declarations of the functions that manage wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WEDGET_H__
#define __VG_WEDGET_H__

#include "vk_list.h"
#include "vg_data.h"
#include "vg_input_cmd.h"


/// @brief Wedget
class Wedget
{
protected:
	//Members
	ICommand*     cmd;
	DrawArea      area;
	SystemInfo*   sysinfo;
	List<Wedget*> wedgets;
public:
	//Content methods
	virtual void InitContent() = 0;
	virtual void DrawContent() = 0;
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Area methods
	void SetSize(int x, int y, int width, int height);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	DrawArea GetArea();

	//Wedget methods
	void AddWedget(Wedget* wedget);

	//Binding methods
	void SetCommand(ICommand* cmd);

	//Methods
	void Init(SystemInfo* sysinfo);
	void Execute(IndevData input);
	void Flush(List<DrawArea> areas);
	void Show();
};

#endif //!__VG_WEDGET_H__

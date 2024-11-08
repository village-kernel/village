//###########################################################################
// vg_display.h
// Declarations of the functions that manage dispaly
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DISPLAY_H__
#define __VG_DISPLAY_H__

#include "vg_data.h"
#include "vg_lcddev.h"
#include "vk_list.h"


/// @brief GraphicsDisplay
class GraphicsDisplay
{
private:
	//Members
	GraphicsData&  data;
	List<Lcddev*>  lcddevs;
	bool           isReady;
public:
	//Methods
	GraphicsDisplay(GraphicsData& data);
	~GraphicsDisplay();
	void Setup();
	void Execute();
	void Exit();

	//Methods
	void RegisterLcddev(Lcddev* lcd);
	void UnregisterLcddev(Lcddev* lcd);
};

#endif //!__VG_DISPLAY_H__

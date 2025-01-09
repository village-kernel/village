//###########################################################################
// monitor_view.h
// Declarations of the monitor view
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MONITOR_VIEW_H__
#define __MONITOR_VIEW_H__

#include "monitor_model.h"

/// @brief MonitorView
class MonitorView
{
private:
	//Members
	MonitorModel model;
public:
	//Methods
	void InitComponent(VgWedget* parent);
};

#endif //!__MONITOR_VIEW_H__

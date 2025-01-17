//###########################################################################
// vg_table.cpp
// Definitions of the functions that manage table
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_table.h"


/// @brief Constructor
VgTable::VgTable()
{
	SetTitle((char*)"table");
}


/// @brief Destructor
VgTable::~VgTable()
{
}


/// @brief VgTable initiate
/// @param devices 
void VgTable::InitContent(VgDevices* devices)
{

}


/// @brief VgTable execute
/// @param input 
void VgTable::ExecContent(VgInputData input)
{
	if (IsInLayerArea(input.point.x, input.point.y))
	{
		ExecuteCommand(input);
	}
}


/// @brief VgTable draw
/// @param drawArea 
void VgTable::DrawContent(VgDrawArea drawArea)
{

}

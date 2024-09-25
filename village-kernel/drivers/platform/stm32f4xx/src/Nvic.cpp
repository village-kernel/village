//###########################################################################
// Nvic.cpp
// Manages the Nested vectored interrupt controller (NVIC)
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Nvic.h"


/// @brief Constructor
Nvic::Nvic()
{
}


/// @brief Config IRQ Type
/// @param type 
void Nvic::Initialize(IRQn_Type type)
{
	irqType = type;
}


/// @brief Returns the priority group setting, which indicates the number of bits used for the group priority and subpriority.
/// @return 
Nvic::PriorityGrouping Nvic::GetPriorityGroupSetting()
{
	return PriorityGrouping(NVIC_GetPriorityGrouping());
}


/// @brief Gets the priority value of the specified interrupt and
///        decodes it into group priority and sub priority fields
/// @param groupPriority 
/// @param subPriority 
void Nvic::DecodePriority(uint32_t* groupPriority, uint32_t* subPriority)
{
	NVIC_DecodePriority(irqType, GetPriorityGroupSetting(), groupPriority, subPriority);
}


/// @brief Configures the priority group setting, which determines the number of bits used for the group priority and subpriority.
/// @param prioGroup 
void Nvic::ConfigPriorityGroupSetting(PriorityGrouping prioGroup)
{
	NVIC_SetPriorityGrouping(prioGroup);
}


/// @brief Sets the group priority and sub priority of the selected interrupt
/// @param groupPriority 
/// @param subPriority 
void Nvic::SetPriority(uint8_t groupPriority, uint8_t subPriority)
{
	uint32_t prioritygroup = NVIC_GetPriorityGrouping();
	NVIC_SetPriority(irqType, NVIC_EncodePriority(prioritygroup, groupPriority, subPriority));
}

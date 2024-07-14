//###########################################################################
// HwConfig.h
//
// Contains hardware configuration such as pin and peripheral assignments
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#if defined(STM32F407xx)
#include "stm32f407_config.h"
#elif defined(STM32H743xx)
#include "stm32h743_config.h"
#endif

#endif

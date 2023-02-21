//###########################################################################
// HWManager.cpp
// Definitions of the functions that manage hardware device
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "HWManager.h"
#include "HwConfig.h"
#include "Kernel.h"


///Initialize the singleton instance of HWManager
HWManager HWManager::instance;


///Constructor
HWManager::HWManager()
{
}


///Hardware initialize
void HWManager::Initialize()
{
	ILI9488Initialize();
}


///Hardware update params
void HWManager::UpdateParams()
{

}


///Hardware fail safe
void HWManager::FailSafe(int arg)
{

}


///Initialize ILI9488
inline void HWManager::ILI9488Initialize()
{
	ILI9488::Config config;
	
	config.backLightCh = LCD_BACK_LIGHT_CH;
	config.backLightPin = LCD_BACK_LIGHT_PIN;

	config.fsmcConfig.csCh = LCD_CS_CH;
	config.fsmcConfig.csPin = LCD_CS_PIN;
	config.fsmcConfig.rsCh = LCD_RS_CH;
	config.fsmcConfig.rsPin = LCD_RS_PIN;
	config.fsmcConfig.wrCh = LCD_WR_CH;
	config.fsmcConfig.wrPin = LCD_WR_PIN;
	config.fsmcConfig.rdCh = LCD_RD_CH;
	config.fsmcConfig.rdPin = LCD_RD_PIN;

	config.fsmcConfig.db0Ch = LCD_DB0_CH;
	config.fsmcConfig.db0Pin = LCD_DB0_PIN;
	config.fsmcConfig.db1Ch = LCD_DB1_CH;
	config.fsmcConfig.db1Pin = LCD_DB1_PIN;
	config.fsmcConfig.db2Ch = LCD_DB2_CH;
	config.fsmcConfig.db2Pin = LCD_DB2_PIN;
	config.fsmcConfig.db3Ch = LCD_DB3_CH;
	config.fsmcConfig.db3Pin = LCD_DB3_PIN;
	config.fsmcConfig.db4Ch = LCD_DB4_CH;
	config.fsmcConfig.db4Pin = LCD_DB4_PIN;
	config.fsmcConfig.db5Ch = LCD_DB5_CH;
	config.fsmcConfig.db5Pin = LCD_DB5_PIN;
	config.fsmcConfig.db6Ch = LCD_DB6_CH;
	config.fsmcConfig.db6Pin = LCD_DB6_PIN;
	config.fsmcConfig.db7Ch = LCD_DB7_CH;
	config.fsmcConfig.db7Pin = LCD_DB7_PIN;
	config.fsmcConfig.db8Ch = LCD_DB8_CH;
	config.fsmcConfig.db8Pin = LCD_DB8_PIN;
	config.fsmcConfig.db9Ch = LCD_DB9_CH;
	config.fsmcConfig.db9Pin = LCD_DB9_PIN;
	config.fsmcConfig.db10Ch = LCD_DB10_CH;
	config.fsmcConfig.db10Pin = LCD_DB10_PIN;
	config.fsmcConfig.db11Ch = LCD_DB11_CH;
	config.fsmcConfig.db11Pin = LCD_DB11_PIN;
	config.fsmcConfig.db12Ch = LCD_DB12_CH;
	config.fsmcConfig.db12Pin = LCD_DB12_PIN;
	config.fsmcConfig.db13Ch = LCD_DB13_CH;
	config.fsmcConfig.db13Pin = LCD_DB13_PIN;
	config.fsmcConfig.db14Ch = LCD_DB14_CH;
	config.fsmcConfig.db14Pin = LCD_DB14_PIN;
	config.fsmcConfig.db15Ch = LCD_DB15_CH;
	config.fsmcConfig.db15Pin = LCD_DB15_PIN;

	ili9488.Initialize(config);
}


///Register module
REGISTER_MODULE(HWManager::Instance(), HARDWARE_ID(0), hardware);

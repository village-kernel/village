//###########################################################################
// HwConfig.h
//
// Contains hardware configuration such as pin and peripheral assignments
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

//*********************************lcd Pin*********************************//
#define LCD_BACK_LIGHT_CH                    Gpio::_ChG
#define LCD_BACK_LIGHT_PIN                   8

#define LCD_CS_CH                            Gpio::_ChG
#define LCD_CS_PIN                           12

#define LCD_RS_CH                            Gpio::_ChF
#define LCD_RS_PIN                           12

#define LCD_WR_CH                            Gpio::_ChD
#define LCD_WR_PIN                           5

#define LCD_RD_CH                            Gpio::_ChD
#define LCD_RD_PIN                           4

#define LCD_DB0_CH                           Gpio::_ChD
#define LCD_DB0_PIN                          14

#define LCD_DB1_CH                           Gpio::_ChD
#define LCD_DB1_PIN                          15

#define LCD_DB2_CH                           Gpio::_ChD
#define LCD_DB2_PIN                          0

#define LCD_DB3_CH                           Gpio::_ChD
#define LCD_DB3_PIN                          1

#define LCD_DB4_CH                           Gpio::_ChE
#define LCD_DB4_PIN                          7

#define LCD_DB5_CH                           Gpio::_ChE
#define LCD_DB5_PIN                          8

#define LCD_DB6_CH                           Gpio::_ChE
#define LCD_DB6_PIN                          9

#define LCD_DB7_CH                           Gpio::_ChE
#define LCD_DB7_PIN                          10

#define LCD_DB8_CH                           Gpio::_ChE
#define LCD_DB8_PIN                          11

#define LCD_DB9_CH                           Gpio::_ChE
#define LCD_DB9_PIN                          12

#define LCD_DB10_CH                          Gpio::_ChE
#define LCD_DB10_PIN                         13

#define LCD_DB11_CH                          Gpio::_ChE
#define LCD_DB11_PIN                         14

#define LCD_DB12_CH                          Gpio::_ChE
#define LCD_DB12_PIN                         15

#define LCD_DB13_CH                          Gpio::_ChD
#define LCD_DB13_PIN                         8

#define LCD_DB14_CH                          Gpio::_ChD
#define LCD_DB14_PIN                         9

#define LCD_DB15_CH                          Gpio::_ChD
#define LCD_DB15_PIN                         10

#endif // !__HW_CONFIG_H__

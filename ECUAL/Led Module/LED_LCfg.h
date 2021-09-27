/*****************************************************************************
* Module: Led Module
* File Name: Led_LCfg.h
* Description:Configurations Header file for Led Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
#ifndef LEDLCFG_H_
#define LEDLCFG_H_
/****************************INCLUDES***************************************/
#include "..\..\MCAL\SWPwm Module\SWPwm_LCfg.h"
#include "..\..\MCAL\Dio Module\Dio_LCfg.h"
/**********************Number of used LEDs***********************************/
#define NUM_OF_LEDS_USED       2
/***************************************************************************/
/*************************************************************************************/
#define LED_ID_0		0
#define LED_ID_1        1
/************************************************************************************/
/* Used PWD Channel for animated LEDs */
#define LED_CHANNEL_0    SWPWM_CHANNEL_0_ID
/* Used Dio Channel for Ordinary LED */
#define LED_CHANNEL_1    DIO_LED_CHANNEL_ID
#endif /* LEDLCFG_H_ */
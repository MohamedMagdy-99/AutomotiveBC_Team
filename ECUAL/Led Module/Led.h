/*****************************************************************************
* Module: Led Module
* File Name: Led.h
* Description:Header file for Led Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/


#ifndef LED_H_
#define LED_H_
/*************************************INCLUDES*************************************/
#include "..\..\Microcontroller\Platform_Types.h"
#include "..\..\Microcontroller\Std_types.h"
#include "LED_LCfg.h"
/*************************************Type Definitons**********************************/
typedef uint8_t LEDId_t ;
typedef uint8_t LEDType_t ;
typedef uint8_t LED_Ch_t ;

typedef struct LEDConfig_t
{
	LEDId_t   LEDId ;
	LEDType_t LEDMode;
	LED_Ch_t  LEDChannel ;
	
	
}LEDConfig_t;
/*************************************************************************************/
typedef enum LEDReturn_t
{
	LEDModuleIntialized,
    LED_E_OK,
	LED_E_NOK,
	LED_InvlidLEDId,
	LED_InvalidMode
	
	
	
}LEDReturn_t;
/**************************************************************************************/
/* LEDtype Options */

#define ORDINARY_LED   0
#define ANIMATED_LED   1
/**************************************************************************************
										APIs
**************************************************************************************/
LEDReturn_t LED_Init(void);
LEDReturn_t LED_ON(LEDId_t LEDId);
LEDReturn_t LED_OFF(LEDId_t LEDId);
LEDReturn_t LED_Toggle(LEDId_t LEDId);
LEDReturn_t LED_AnimationStrat(LEDId_t LEDId,uint32_t u32_Freq, uint8_t u8_DutyCycle);
LEDReturn_t LED_AnimationStop(LEDId_t LEDId);
/************************************************************************************/
extern LEDConfig_t LEDConfigArr[NUM_OF_LEDS_USED];


#endif /* LED_H_ */
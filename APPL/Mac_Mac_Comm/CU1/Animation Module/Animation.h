/*****************************************************************************
* Module: Animation Module
* File Name: Animation.h
* Description:Header file for Animation Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
#ifndef ANIMATION_H_
#define ANIMATION_H_
/****************************INCLUDES****************************************/
#include "Microcontroller\Platform_Types.h"
#include "Microcontroller\Std_types.h"
#include "AnimationLCfg.h"
/****************************************************************************/
/* maximum number of serving animation per device */
#define MAX_SERVING_NUM   30U
/********************************Return values********************************************/
typedef enum ANReturn_t
{
	ANI_InitializedBefore,
	ANI_initialized,
	ANI_E_NOK,
	ANI_E_OK,
	InvlidDeviceId,
	ANI_ExceedMaxServing,
	
}ANReturn_t;
/******************************Pattrens Configuration************************************/
typedef struct ANI_Config_t
{
	uint8_t DeviceId ;
	uint8_t PatternId ;
	uint16_t ToltalPeriod ;
	uint16_t LOWPeriod ;
	uint16_t RisingPeriod ;
	uint16_t HighPeriod ;
	uint16_t FallingPeriod ;
	uint16_t IncreaseStepPeriod ;
	
}ANI_Config_t;
/**************************************************************************************/
extern ANI_Config_t ANIPatternsArr[TOTAL_NUM_OF_PATTERNS];
extern uint8_t ANIDeviceArr[NUM_OF_DEVICES_USED] ;
/*************************************************************************************
								    	APIs
**************************************************************************************/
ANReturn_t ANI_Init(void);
ANReturn_t ANI_Start(uint8_t DeviceId , uint8_t SubId, uint8_t AnimationPattern);
ANReturn_t ANI_Stop(uint8_t DeviceId , uint8_t SubId);
void ANI_MainFunction(void* pvParam);
/***************************************************************************************/
#endif /* ANIMATION_H_ */
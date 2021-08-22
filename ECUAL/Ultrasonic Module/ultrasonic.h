/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic.h
* Description: Header file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "..\..\MCAL\ICU Module\ICU.h"
#include "..\..\MCAL\Dio Module\Dio.h"
#include "..\..\Microcontroller\Platform_Types.h"
#include "../../Microcontroller/Std_types.h"
#include "Ultrasonic_LCfg.h"

typedef uint8_t US_Channel_t;

typedef struct US_Config_t
{
	ICU_channel_t ICU_ChannedID;
	uint8_t Trigger_Pin;
}US_ChannelConfig_t;

/************************************************************
				        APIs
************************************************************/
Std_ReturnType Ultrasonic_Init(void);
Std_ReturnType Ultrasonic_GetDistance(US_Channel_t US_ChannelID ,  uint16_t *u16_Distance);
/*- EXTERN VARIABLE DECLARATIONS */
extern const US_ChannelConfig_t US_Configurations[US_USED_CHANNELS] ;

#endif /* ULTRASONIC_H_ */

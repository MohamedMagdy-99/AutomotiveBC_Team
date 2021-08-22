/*****************************************************************************
* Module: ICU Module
* File Name: ICU.h
* Description: Header file for ICU Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/


#ifndef ICU_H_
#define ICU_H_
#include "..\..\Microcontroller\Std_types.h"
#include "..\..\Microcontroller\Platform_Types.h"
#include "ICU_LCfg.h"
#include "..\Gpt Module\Gpt.h"

/*
 * Data type for the ICU Channel
 */
typedef uint8_t ICU_channel_t;

/*
 * Data type for the ICU Counts
 */
typedef uint32_t ICU_Counts_t;

/*
 * Data type for the ICU Configurations
 */
typedef struct
{
	uint8_t Gpt_Channel;
	uint8_t Ext_InterruptChannel;
}ICU_ChannelConfig_t;

Std_ReturnType ICU_Init(void);
Std_ReturnType ICU_GetONPeriod_Counts(ICU_channel_t ChannelId_u8 , ICU_Counts_t *Counts_pu32);

/*- EXTERN VARIABLE DECLARATIONS ----------------------------------*/
extern const ICU_ChannelConfig_t ICU_Configurations[ICU_USED_CHANNELS];
#endif /* ICU_H_ */
/*****************************************************************************
* Module: Gpt Module
* File Name: Gpt.h
* Description: Header file for GPT Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/

#ifndef GPT_H_
#define GPT_H_

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"
#include "Interrupt_Interface.h"
#include "Gpt_LCfg.h"
//#include "../../MCAL/Interrupt Driver/ISR.h"

/*- CONSTANTS ----------------------------------------------*/
#define TIMERS_NUM			3U
#define TIMER_0_MAX_TICKS	256
#define TIMER_1_MAX_TICKS	65536
#define TIMER_2_MAX_TICKS	256
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfGpt_CallBack_t)(uint8_t);

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	GPT_STATUS_ERROR_NOK,
	GPT_STATUS_ERROR_OK,
	GPT_STATUS_ALREADY_RUNNING,
	GPT_STATUS_NOT_RUNNING,
	GPT_STATUS_ERROR_ALREADY_INIT
}enuGpt_Status_t;

typedef enum
{
	GPT_INITIALIZED,
	GPT_NOT_INITIALIZED
}enuGpt_initStatus_t;

typedef struct
{
	uint8_t u8_TimerNumber;
	uint16_t u8_Prescaler;
	uint8_t u8_Mode;
}strGpt_Config_t;


/*- FUNCTION DECLARATIONS ----------------------------------*/

enuGpt_Status_t GptInit(void);


enuGpt_Status_t GptStart_Sync(uint8_t ChannelId, uint32_t u32_Ticks); 

enuGpt_Status_t GptStart_aSync(uint8_t ChannelId, uint32_t u32_Ticks, pfGpt_CallBack_t FunToBeCalledInISR);


enuGpt_Status_t GptStop(uint8_t ChannelId); 

enuGpt_Status_t Gpt_StartTimer(uint8_t ChannelId);

enuGpt_Status_t Gpt_EnableNotification_OVF(uint8_t ChannelId, pfGpt_CallBack_t FunToBeCalledInISR);
enuGpt_Status_t Gpt_setCounterValue(uint8_t ChannelId, uint16_t CounterValue);
enuGpt_Status_t Gpt_getCounterValue(uint8_t ChannelId, uint16_t *CounterValue);
enuGpt_Status_t Gpt_Start(uint8_t ChannelId, uint16_t InitialCount);

void setOvfCallback(pfGpt_CallBack_t FunToBeCalledInISR);

void Gpt_ReturnCounterVal(uint8_t ChannelId , uint32_t *u32_CounterVal);
/*- EXTERN VARIABLE DECLARATIONS ----------------------------------*/
extern strGpt_Config_t strGpt_Channels[GPT_USED_CHANNELS];

#endif /* GPT_H_ */


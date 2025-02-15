/*****************************************************************************
* Module: Debounce Module
* File Name: DebounceHandler.h
* Description: Header file for Debounce Handler Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/ 


#ifndef DEBOUNCEHANDLER_H_
#define DEBOUNCEHANDLER_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Gpt.h"
#include "DebounceHandler_Cfg.h"
#include "Dio.h"
#include "Std_Types.h"
#include "Delay.h"
#include "Common_Macros.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS *-*-*-*-*-*/
/* handler states */
#define DEBOUNCE_HANDLER_IDLE									(90U)
#define DEBOUNCE_HANDLER_EVENT_RECV					        	(91U)
#define DEBOUNCE_HANDLER_EVENT_WAITING						    (92U)
#define DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE				(93U)

/*- Primitive Types
-------------------------------*/
typedef Std_ReturnType(*deviceState_t)(uint8_t, uint8_t*);

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t  u8_deviceId;
	uint8_t	 u8_timerId;
	uint16_t u16_delayTicks;
	uint8_t	 u8_delayType;	 
	uint8_t	 u8_deviceCheck_PollingOrExtInt;
	uint8_t  u8_deviceAciveState;
	uint8_t  u8_deviceInActivetState;
	deviceState_t getdeviceStateFun;
}strDeviceDebounce_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
Std_ReturnType debounceHandler_updatedeviceState(uint8_t debouncingdeviceId);

Std_ReturnType debounceHandler_getDeviceState(uint8_t debouncingdeviceId, uint8_t* debouncingdeviceState);

Std_ReturnType debounceHandler_Init(void);

/* Event Trigger CallBack Function for External Int to installed in APP */
void eventReceived_Device_CallBack(uint8_t Int_ID);

/* configuration variable */
extern strDeviceDebounce_Config_t strDeviceDeounce_Config[DEBOUNCE_DEVICES_USED];
extern uint8_t au8_debouncingHandlerState[DEBOUNCE_DEVICES_USED];

#endif /* DEBOUNCEHANDLER_H_ */
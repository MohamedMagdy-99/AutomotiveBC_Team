/*****************************************************************************
* Module: Debounce Module
* File Name: DebounceHandler.c
* Description: Source file for Button Debounce Handler Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "DebounceHandler.h"

/*- GLOBAL EXTERN VARIABLES -------------------------------------*/
uint8_t au8_deviceLegitState[DEBOUNCE_DEVICES_USED];

uint8_t au8_deviceCurrentState[DEBOUNCE_DEVICES_USED];

uint8_t au8_debouncingHandlerState[DEBOUNCE_DEVICES_USED];

/* Debounce Delay CallBack Fucntion */
STATIC void callBack_AfterDelay(uint8_t Int_ID);

/*  gets the state of a given device active or inactive */
STATIC Std_ReturnType debounceHandler_eventReceived(uint8_t debouncingButtonId);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType debounceHandler_updatedeviceState(uint8_t debouncingdeviceId)
{
	switch(au8_debouncingHandlerState[debouncingdeviceId])
	{
		case(DEBOUNCE_HANDLER_IDLE):
		{
			/* check if button is polling */
			if(strDeviceDeounce_Config[debouncingdeviceId].u8_deviceCheck_PollingOrExtInt == POLLING)
			{
				strDeviceDeounce_Config[debouncingdeviceId].getdeviceStateFun(strDeviceDeounce_Config[debouncingdeviceId].u8_deviceId,
				&au8_deviceCurrentState[debouncingdeviceId]);
				
				if(au8_deviceCurrentState[debouncingdeviceId] != au8_deviceLegitState[debouncingdeviceId])
				{
					au8_debouncingHandlerState[debouncingdeviceId] = DEBOUNCE_HANDLER_EVENT_RECV; 
				}
				else
				{
					/* not pressed yet */
				}
			}
			else
			{
				/* ext int will trigger */
			}			
			break;
		}
		case(DEBOUNCE_HANDLER_EVENT_RECV):
		{
			/* start delay timer */
			if(strDeviceDeounce_Config[debouncingdeviceId].u8_delayType == DELAY_TIMER_ASYNC)
			{
				GptStart_aSync(strDeviceDeounce_Config[debouncingdeviceId].u8_timerId,
				strDeviceDeounce_Config[debouncingdeviceId].u16_delayTicks,
				callBack_AfterDelay);
				
				au8_debouncingHandlerState[debouncingdeviceId] = DEBOUNCE_HANDLER_EVENT_WAITING;				
			}
			else if(strDeviceDeounce_Config[debouncingdeviceId].u8_delayType == DELAY_TIMER_SYNC)
			{
				GptStart_Sync(strDeviceDeounce_Config[debouncingdeviceId].u8_timerId,
				strDeviceDeounce_Config[debouncingdeviceId].u16_delayTicks);	
				
				/* change state */
				au8_debouncingHandlerState[debouncingdeviceId] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;			
			}
			else if(strDeviceDeounce_Config[debouncingdeviceId].u8_delayType == DELAY_LOOP)
			{
				/* manual delay_ms */
				Delay_ms(strDeviceDeounce_Config[debouncingdeviceId].u16_delayTicks);
				/* change state */
				au8_debouncingHandlerState[debouncingdeviceId] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;	
			}
			else
			{
				
			}
			break;
		}
		case(DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE):
		{
			strDeviceDeounce_Config[debouncingdeviceId].getdeviceStateFun(strDeviceDeounce_Config[debouncingdeviceId].u8_deviceId,
			&au8_deviceCurrentState[debouncingdeviceId]);
			
			if(au8_deviceCurrentState[debouncingdeviceId] != au8_deviceLegitState[debouncingdeviceId])
			{ 
				 /* a new legit change in button */
				au8_deviceLegitState[debouncingdeviceId] = au8_deviceCurrentState[debouncingdeviceId];
				
				break;
			}
			else
			{
				/* fake change */
			}
			/* make state idle again */
			au8_debouncingHandlerState[debouncingdeviceId] = DEBOUNCE_HANDLER_IDLE;            
			break;
		}
		case(DEBOUNCE_HANDLER_EVENT_WAITING):
		{
			/* busy */
			break;
		}						
		default:
		{
			return E_NOT_OK;
		}
	}
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: Initialized Debounce Handler
************************************************************************************/
Std_ReturnType debounceHandler_Init(void)
{
	uint8_t u8_counter = Initial_Value;
	for(u8_counter = Initial_Value; u8_counter < DEBOUNCE_DEVICES_USED; u8_counter++)
	{
		au8_debouncingHandlerState[u8_counter] = DEBOUNCE_HANDLER_IDLE;
		au8_deviceLegitState[u8_counter] = strDeviceDeounce_Config[u8_counter].u8_deviceInActivetState;
		au8_deviceCurrentState[u8_counter] = strDeviceDeounce_Config[u8_counter].u8_deviceInActivetState;
	}
	return E_OK;
}

/************************************************************************************
* Parameters (in): Device ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the state of a given device active or inactive
************************************************************************************/
Std_ReturnType debounceHandler_getDeviceState(uint8_t debouncingdeviceId, uint8_t* debouncingdeviceState)
{
	/* return current legit state of given device active or inactive */
	*debouncingdeviceState = au8_deviceLegitState[debouncingdeviceId];
	return E_OK;
}

/************************************************************************************
* Parameters (in): Device ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the state of a given device active or inactive
************************************************************************************/
STATIC Std_ReturnType debounceHandler_eventReceived(uint8_t debouncingButtonId)
{
	if(au8_debouncingHandlerState[debouncingButtonId] != DEBOUNCE_HANDLER_IDLE)
	{
		return E_NOT_OK;
	}
	else
	{
		/* start timer delay flag */
		au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_EVENT_RECV; 
	}
	return E_OK;
}


/* Debounce Delay CallBack Fucntion */
STATIC void callBack_AfterDelay(uint8_t Int_ID)
{
	uint8_t u8_loopCounter = Initial_Value;
	
	switch(Int_ID)
	{
		case(TIMER0_OVF_IRQ):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strGpt_Channels[strDeviceDeounce_Config[u8_loopCounter].u8_timerId].u8_TimerNumber == TIMER_0)
				{
					au8_debouncingHandlerState[u8_loopCounter] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
				}
			}
			break;
		}
		case(TIMER1_OVF_IRQ):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strGpt_Channels[strDeviceDeounce_Config[u8_loopCounter].u8_timerId].u8_TimerNumber == TIMER_1)
				{
					au8_debouncingHandlerState[u8_loopCounter] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
				}
			}
			break;
		}
		case(TIMER2_OVF_IRQ):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strGpt_Channels[strDeviceDeounce_Config[u8_loopCounter].u8_timerId].u8_TimerNumber == TIMER_2)
				{
					au8_debouncingHandlerState[u8_loopCounter] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
				}
			}
			break;
		}
	}
}





/* Event Trigger CallBack Function for External Int */
void eventReceived_Device_CallBack(uint8_t Int_ID)
{
	uint8_t u8_loopCounter = Initial_Value;
	
	switch(Int_ID)
	{
		case(EXT_INT_0):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strDeviceDeounce_Config[u8_loopCounter].u8_deviceCheck_PollingOrExtInt == EXT_INT_0)
				{
					debounceHandler_eventReceived(u8_loopCounter);
				}
			}
			break;
		}
		case(EXT_INT_1):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strDeviceDeounce_Config[u8_loopCounter].u8_deviceCheck_PollingOrExtInt == EXT_INT_1)
				{
					debounceHandler_eventReceived(u8_loopCounter);
				}
			}
			break;
		}
		case(EXT_INT_2):
		{
			for(u8_loopCounter = Initial_Value; u8_loopCounter < DEBOUNCE_DEVICES_USED; u8_loopCounter++)
			{
				if(strDeviceDeounce_Config[u8_loopCounter].u8_deviceCheck_PollingOrExtInt == EXT_INT_2)
				{
					debounceHandler_eventReceived(u8_loopCounter);
				}
			}
			break;
		}
	}	
}

/*****************************************************************************
* Module: Debounce Module
* File Name: DebounceHandler_Cfg.c
* Description: Source file for Debounce Handler Cfg Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "DebounceHandler.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* here you adjust the debounce devices configurations */
strDeviceDebounce_Config_t strDeviceDeounce_Config[DEBOUNCE_DEVICES_USED]=
{
	 /*Device Id */	  /* timer Id */     /* delay Ticks */  /* delay type */ /* change check type */ /* device active state */ /* device inactive state */   /* device state fun */
	{D_DEVICE_1_ID, D_DEVICE_1_TIMER_ID,  D_DEVICE_1_DELAY,	DELAY_TIMER_ASYNC,    POLLING ,			 BUTTON_STATE_PRESSED,        BUTTON_STATE_RELEASED			,Button_getState},
	{D_DEVICE_2_ID, D_DEVICE_2_TIMER_ID,  D_DEVICE_2_DELAY,	DELAY_TIMER_ASYNC,    POLLING ,			 BUTTON_STATE_PRESSED,        BUTTON_STATE_RELEASED			,Button_getState}
	
};


/* you must put all devices with same arrange as Cfg struct, if not using timer Async, put it as default callBack */
callBackFun_t debounceDeviceTimerCallBackFun[DEBOUNCE_DEVICES_USED] =
{
	callBack_Device_1,
	callBack_Device_2
};

/* Event Trigger Call Back Functions for External Int */
void eventReceived_Device1_CallBack(void)
{
	debounceHandler_eventReceived(DEB_DEVICE_1_ID);
}

void eventReceived_Device2_CallBack(void)
{
	debounceHandler_eventReceived(DEB_DEVICE_2_ID);
}

/* Timers Call Back Functions */
void callBack_Device_1(void)
{
	au8_debouncingHandlerState[DEB_DEVICE_1_ID] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
	
}

void callBack_Device_2(void)
{
	au8_debouncingHandlerState[DEB_DEVICE_2_ID] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
	
}

void callBack_Device_Default(void)
{
	/* does nothing */
}
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
/* here you adjust the Debounce devices configurations */
strDeviceDebounce_Config_t strDeviceDeounce_Config[DEBOUNCE_DEVICES_USED]=
{
	 /*Device Id */	  /* timer Id */     /* delay Ticks */  /* delay type */ /* change check type */ /* device active state */ /* device inactive state */   /* device state fun */
	{D_DEVICE_1_ID, D_DEVICE_1_TIMER_ID,  D_DEVICE_1_DELAY,	DELAY_LOOP,			POLLING ,		     BUTTON_STATE_PRESSED,        BUTTON_STATE_RELEASED			,Button_getState},
	{D_DEVICE_2_ID, D_DEVICE_2_TIMER_ID,  D_DEVICE_2_DELAY,	DELAY_LOOP,			POLLING ,			 BUTTON_STATE_PRESSED,        BUTTON_STATE_RELEASED			,Button_getState},
	{D_DEVICE_3_ID, D_DEVICE_3_TIMER_ID,  D_DEVICE_3_DELAY,	DELAY_LOOP,		    POLLING ,			 BUTTON_STATE_PRESSED,        BUTTON_STATE_RELEASED			,Button_getState}	
	
};





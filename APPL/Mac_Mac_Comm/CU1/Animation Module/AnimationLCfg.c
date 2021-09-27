/*****************************************************************************
* Module: Animation Module
* File Name: AnimationLCfg.c
* Description:Configuration source file for Animation Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
#include "Animation.h"

ANI_Config_t ANIPatternsArr[TOTAL_NUM_OF_PATTERNS]=
{
       /* Device ID */     /*Pattern ID*/    /*TotalPeriod*/  /*low period */  /*Rising Period */ /*  High period*/  /*Falling period*/  /*Step Period */
   
	{  LED_DEVICE_ID   ,   MAL_FUN_PATTERN  ,    3000       ,   1500         ,      500        ,     500           ,      500          ,       10       },
	{  LED_DEVICE_ID   , VER_SEARCH_PATTERN ,    1200       ,   600          ,      200        ,     200           ,      200          ,       10       },
	{  LED_DEVICE_ID, DEVICE_SEARCH_PATTERN ,    1500       ,   750          ,      250        ,     250           ,      250          ,       10       },
	{  LED_DEVICE_ID, CONNECTION_ON_PATTERN ,    300        ,   150          ,      50         ,     50            ,      50           ,       10       }	       
};

uint8_t ANIDeviceArr[NUM_OF_DEVICES_USED] =
{
	LED_DEVICE_ID
};
/*****************************************************************************
* Module: Led Module
* File Name: Led_LCfg.c
* Description:Configurations Source file for Led Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
/********************************INCLUDES************************************/
#include "LED.h"
/***************************************************************************/





LEDConfig_t LEDConfigArr[NUM_OF_LEDS_USED]=

                                             /* Dio channel used in case of ORDINARY LED */
{   /*LED ID*/        /* LED Type */        /* PWM channel used in case of ANIMATED LED */
	
	{LED_ID_0 ,         ANIMATED_LED ,          LED_CHANNEL_0   }, 
    {LED_ID_1 ,         ORDINARY_LED ,          LED_CHANNEL_1   }		
};
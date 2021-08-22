/*****************************************************************************
* Module: Ultrasonic Module
* File Name: Ultrasonic_Cfg.c
* Description: Source file for Ultrasonic sensor Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/

#include "Ultrasonic.h"


const US_ChannelConfig_t US_Configurations[US_USED_CHANNELS] =
{
	/* ICU_ChannedID */  /* DIO Trig Channel */
	{  ICU_CHANNEL_0  ,   DIO_US_TRG_CHANNEL_ID  }
	
};
	
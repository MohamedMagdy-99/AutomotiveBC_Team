/*****************************************************************************
* Module: Gpt Module
* File Name: Gpt_Cfg.c
* Description: Source file for GPT Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


/*- INCLUDES
----------------------------------------------*/
#include "Gpt.h"


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* configuration of used timer channels */
strGpt_Config_t strGpt_Channels[GPT_USED_CHANNELS]=
{
	/*Timer Number*/ /*Prescaler*/   /* Mode */
	{  TIMER_0    ,   PRESCALER_64  , NORMAL_MODE   },
	{  TIMER_1    ,   PRESCALER_8  , NORMAL_MODE   },
	{  TIMER_2    ,   PRESCALER_64  , NORMAL_MODE   }
	
};

/*****************************************************************************
* Module: SW_ICU Module
* File Name: ICU_Cfg.c
* Description: Source file for SW_ICU Module
* Author: Shady Mamdouh
* Date: 8/12/2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "ICU.h"



/*----------------------------------------------*/
/* configuration of used ICU channels */
const ICU_ChannelConfig_t ICU_Configurations[ICU_USED_CHANNELS]=
{
	{TIMER_CHANNEL_1_ID, EXT_INT2}
};
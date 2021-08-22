/*****************************************************************************
* Module: Gpt Module
* File Name: Gpt_Cfg.h
* Description: Header file for GPT Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef GPT_LCFG_H_
#define GPT_LCFG_H_

/* CONSTANTS */

/* user set the number of pins used in the project */

#define GPT_USED_CHANNELS		2
#define SYS_CLOCK_FREQUENCY		8000000


#define TIMER_0   0
#define TIMER_1   1
#define TIMER_2   2

#define PRESCALER_1     1
#define PRESCALER_8     8
#define PRESCALER_32    32
#define PRESCALER_64    64
#define PRESCALER_128   128
#define PRESCALER_256   256
#define PRESCALER_1024	1024

#define NORMAL_MODE   0

#define TIMER_CHANNEL_0_ID	0
#define TIMER_CHANNEL_1_ID	1
#define TIMER_CHANNEL_2_ID	2


#endif /* GPT_LCFG_H_ */
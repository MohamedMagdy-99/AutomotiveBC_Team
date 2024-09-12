/*****************************************************************************
* Module: OS Module
* File Name: OS_Cfg.h
* Description: Header file for OS Module
* Author: Mohamed Magdy
* Date: 28-Aug-2021
******************************************************************************/


#ifndef OS_CFG_H_
#define OS_CFG_H_

 /*- Constants
 -------------------------------*/
 #define OS_BASE_SYSTICKS_TIMERTICKS	(125U) /* N ticks for 8Mhz 8 bits timer is 1ms */
 
 #define MAX_NUM_TASKS					(3U)

 #define MAX_PRIOIRTY					(255U)  /* 0 is least priority */
 
 /* timer ID of GPT driver */
 #define TIMER_ID						TIMER_CHANNEL_0_ID
 
 /* low power mode */
 #define CPU_SLEEP_MODE						IDLE_MODE
 
 /* CPU load calc. part, not activated */
 #if 0
 /* CPU load settings, if i want to refresh CPU load each 1000 OS ticks, means i have set number of times (CPU_LOAD_CALC_CYCLES) 
  to calculate the cpu load each (CPU_LOAD_FRAME) (4 * 250 = 1000) */
 
 #define CPU_LOAD_FRAME					(1000U)  /* N OS ticks */
 
 #define CPU_LOAD_CALC_CYCLES			(5u)    /* calculate CPU load N times every CPU_LOAD_FRAME (not more than 256) */
#endif

#endif /* OS_CFG_H_ */
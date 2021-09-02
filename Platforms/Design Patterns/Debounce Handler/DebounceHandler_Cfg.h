/*****************************************************************************
* Module: Debounce Module
* File Name: DebounceHandler_Cfg.h
* Description: Header file for Debounce Handler Cfg Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

#ifndef DEBOUNCEHANDLER_CFG_H_
#define DEBOUNCEHANDLER_CFG_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES (Debouncing Devices used) *-*-*-*-*-*/

#include "../Button Driver/Button.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/* user set the number of pins used in the project */

#define DEBOUNCE_DEVICES_USED			(2U)

/* button Id according to cfg struct array order to be used in function calls */
#define DEB_DEVICE_1_ID				    (0U)
#define DEB_DEVICE_2_ID				    (1U)

/* debounce devices id to be filled in cfg struct */
#define D_DEVICE_1_ID					BUTTON_1_ID
#define D_DEVICE_2_ID					BUTTON_2_ID

/* timers Id */
#define D_DEVICE_1_TIMER_ID				TIMER_CHANNEL_0_ID
#define D_DEVICE_2_TIMER_ID				TIMER_CHANNEL_1_ID

/* timers delay Ticks */
#define D_DEVICE_1_DELAY				(2500U)
#define D_DEVICE_2_DELAY			    (2500U)

/* delay type */
#define DELAY_TIMER_ASYNC						(50U)
#define DELAY_TIMER_SYNC						(51U)
#define DELAY_LOOP								(52U)

/* loop delay in ms */
#define DEFAULT_DELAY_LOOP_MS					(20U)

/* event change check type */
#define EXT_INT							(12U)
#define POLLING							(11U)


/* you declare here and define in Cfg.c */
/****************************************/
/* Event Trigger Call Back Functions for External Int */
void eventReceived_Device1_CallBack(void);
void eventReceived_Device2_CallBack(void);

/* Timers Call Back Functions */
void callBack_Device_1(void);
void callBack_Device_2(void);

#endif /* DEBOUNCEHANDLER_CFG_H_ */
/*
 * SWPwm_Cfg.h
 *
 * Created: 7/15/2021 3:26:59 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef SWPWM_LCFG_H_
#define SWPWM_LCFG_H_

#include "..\Gpt Module\Gpt_LCfg.h"
#include "..\Dio Module\Dio_LCfg.h"

/* Number of PWM Channels Used */
#define SWPWM_CHANNELS_NUM				1U

/* SWPWM Channel 0 Configurations */
#define SWPWM_CHANNEL_0_TIMER			TIMER_CHANNEL_0_ID		/* Timer Channel used by the SWPWM Channel 0 */
#define SWPWM_CHANNEL_0_DIO				DIO_PWM_CHANNEL_ID		/* DIO Channel used by the SWPWM Channel 0 */

/* ID for the SWPWM Channel 0*/
#define SWPWM_CHANNEL_0_ID				0U




#endif /* SWPWM_LCFG_H_ */
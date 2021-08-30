/*****************************************************************************
* Module: Low Power Modes Module
* File Name: PowerModes.h
* Description: Header file for Low Power Modes Module
* Author: Mohamed Magdy
* Date: 30-Aug-2021
******************************************************************************/


#ifndef LPM_H_
#define LPM_H_

/* INCLUDES
----------------------------*/
#include "PowerModes_Regs.h"
#include "Common_Macros.h"
/* CONSTANTS
----------------------------*/
 /* Sleep Modes */

#define IDLE_MODE						(0x00U)
#define POWER_DOWN_MODE					(0x01U)
#define POWER_SAVE_MODE					(0x02U)
#define STANDBY_MODE					(0x03U)
#define EXTENDED_STANDBY_MODE			(0x04U)
#define ADC_NOISE_REDUCTION_MODE		(0x05U)

/* Primitive Types
----------------------------*/
typedef uint8_t LPM_LowPowerMode_t;
/* Function Declarations
----------------------------*/

Std_ReturnType LPM_EnterLowPowerMode(LPM_LowPowerMode_t u8_Mode);

Std_ReturnType LPM_DisableLowPowerMode(void);
#endif /* LPM_H_ */
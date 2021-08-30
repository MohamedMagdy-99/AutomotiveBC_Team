/*****************************************************************************
* Module: Low Power Modes Module
* File Name: PowerModes_Regs.h
* Description: Header file for Low Power Modes Module
* Author: Mohamed Magdy
* Date: 30-Aug-2021
******************************************************************************/


#ifndef LPM_REGS_H_
#define LPM_REGS_H_

#include "Std_Types.h"

/* The MCU Control Register contains control bits for power management. */

#define MCUCR_R		(*(volatile uint8_t * const)0x0055)

#define SM0_B			4
#define SM1_B			5
#define SM2_B			6
#define SE_B			7

/*************************************************************/
/*************************************************************/


#endif /* LPM_REGS_H_ */
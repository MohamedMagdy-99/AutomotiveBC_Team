/******************************************************************************
 *
 * Module: SPI - Registers
 *
 * File Name: ISR_Regs.h
 *
 * Description: ISR Registers
 *
 * Author: Mohamed Magdy
 *
 * Date: 20-July-2021
 *******************************************************************************/



#ifndef  ISR_REGS_H_
#define  ISR_REGS_H_

#include "../Std_Types.h"

/*- Interrupt REGISTERS
-------------------------------*/
#define SREG_R		(*(volatile uint8_t * const)0x005F)
#define GLOBAL_INT	7
/*************************************************************************************/
#define GICR_R		(*(volatile uint8_t * const)0x005B)

#define INT0_B		6
#define INT1_B		7
#define INT2_B		5
/*************************************************************************************/
#define MCUCR_R		(*(volatile uint8_t * const)0x0055)

#define ISC00_B			0
#define ISC01_B			1
#define ISC10_B			2
#define ISC11_B			3
/*************************************************************************************/
#define MCUCSR_R		(*(volatile uint8_t * const)0x0054)

#define ISC2_B			6


#endif /*  ISR_REGS_H_ */
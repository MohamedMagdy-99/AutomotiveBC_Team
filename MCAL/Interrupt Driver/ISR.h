/*****************************************************************************
* Module: Interrupt Module
* File Name: ISR.h
* Description: Header file for Interrupt Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/


#ifndef ISR_H_
#define ISR_H_

#include "../../Microcontroller/Atmega32 Registers/ISR_Regs.h"
#include "../../Microcontroller/Std_Types.h"
#include "../../Libraries/Common_Macros.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfINT0_CallBack_t)(void);
typedef void (*pfINT2_CallBack_t)(void);

/*- Vector Table
-------------------------------*/
#define INT0         __vector_1					//External Interrupt Request 0
#define INT1         __vector_2					//External Interrupt Request 1
#define INT2		 __vector_3					//External Interrupt Request 2
#define TIMER2_COMP	 __vector_4					//Timer/Counter2 Compare Match
#define TIMER2_OVF	 __vector_5					//Timer/Counter2 Overflow
#define TIMER1_CAPT	 __vector_6  				//Timer/Counter1 Capture Event
#define TIMER1_COMPA __vector_7					//Timer/Counter1 Compare Match A
#define TIMER1_COMPB __vector_8					//Timer/Counter1 Compare Match B
#define TIMER1_OVF	 __vector_9					//Timer/Counter1 Overflow
#define TIMER0_COMP	 __vector_10				//Timer/Counter0 Compare Match
#define TIMER0_OVF	 __vector_11				//Timer/Counter0 Overflow
#define SPI_STC		 __vector_12				//SPI Serial Transfer Complete
#define USART_RXC	 __vector_13				//USART, Rx Complete
#define USART_UDRE	 __vector_14				//USART Data Register Empty
#define USART_TXC	 __vector_15				//USART, Tx Complete
#define ADC			 __vector_16				//ADC Conversion Complete
#define EE_RDY		 __vector_17				//EEPROM Ready
#define ANA_COMP	 __vector_18				//Analog Comparator
#define TWI			 __vector_19				//Two-wire Serial Interface
#define SPM_RDY		 __vector_20				//Store Program Memory Ready

#define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,used)) __VA_ARGS__; \
void vector (void)


/* CONSTANTS */

#define LOW_LEVEL			0			//The low level of INT0 generates an interrupt request.
#define LOGIC_CHANGE		1			//Any logical change on INT0 generates an interrupt request.
#define FALLING_EDGE		2			//The falling edge of INT0 generates an interrupt request.
#define RISING_EDGE			3			//The rising edge of INT0 generates an interrupt request.
/*************************************************************************************/

#define EXT_INT0			0U
#define EXT_INT1			1U
#define EXT_INT2			2U
/*************************************************************************************/
/*- Function Declarations
-------------------------------*/
void EnableGlobalInterrupts(void);
void DisableGlobalInterrupts(void);

void DisableExternalInterrupts_INT0();
void EnableExternalInterrupts_INT0(uint8_t senseControl);
void setExtINT0Callback(pfINT0_CallBack_t FunToBeCalledInISR);

void DisableExternalInterrupts_INT2();
void EnableExternalInterrupts_INT2(uint8_t senseControl);
void setExtINT2Callback(pfINT2_CallBack_t FunToBeCalledInISR);

#endif /* ISR_H_ */
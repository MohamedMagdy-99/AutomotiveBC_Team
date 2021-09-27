/*****************************************************************************
* Module: Interrupt Handler Module
* File Name: Interrupt.h
* Description: Header file for Interrupt Handler
* Author: Ahnmed Nabil
* Date: 19-August-2021
******************************************************************************/


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "Std_types.h"
#include "Platform_Types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pf_Vector)(void);
typedef void (*pf_CallBack)(uint8_t);
#define VECTORS_NUM     20U

/*- Vector Table
-------------------------------*/
#define INT0_INT         __vector_1					//External Interrupt Request 0
#define INT1_INT          __vector_2					//External Interrupt Request 1
#define INT2_INT 		 __vector_3					//External Interrupt Request 2
#define TIMER2_COMP	 __vector_4					//Timer/Counter2 Compare Match
#define TIMER2_OVF	 __vector_5					//Timer/Counter2 Overflow
#define TIMER1_CAPT	 __vector_6  				//Timer/Counter1 Capture Event

#if USING_FREE_RTOS
#else
#define TIMER1_COMPA __vector_7					//Timer/Counter1 Compare Match A
#endif

#define TIMER1_COMPB __vector_8					//Timer/Counter1 Compare Match B
#define TIMER1_OVF	 __vector_9					//Timer/Counter1 Overflow
#define TIMER0_COMP	 __vector_10				//Timer/Counter0 Compare Match
#define TIMER0_OVF	 __vector_11				//Timer/Counter0 Overflow
#define SPI_STC		 __vector_12				//SPI Serial Transfer Complete
#define USART_RXC	 __vector_13				//USART, Rx Complete
#define USART_UDRE	 __vector_14				//USART Data Register Empty
#define USART_TXC	 __vector_15				//USART, Tx Complete
#define ADC_INT			 __vector_16				//ADC Conversion Complete
#define EE_RDY		 __vector_17				//EEPROM Ready
#define ANA_COMP	 __vector_18				//Analog Comparator
#define TWI			 __vector_19				//Two-wire Serial Interface
#define SPM_RDY		 __vector_20				//Store Program Memory Ready

#define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,used)) __VA_ARGS__; \
void vector (void)


/*- Function Declarations
-------------------------------*/
void IntDefaultHandler(uint8_t Int_ID);

extern pf_CallBack old_Vectors[VECTORS_NUM];
#endif /* INTERRUPT_H_ */
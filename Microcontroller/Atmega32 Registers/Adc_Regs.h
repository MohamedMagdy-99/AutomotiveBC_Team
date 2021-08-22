/*****************************************************************************
* Module: Adc Module
* File Name: Adc_Regs.h
* Description: Header file for Adc Module
* Author: Mohamed Magdy
* Date: 25-July-2021
******************************************************************************/


#ifndef ADC_REGS_H_
#define ADC_REGS_H_

#include "Std_Types.h"

/* ADMUX – ADC Multiplexer Selection Register */

#define ADMUX_R		(*(volatile uint8_t * const)0x27)

#define MUX0_B				0
#define MUX1_B 				1
#define MUX2_B 				2
#define MUX3_B 				3
#define MUX4_B 				4
#define ADLAR_B 			5
#define REFS0_B 			6
#define REFS1_B				7
/*************************************************************/
/*************************************************************/
/* ADCSRA – ADC Control and Status Register A*/


#define ADCSRA_R		(*(volatile uint8_t * const)0x26)

#define ADPS0_B				0
#define ADPS1_B				1
#define ADPS2_B 			2
#define ADIE_B 				3
#define ADIF_B 				4
#define ADATE_B 			5
#define ADSC_B 				6
#define ADEN_B				7
/*************************************************************/
/*************************************************************/

/* ADCL – ADC Data Register Low (ADLAR=0) */

#define ADCL_R		(*(volatile uint8_t * const)0x24)

#define ADC0_B				0
#define ADC1_B 				1
#define ADC2_B 				2
#define ADC3_B				3
#define ADC4_B				4
#define ADC5_B				5
#define ADC6_B				6
#define ADC7_B				7
/*************************************************************/
/* ADCH – ADC Data Register High (ADLAR=0) */

#define ADCH_R		(*(volatile uint8_t * const)0x25)

#define ADC8_B				0
#define ADC9_B 				1

/*************************************************************/
/* ADCL – ADC Data Register Low (ADLAR=1)*/

#define ADCL_ADLAR_1_R		(*(volatile uint8_t * const)0x24)

#define ADC0_B_ADCL_ADLAR_1				6
#define ADC1_B_ADCL_ADLAR_1				7

/*************************************************************/
/* ADCH – ADC Data Register High (ADLAR=1) */

#define ADCH_ADLAR_1_R		(*(volatile uint8_t * const)0x25)

#define ADC2_B_ADCH_ADLAR_1				0
#define ADC3_B_ADCH_ADLAR_1 			1
#define ADC4_B_ADCH_ADLAR_1 			2
#define ADC5_B_ADCH_ADLAR_1				3
#define ADC6_B_ADCH_ADLAR_1				4
#define ADC7_B_ADCH_ADLAR_1				5
#define ADC8_B_ADCH_ADLAR_1				6
#define ADC9_B_ADCH_ADLAR_1				7

/*************************************************************/
/* SFIOR – Special Function IO Register */

#define SFIOR_R		(*(volatile uint8_t * const)0x50)

#define ADTS0_B 				5
#define ADTS1_B					6
#define ADTS2_B					7

#endif /* ADC_REGS_H_ */
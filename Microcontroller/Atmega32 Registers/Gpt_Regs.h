/*****************************************************************************
* Module: Microcontroller Module
* File Name: Gpt_Regs.h
* Description: Source file for Microcontroller Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/

#ifndef GPT_REGS_H_
#define GPT_REGS_H_
#include "..\Std_Types.h"
/* Timers registers and bits */

#define TIMSK_R		(*(volatile uint8_t * const)0x0059)

#define TOIE0_B		0		/* Timer 0 */
#define OCIE0_B		1		/* Timer 0 */

#define TOIE1_B		2		/* Timer 1 */
#define OCIE1B_B	3		/* Timer 1 */
#define OCIE1A_B	4		/* Timer 1 */
#define TICIE1_B	5		/* Timer 1 */

#define TOIE2_B		6		/* Timer 2 */
#define OCIE2_B		7		/* Timer 2 */
/*************************************************************/
/*************************************************************/

#define TIFR_R		(*(volatile uint8_t * const)0x0058)

#define TOV0_B		0		/* Timer 0 */
#define OCF0_B 		1		/* Timer 0 */

#define TOV1_B 		2		/* Timer 1 */
#define OCF1B_B 	3		/* Timer 1 */
#define OCF1A_B 	4		/* Timer 1 */
#define ICF1_B 		5		/* Timer 1 */

#define TOV2_B 		6		/* Timer 2 */
#define OCF2_B		7		/* Timer 2 */
/*************************************************************/
/*************************************************************/

/* Timer 0 */

#define TCCR0_R		(*(volatile uint8_t * const)0x0053)

#define CS00_B		0
#define CS01_B		1
#define CS02_B		2
#define WGM01_B		3
#define COM00_B		4
#define COM01_B		5
#define WGM00_B		6
#define FOC0_B		7

#define TCNT0_R		(*(volatile uint8_t * const)0x0052)
#define OCR0_R		(*(volatile uint8_t * const)0x005C)
/*************************************************************/
/*************************************************************/

/* Timer 1 */

#define TCCR1A_R	(*(volatile uint8_t * const)0x004F)

#define WGM10_B		0
#define WGM11_B 	1
#define FOC1B_B		2
#define FOC1A_B		3
#define COM1B0_B	4
#define COM1B1_B	5
#define COM1A0_B	6
#define COM1A1_B	7

#define TCCR1B_R	(*(volatile uint8_t * const)0x004E)

#define CS10_B		0
#define CS11_B 		1
#define CS12_B 		2
#define WGM12_B		3
#define WGM13_B		4
#define ICES1_B		6
#define ICNC1_B		7

#define TCNT1_R		(*(volatile uint16_t * const)0x004C)
#define OCR1A_R		(*(volatile uint16_t * const)0x004A)
#define OCR1B_R		(*(volatile uint16_t * const)0x0048)
#define ICR1_R		(*(volatile uint16_t * const)0x0046)
/*************************************************************/
/*************************************************************/

/* Timer 2 */

#define TCCR2_R		(*(volatile uint8_t * const)0x0045)

#define CS20_B		0
#define CS21_B		1
#define CS22_B 		2
#define WGM21_B		3
#define COM20_B 	4
#define COM21_B		5
#define WGM20_B 	6
#define FOC2_B		7

#define TCNT2_R		(*(volatile uint8_t * const)0x0044)
#define OCR2_R		(*(volatile uint8_t * const)0x0043)

#endif /* GPT_REGS_H_ */

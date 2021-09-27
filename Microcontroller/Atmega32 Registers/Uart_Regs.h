/******************************************************************************
 *
 * Module: Uart - Registers
 *
 * File Name: Uart_Regs.h
 *
 * Description: Uart Registers
 *
 * Author: Mohamed Magdy
 *
 * Date: 19-July-2021
 *******************************************************************************/



#ifndef UART_REGS_H_
#define UART_REGS_H_

#include "Microcontroller/Std_Types.h"

/* USART I/O Data Registers */

#define UDR_R		(*(volatile uint8_t * const)0x2C)

/*************************************************************/
/*************************************************************/
/* UCSRC – USART Control and Status Register C */


#define UCSRC_R		(*(volatile uint8_t * const)0x40)

#define UCPOL_B			0		
#define UCSZ0_B 		1		
#define UCSZ1_B 		2		
#define USBS_B 			3		
#define UPM0_B 			4		
#define UPM1_B 			5		
#define UMSEL_B 		6		
#define URSEL_B			7		
/*************************************************************/
/*************************************************************/

/*************************************************************/
/* UCSRA – USART Control and Status Register A */

#define UCSRA_R		(*(volatile uint8_t * const)0x2B)

#define MPCM_B			0
#define U2X_B 			1
#define PE_B 			2
#define DOR_B 			3
#define FE_B 			4
#define UDRE_B 			5
#define TXC_B 			6
#define RXC_B			7
/*************************************************************/
/*************************************************************/
/*************************************************************/
/* UCSRB – USART Control and Status Register B */

#define UCSRB_R		(*(volatile uint8_t * const)0x2A)

#define TXB8_B			0
#define RXB8_B 			1
#define UCSZ2_B 		2
#define TXEN_B 			3
#define RXEN_B 			4
#define UDRIE_B 		5
#define TXCIE_B 		6
#define RXCIE_B			7
/*************************************************************/
/*************************************************************/
/* Baud Rate Registers */

#define UBRRL_R		(*(volatile uint8_t * const)0x29)
#define UBRRH_R		(*(volatile uint8_t * const)0x40)

#endif /* UART_REGS_H_ */
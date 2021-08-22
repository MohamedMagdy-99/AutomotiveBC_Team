/******************************************************************************
 *
 * Module: I2C - Registers
 *
 * File Name: I2C_Regs.h
 *
 * Description: I2C Registers
 *
 * Author: Mohamed Magdy
 *
 * Date: 21-July-2021
 *******************************************************************************/



#ifndef  I2C_REGS_H_
#define  I2C_REGS_H_

#include "Std_Types.h"

/* TWBR – TWI Bit Rate Register */

#define TWBR_R		(*(volatile uint8_t * const)0x20)

#define TWBR0_B				0
#define TWBR1_B 			1
#define TWBR2_B 			2
#define TWBR3_B 			3
#define TWBR4_B 			4
#define TWBR5_B 			5
#define TWBR6_B 			6
#define TWBR7_B				7
/*************************************************************/
/*************************************************************/
/* TWCR – TWI Control Register */


#define TWCR_R		(*(volatile uint8_t * const)0x56)

#define TWIE_B				0		
	
#define TWEN_B 				2		
#define TWWC_B 				3		
#define TWSTO_B 			4		
#define TWSTA_B 			5		
#define TWEA_B 				6		
#define TWINT_B				7		
/*************************************************************/
/*************************************************************/

/* TWSR – TWI Status Register */

#define TWSR_R		(*(volatile uint8_t * const)0x21)

#define TWPS0_B				0
#define TWPS1_B 			1

#define TWS0_B 				3
#define TWS1_B 				4
#define TWS2_B 				5
#define TWS3_B				6
#define TWS4_B				7
/*************************************************************/
/* TWAR – TWI (Slave) Address Register */

#define TWAR_R		(*(volatile uint8_t * const)0x22)

#define TWGCE_B				0
#define TWA0_B 				1
#define TWA1_B 				2	
#define TWA2_B 				3
#define TWA3_B 				4
#define TWA4_B 				5
#define TWA5_B				6
#define TWA6_B				7
/*************************************************************/
/* TWDR – TWI Data Register */

#define TWDR_R		(*(volatile uint8_t * const)0x23)

#define TWD0_B				0
#define TWD1_B 				1
#define TWD2_B 				2
#define TWD3_B 				3
#define TWD4_B 				4
#define TWD5_B 				5
#define TWD6_B				6
#define TWD7_B				7
#endif /*  I2C_REGS_H_ */
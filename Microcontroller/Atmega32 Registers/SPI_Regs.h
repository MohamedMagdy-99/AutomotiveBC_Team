/******************************************************************************
 *
 * Module: SPI - Registers
 *
 * File Name: Spi_Regs.h
 *
 * Description: Spi Registers
 *
 * Author: Mohamed Magdy
 *
 * Date: 20-July-2021
 *******************************************************************************/



#ifndef  SPI_REGS_H_
#define  SPI_REGS_H_

#include "Std_Types.h"

/* SPI Data Register is a read/write register */

#define SPDR_R		(*(volatile uint8_t * const)0x2F)

/*************************************************************/
/*************************************************************/
/* SPI Control Register */


#define SPCR_R		(*(volatile uint8_t * const)0x2D)

#define SPR0_B			0		
#define SPR1_B 			1		
#define CPHA_B 			2		
#define CPOL_B 			3		
#define MSTR_B 			4		
#define DORD_B 			5		
#define SPE_B 			6		
#define SPIE_B			7		
/*************************************************************/
/*************************************************************/

/* SPI Status Register */

#define SPSR_R		(*(volatile uint8_t * const)0x2E)

#define SPI2X_B			0
#define WCOL_B 			6
#define SPIF_B			7
/*************************************************************/


#endif /*  SPI_REGS_H_ */
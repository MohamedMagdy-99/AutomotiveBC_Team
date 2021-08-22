/******************************************************************************
 *
 * Module: Dio - Registers
 *
 * File Name: Dio_Regs.h
 *
 * Description: Dio Registers
 *
 * Author: Ahmed Nabil
 *
 * Date: 14-July-2021
 *******************************************************************************/

#ifndef PORT_REG_H_
#define PORT_REG_H_

#include "../Std_Types.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*-*-*-*-*-*-*-*- DIO REGISTERS -*-*-*-*-*-*-*-*-*-*-*-*/
/*-* PORT A Registers *-*/
#define DIO_PORTA_DATA			(*((volatile uint8_t*)(0x3B)))
#define DIO_PORTA_DIR			(*((volatile uint8_t*)(0x3A)))
#define DIO_PORTA_PIN			(*((volatile uint8_t*)(0x39)))

/*-* PORT B Registers *-*/
#define DIO_PORTB_DATA			(*((volatile uint8_t*)(0x38)))
#define DIO_PORTB_DIR			(*((volatile uint8_t*)(0x37)))
#define DIO_PORTB_PIN			(*((volatile uint8_t*)(0x36)))

/*-* PORT C Registers *-*/
#define DIO_PORTC_DATA			(*((volatile uint8_t*)(0x35)))
#define DIO_PORTC_DIR			(*((volatile uint8_t*)(0x34)))
#define DIO_PORTC_PIN			(*((volatile uint8_t*)(0x33)))

/*-* PORT D Registers *-*/
#define DIO_PORTD_DATA			(*((volatile uint8_t*)(0x32)))
#define DIO_PORTD_DIR			(*((volatile uint8_t*)(0x31)))
#define DIO_PORTD_PIN			(*((volatile uint8_t*)(0x30)))

#endif /* PORT_REG_H_ */

/*
 * Dio_Cfg.h
 *
 * Created: 7/13/2021 7:54:56 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef DIO_CFG_H_
#define DIO_CFG_H_

#include "Dio_Regs.h"

#define DIO_USED_PINS_NUM					(23U)


/* DIO Configured Port ID's  */
#define DioConf_COL_1_PORT_NUM				PORT_C
#define DioConf_COL_2_PORT_NUM				PORT_C
#define DioConf_COL_3_PORT_NUM				PORT_C

#define DioConf_ROW_1_PORT_NUM				PORT_C
#define DioConf_ROW_2_PORT_NUM				PORT_C
#define DioConf_ROW_3_PORT_NUM				PORT_C
#define DioConf_ROW_4_PORT_NUM				PORT_A

#define DioConf_SEG_A_PORT_NUM				PORT_B
#define DioConf_SEG_B_PORT_NUM				PORT_B
#define DioConf_SEG_C_PORT_NUM				PORT_B
#define DioConf_SEG_D_PORT_NUM				PORT_B

#define DioConf_SEG_1_EN_PORT_NUM			PORT_D
#define DioConf_SEG_2_EN_PORT_NUM			PORT_D

#define DioConf_LCD_RS_PORT_NUM				PORT_A
#define DioConf_LCD_RW_PORT_NUM				PORT_A
#define DioConf_LCD_EN_PORT_NUM				PORT_A
#define DioConf_LCD_D4_PORT_NUM				PORT_A
#define DioConf_LCD_D5_PORT_NUM				PORT_A
#define DioConf_LCD_D6_PORT_NUM				PORT_A
#define DioConf_LCD_D7_PORT_NUM				PORT_A

#define DioConf_PORTD4_PORT_NUM				PORT_D
#define DioConf_PORTD5_PORT_NUM				PORT_D

#define DioConf_PWM_B5_PORT_NUM				PORT_B
/* DIO Configured Channel ID's */
#define DioConf_COL_1_PIN_NUM				PIN_5
#define DioConf_COL_2_PIN_NUM				PIN_6
#define DioConf_COL_3_PIN_NUM				PIN_7

#define DioConf_ROW_1_PIN_NUM				PIN_2
#define DioConf_ROW_2_PIN_NUM				PIN_3
#define DioConf_ROW_3_PIN_NUM				PIN_4
#define DioConf_ROW_4_PIN_NUM				PIN_0

#define DioConf_SEG_A_PIN_NUM				PIN_0
#define DioConf_SEG_B_PIN_NUM				PIN_1
#define DioConf_SEG_C_PIN_NUM				PIN_2
#define DioConf_SEG_D_PIN_NUM				PIN_3

#define DioConf_SEG_1_EN_PIN_NUM			PIN_2
#define DioConf_SEG_2_EN_PIN_NUM			PIN_3

#define DioConf_LCD_RS_PIN_NUM				PIN_1
#define DioConf_LCD_RW_PIN_NUM				PIN_2
#define DioConf_LCD_EN_PIN_NUM				PIN_3
#define DioConf_LCD_D4_PIN_NUM				PIN_4
#define DioConf_LCD_D5_PIN_NUM				PIN_5
#define DioConf_LCD_D6_PIN_NUM				PIN_6
#define DioConf_LCD_D7_PIN_NUM				PIN_7


#define DioConf_PORTD4_PIN_NUM				PIN_4
#define DioConf_PORTD5_PIN_NUM				PIN_5
#define DioConf_PWM_B5_PIN_NUM				PIN_5
/* Channel Index in the array of structures in Dio_Cfg.c */

#define DIO_COL_1_CHANNEL_ID				0
#define DIO_COL_2_CHANNEL_ID				1
#define DIO_COL_3_CHANNEL_ID				2

#define DIO_ROW_1_CHANNEL_ID				3
#define DIO_ROW_2_CHANNEL_ID				4
#define DIO_ROW_3_CHANNEL_ID				5

#define DIO_SEG_A_CHANNEL_ID				6
#define DIO_SEG_B_CHANNEL_ID				7
#define DIO_SEG_C_CHANNEL_ID				8
#define DIO_SEG_D_CHANNEL_ID				9

#define DIO_SEG_1_EN_CHANNEL_ID				10
#define DIO_SEG_2_EN_CHANNEL_ID				11

#define DIO_ROW_4_CHANNEL_ID				12


#define DIO_LCD_RS_CHANNEL_ID				13
#define DIO_LCD_RW_CHANNEL_ID				14
#define DIO_LCD_E_CHANNEL_ID				15

#define DIO_LCD_D4_CHANNEL_ID				16
#define DIO_LCD_D5_CHANNEL_ID				17
#define DIO_LCD_D6_CHANNEL_ID				18
#define DIO_LCD_D7_CHANNEL_ID				19


#define DIO_PORTD4_CHANNEL_ID				20
#define DIO_PORTD5_CHANNEL_ID				21
#define DIO_PWM_CHANNEL_ID					22
#endif /* DIO_CFG_H_ */
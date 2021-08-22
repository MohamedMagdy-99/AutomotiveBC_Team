/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd_Cfg.h
* Description: Header file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/* Async Cfg */
#define AsyncMode					TRUE
#define	DelayTicks_Commands			250
#define	DelayTicks_PowerUp			2500

#define TIMER_USED_ID		TIMER_CHANNEL_0_ID
/*********************************************/
#define LCD_ID_0			0U
#define Lcd_Rows			2
#define Lcd_Columns			16

#define RS_DIO_ID			DIO_LCD_RS_CHANNEL_ID	
#define RW_DIO_ID			DIO_LCD_RW_CHANNEL_ID	
#define EN_DIO_ID			DIO_LCD_E_CHANNEL_ID
								
#define D4_DIO_ID			DIO_LCD_D4_CHANNEL_ID
#define D5_DIO_ID			DIO_LCD_D5_CHANNEL_ID
#define D6_DIO_ID			DIO_LCD_D6_CHANNEL_ID
#define D7_DIO_ID			DIO_LCD_D7_CHANNEL_ID

#endif /* LCD_CFG_H_ */
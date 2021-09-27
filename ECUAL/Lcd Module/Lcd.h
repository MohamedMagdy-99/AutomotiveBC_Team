/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd.h
* Description: Header file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/* INCLUDES */

#include "../../Microcontroller/Platform_Types.h"
#include "../../Libraries/Common_Macros.h"
#include "../../MCAL/Dio Module/Dio.h"
#include "Lcd_Cfg.h"
#include "../../Microcontroller/Delay Module/Delay.h"
#include "../../Libraries/Utility Module/Utility.h"


#if (AsyncMode == TRUE)
	#include "../../MCAL/Gpt Module/Gpt.h"
#endif


/* CONSTANTS */
/* Commands */
#define CLEAR						0x01
#define HOME						0x02
#define ENTRY_MODE					0x06
#define DISPLAY_ON					0x0C
#define	DISPLAY_OFF					0x08
#define LINES_2_FONT_5x8			0x28
#define INIT_4BITS_COMMAND_1		0x33
#define INIT_4BITS_COMMAND_2		0x32

/* states when using async mode */
#if (AsyncMode == TRUE)
	#define IDLE						7
	#define RUNNING						6
	#define CLEAR_DISPLAY_PENDING		2
	#define SET_CURSOR_PENDING			3
	#define SEND_STRING_PENDING			4
	#define SEND_INT_PENDING			5
#endif
/*- ENUMS --------------------------------------------------*/
typedef enum
{
	LCD_STATUS_ERROR_NOK,
	LCD_STATUS_ERROR_OK

}enuLcd_Status_t;

typedef enum
{
	LCD_INITIALIZED,
	LCD_NOT_INITIALIZED
}enuLcd_initStatus_t;
/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/
enuLcd_Status_t Lcd_toggleEnable(void);
enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data);
enuLcd_Status_t Lcd_sendCharacter(uint8_t u8_char);
enuLcd_Status_t Lcd_sendString(uint8_t* au8_string);
enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis);
enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command);
enuLcd_Status_t Lcd_init(void);
enuLcd_Status_t Lcd_clearDisplay(void);
enuLcd_Status_t Lcd_sendHigherNibble(uint8_t u8_data);
enuLcd_Status_t Lcd_sendLowerNibble(uint8_t u8_data);

enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base); 

#if (AsyncMode == TRUE)
	void LcdDelayFinished(uint8_t Id);
	void LcdPoweringUpFinished(uint8_t Id);
#endif

#if(AsyncMode == FALSE)
	enuLcd_Status_t Lcd_pingPongStringR1(uint8_t* au8_string, uint8_t u8_numChars);
	enuLcd_Status_t Lcd_pingPongStringR2(uint8_t* au8_string, uint8_t u8_numChars);	
#endif	

enuLcd_Status_t Lcd_init_test(void);
enuLcd_Status_t Lcd_sendCommand_test(uint8_t u8_command);
enuLcd_Status_t Lcd_sendData_4bitMode_test(uint8_t u8_data);

#endif /* LCD_H_ */
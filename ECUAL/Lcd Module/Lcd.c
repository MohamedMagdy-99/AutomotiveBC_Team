/*****************************************************************************
* Module: Lcd Module
* File Name: Lcd.c
* Description: Source file for Lcd Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Lcd.h"

/*- INCLUDES
----------------------------------------------*/
#define LEFT		(0x00U)
#define RIGHT		(0x01U)


/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
enuLcd_Status_t Lcd_Status = LCD_STATUS_ERROR_OK;
enuLcd_initStatus_t Lcd_Init = LCD_NOT_INITIALIZED;

/* states */
#if (AsyncMode == TRUE)
uint8_t LCD_NEXT_STATE = IDLE;
uint8_t LCD_SEND_STRING_STATE = IDLE;
uint8_t LCD_CLEAR_DISPLAY_STATE = IDLE;
uint8_t LCD_SET_CURSOR_STATE = IDLE;
uint8_t LCD_SEND_COMMAND_STATE = IDLE;
uint8_t LCD_SENDING_INT_STATE = IDLE;

uint8_t LCD_SENDING_CHAR_FOR_INT_STATE = IDLE;
uint8_t LCD_SENDING_CHAR_FOR_STRING_STATE = IDLE;

uint8_t Lcd_Init_DoneFlag = FALSE;
uint8_t Lcd_PoweringUp_Flag = FALSE;

uint8_t gau8_currentString[Lcd_Columns];
uint8_t gau8_nextString[Lcd_Columns];
uint8_t gau8_currentInteger[6];

uint8_t gu8_currentX = Initial_Value;
uint8_t gu8_currentY = Initial_Value;

#define LCD_INIT_4BITS_COMMAND_1_ID			1
#define LCD_INIT_4BITS_COMMAND_2_ID			2
#define LCD_LINES_2_FONT_5x8_COMMAND_ID		3
#define LCD_DISPLAY_OFF_COMMAND_ID			4
#define LCD_CLEAR_COMMAND_ID				5
#define LCD_ENTRY_MODE_COMMAND_ID			6
#define LCD_DISPLAY_ON_COMMAND_ID			7

uint8_t gu8_currentlyRunningCommand = LCD_INIT_4BITS_COMMAND_1_ID;

/* one time strings option, to be redesigned later in cfg.c */
uint8_t gau8_oneTimeString_1[11] = "Distance:";

uint8_t gu8_oneTimeString_1_Flag = FALSE;
#endif

#if (AsyncMode == FALSE)
uint8_t gau8_currentStringR1[Lcd_Columns] = "DEFAULT1";
uint8_t gau8_currentStringR2[Lcd_Columns] = "DEFAULT2";
#endif
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/************************************************************************************************************************/
/*********************************************** BLOCKING APIS **********************************************************/
/************************************************************************************************************************/

#if (AsyncMode == FALSE)
enuLcd_Status_t Lcd_init(void)
{
	if(Lcd_Init == LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	Dio_init(strDio_pins);
	
	Delay_ms(20);
	//Activate 4 bit mode
	Lcd_sendCommand(INIT_4BITS_COMMAND_1);
	Lcd_sendCommand(INIT_4BITS_COMMAND_2);
	
	//Function Set (2 lines & 5x8 font)
	Lcd_sendCommand(LINES_2_FONT_5x8);
	
	//Display OFF
	Lcd_sendCommand(DISPLAY_OFF);
	
	//Clear Display
	Lcd_sendCommand(CLEAR);
	
	//Entry Mode Set
	Lcd_sendCommand(ENTRY_MODE);
	
	//Display ON
	Lcd_sendCommand(DISPLAY_ON);
	
	Lcd_Init = LCD_INITIALIZED;
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
{
	Lcd_sendHigherNibble(u8_data);							//send higher nibble
	Lcd_toggleEnable();		//toggle enable
	
	Lcd_sendLowerNibble(u8_data);							//send lower nibble
	Lcd_toggleEnable();		//toggle enable
	
	Delay_ms(2);
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
{
	uint8_t au8_positions[4] = {0, 64, Lcd_Columns, Lcd_Columns+64};
	
	Lcd_sendCommand(0x80+au8_positions[u8_xAxis-1]+(u8_yAxis-1));
	
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_clearDisplay(void)
{
	Lcd_sendCommand(CLEAR);
	return LCD_STATUS_ERROR_OK;
}


enuLcd_Status_t Lcd_sendString(uint8_t* au8_string)
{
	uint8_t u8_loopCounter = Initial_Value;
	for (u8_loopCounter=Initial_Value;au8_string[u8_loopCounter]!='\0';u8_loopCounter++)
	{
		Lcd_sendCharacter(au8_string[u8_loopCounter]);
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
{
	
	Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
	
	Lcd_sendData_4bitMode(u8_command);
	
	return LCD_STATUS_ERROR_OK;
}
enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base)
{
	uint8_t pu8_String[6];
	integerToString(u16_number, pu8_String, u8_base);
	
	Lcd_sendString(pu8_String);
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_pingPongStringR1(uint8_t* au8_string, uint8_t u8_numChars)
{
	STATIC uint8_t columnPosition_R = 1;
	STATIC uint8_t columnPosition_L = 1;
	STATIC uint8_t u8_RightLeftShiftFlag = RIGHT;
	
	if(stringCmp((uint8_t*)"DEFAULT", gau8_currentStringR1) == TRUE)
	{
		stringCopy(au8_string, gau8_currentStringR1);
	}
	else
	{
		if(stringCmp(au8_string, gau8_currentStringR1) == FALSE)
		{
			/* reset fun parameters */
		   EmptyString(gau8_currentStringR1);
		   stringCopy(au8_string, gau8_currentStringR1);
		   columnPosition_R = 1;
		   columnPosition_L = 1;
		   u8_RightLeftShiftFlag = RIGHT;
		   Lcd_cursorPosition(1, 1);
		   Lcd_sendString((uint8_t*)"                ");
			
		}
	}
	
	
	if(u8_RightLeftShiftFlag == RIGHT)
	{

		Lcd_cursorPosition(1, columnPosition_R-1);
		Lcd_sendCharacter(' ');
		Lcd_cursorPosition(1, columnPosition_R);
		Lcd_sendString(gau8_currentStringR1);
		if(columnPosition_R == (Lcd_Columns-u8_numChars)+1)
		{
			columnPosition_L = (Lcd_Columns-u8_numChars);
			u8_RightLeftShiftFlag = LEFT;	
		}
		columnPosition_R++;
		//Delay_ms(R1_PINGPONG_MS);		
	}
	else if(u8_RightLeftShiftFlag == LEFT)
	{

		Lcd_cursorPosition(1, columnPosition_L);
		Lcd_sendString(gau8_currentStringR1);
		Lcd_sendCharacter(' ');
		if(columnPosition_L == 1)
		{
			columnPosition_R = 1;
			u8_RightLeftShiftFlag = RIGHT;	
		}
		columnPosition_L--;
		//Delay_ms(R1_PINGPONG_MS);		
	}
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_pingPongStringR2(uint8_t* au8_string, uint8_t u8_numChars)
{
	STATIC uint8_t columnPosition_R = 1;
	STATIC uint8_t columnPosition_L = 1;
	STATIC uint8_t u8_RightLeftShiftFlag = RIGHT;
	
	if(stringCmp((uint8_t*)"DEFAULT", gau8_currentStringR2) == TRUE)
	{
		stringCopy(au8_string, gau8_currentStringR2);
	}
	else
	{
		if(stringCmp(au8_string, gau8_currentStringR2) == FALSE)
		{
			/* reset fun parameters */
			EmptyString(gau8_currentStringR2);
			stringCopy(au8_string, gau8_currentStringR2);
			columnPosition_R = 1;
			columnPosition_L = 1;
			u8_RightLeftShiftFlag = RIGHT;
			Lcd_cursorPosition(2, 1);
			Lcd_sendString((uint8_t*)"                ");
			
		}
	}
	
	
	if(u8_RightLeftShiftFlag == RIGHT)
	{

		Lcd_cursorPosition(2, columnPosition_R-1);
		Lcd_sendCharacter(' ');
		Lcd_cursorPosition(2, columnPosition_R);
		Lcd_sendString(gau8_currentStringR2);
		if(columnPosition_R == (Lcd_Columns-u8_numChars)+1)
		{
			columnPosition_L = (Lcd_Columns-u8_numChars);
			u8_RightLeftShiftFlag = LEFT;
		}
		columnPosition_R++;
		Delay_ms(R2_PINGPONG_MS);
	}
	else if(u8_RightLeftShiftFlag == LEFT)
	{

		Lcd_cursorPosition(2, columnPosition_L);
		Lcd_sendString(gau8_currentStringR2);
		Lcd_sendCharacter(' ');
		if(columnPosition_L == 1)
		{
			columnPosition_R = 1;
			u8_RightLeftShiftFlag = RIGHT;
		}
		columnPosition_L--;
		Delay_ms(R2_PINGPONG_MS);
	}
	return LCD_STATUS_ERROR_OK;
}
#endif




/************************************************************************************************************************/
/*********************************************** NON BLOCKING APIS ******************************************************/
/************************************************************************************************************************/

#if (AsyncMode == TRUE)
enuLcd_Status_t Lcd_init(void)
{
	if(Lcd_Init == LCD_INITIALIZED || LCD_SEND_COMMAND_STATE == RUNNING || Lcd_PoweringUp_Flag == RUNNING) return LCD_STATUS_ERROR_NOK;
	
	if(Lcd_Init_DoneFlag == TRUE)
	{
		Lcd_Init = LCD_INITIALIZED;
		return LCD_STATUS_ERROR_OK;
	}
	
	if(Lcd_PoweringUp_Flag == FALSE)
	{
		Dio_init(strDio_pins);
		GptInit();
		GptStart_aSync(TIMER_USED_ID, DelayTicks_PowerUp, LcdPoweringUpFinished);
		Lcd_PoweringUp_Flag = RUNNING;
		return LCD_STATUS_ERROR_OK;
	}
	
	
	switch(gu8_currentlyRunningCommand)
	{
		case(LCD_INIT_4BITS_COMMAND_1_ID):
		{
			//Activate 4 bit mode
			Lcd_sendCommand(INIT_4BITS_COMMAND_1);
			break;
		}
		case(LCD_INIT_4BITS_COMMAND_2_ID):
		{
			//Activate 4 bit mode
			Lcd_sendCommand(INIT_4BITS_COMMAND_2);
			break;
		}
		case(LCD_LINES_2_FONT_5x8_COMMAND_ID):
		{
			//Function Set (2 lines & 5x8 font)
			Lcd_sendCommand(LINES_2_FONT_5x8);
			break;
		}
		case(LCD_DISPLAY_OFF_COMMAND_ID):
		{
			//Display OFF
			Lcd_sendCommand(DISPLAY_OFF);
			break;
		}
		case(LCD_CLEAR_COMMAND_ID):
		{
			//Clear Display
			Lcd_sendCommand(CLEAR);
			break;
		}
		case(LCD_ENTRY_MODE_COMMAND_ID):
		{
			//Entry Mode Set
			Lcd_sendCommand(ENTRY_MODE);
			break;
		}
		case(LCD_DISPLAY_ON_COMMAND_ID):
		{
			//Display ON
			Lcd_sendCommand(DISPLAY_ON);
			break;
		}
		default: return LCD_STATUS_ERROR_NOK;
	}

	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_cursorPosition(uint8_t u8_xAxis, uint8_t u8_yAxis)
{
	if(Lcd_Init != LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SEND_STRING_STATE == RUNNING
	|| LCD_SENDING_INT_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			gu8_currentX = u8_xAxis;
			gu8_currentY = u8_yAxis;
			LCD_NEXT_STATE = SET_CURSOR_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == SET_CURSOR_PENDING)
	{
		if(gu8_currentX == u8_xAxis && gu8_currentY == u8_yAxis)
		{
			LCD_SET_CURSOR_STATE = RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}

	}
	else if(LCD_NEXT_STATE == SEND_STRING_PENDING || LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING
	|| LCD_NEXT_STATE == SEND_INT_PENDING)
	{
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == IDLE)
	{
		gu8_currentX = u8_xAxis;
		gu8_currentY = u8_yAxis;
		LCD_SET_CURSOR_STATE = RUNNING;
	}
	else
	{
		/* RUN */
	}
	
	uint8_t au8_positions[4] = {0, 64, Lcd_Columns, Lcd_Columns+64};
	Lcd_sendCommand(0x80+au8_positions[u8_xAxis-1]+(u8_yAxis-1));
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_clearDisplay(void)
{
	if(Lcd_Init != LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	if(LCD_SEND_STRING_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING
	|| LCD_SENDING_INT_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			LCD_NEXT_STATE = CLEAR_DISPLAY_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING)
	{
		LCD_CLEAR_DISPLAY_STATE = RUNNING;
		LCD_NEXT_STATE = IDLE;
	}
	else if(LCD_NEXT_STATE == SEND_STRING_PENDING || LCD_NEXT_STATE == SET_CURSOR_PENDING
	|| LCD_NEXT_STATE == SEND_INT_PENDING)
	{
		return LCD_STATUS_ERROR_NOK;
	}
	else if( LCD_NEXT_STATE == IDLE)
	{
		LCD_CLEAR_DISPLAY_STATE = RUNNING;
	}
	else
	{
		/* RUN */
	}
	
	Lcd_sendCommand(CLEAR);
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendString(uint8_t* au8_string)
{
	if(Lcd_Init != LCD_INITIALIZED) return LCD_STATUS_ERROR_NOK;
	
	static uint8_t u8_stringIndexCounter = Initial_Value;
	
	if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING 
	  || LCD_SENDING_INT_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			stringCopy(au8_string, gau8_nextString);
			LCD_NEXT_STATE = SEND_STRING_PENDING;
			
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == SEND_STRING_PENDING && LCD_SENDING_INT_STATE != RUNNING 
			&& LCD_SEND_STRING_STATE != RUNNING)
	{
		if(stringCmp(au8_string, gau8_nextString) == TRUE)
		{
			stringCopy(au8_string, gau8_currentString);
			EmptyString(gau8_nextString);
			LCD_SEND_STRING_STATE =  RUNNING;
			LCD_NEXT_STATE = IDLE;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}
	}
	else if((LCD_NEXT_STATE == SET_CURSOR_PENDING || LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING || LCD_NEXT_STATE == SEND_INT_PENDING)
			&& LCD_SEND_STRING_STATE != RUNNING)
	{
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == IDLE)
	{
		if(LCD_SEND_STRING_STATE == RUNNING)
		{
			stringCopy(au8_string, gau8_nextString);
			LCD_NEXT_STATE = SEND_STRING_PENDING;
			return LCD_STATUS_ERROR_OK;
		}
		else
		{
			stringCopy(au8_string, gau8_currentString);
			LCD_SEND_STRING_STATE = RUNNING;			
		}
	}
	else
	{
		/* RUN */
	}
	
	if(u8_stringIndexCounter != 0 && stringCmp(au8_string, gau8_currentString) == FALSE)
	{
		return LCD_STATUS_ERROR_NOK;
	}
	/******************** TEMP ********************/
 	if(gu8_oneTimeString_1_Flag == TRUE && stringCmp(au8_string, gau8_oneTimeString_1) == TRUE)
 	{
 		u8_stringIndexCounter = Initial_Value;
 		LCD_SEND_STRING_STATE = IDLE;
 		return LCD_STATUS_ERROR_NOK;
 	}
	/*********************************************/
	if(au8_string[u8_stringIndexCounter]!='\0')
	{
		if(LCD_SENDING_CHAR_FOR_STRING_STATE == IDLE)
		{
			LCD_SENDING_CHAR_FOR_STRING_STATE = RUNNING;
			Lcd_sendCharacter(au8_string[u8_stringIndexCounter]);
			u8_stringIndexCounter++;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}

	}
	else
	{
		u8_stringIndexCounter = Initial_Value;
		LCD_SEND_STRING_STATE = IDLE;
		
		/*********************** TEMP *********************************/
 		if(gu8_oneTimeString_1_Flag == FALSE)
 		{
 			if(stringCmp(gau8_currentString, gau8_oneTimeString_1) == TRUE)
 			{
 				gu8_oneTimeString_1_Flag = TRUE;
 				EmptyString(gau8_currentString);
 			}
 		}
		/**************************************************************/
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendVariableInt(uint16_t u16_number, uint8_t u8_base)
{
	if(Lcd_Init != LCD_INITIALIZED)
	return LCD_STATUS_ERROR_NOK;
	
	uint8_t au8_string[6];
	integerToString(u16_number, au8_string, u8_base);
	
	static uint8_t u8_integerIndexCounter = Initial_Value;
	
	if(LCD_CLEAR_DISPLAY_STATE == RUNNING || LCD_SET_CURSOR_STATE == RUNNING
	|| LCD_SEND_STRING_STATE == RUNNING)
	{
		if(LCD_NEXT_STATE == IDLE)
		{
			LCD_NEXT_STATE = SEND_INT_PENDING;
		}
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == SEND_INT_PENDING && LCD_SEND_STRING_STATE != RUNNING
			 && LCD_SENDING_INT_STATE != RUNNING)
	{
		stringCopy(au8_string, gau8_currentInteger);
		LCD_SENDING_INT_STATE = RUNNING;
		LCD_NEXT_STATE = IDLE;
	}
	else if((LCD_NEXT_STATE == SET_CURSOR_PENDING || LCD_NEXT_STATE == CLEAR_DISPLAY_PENDING || LCD_NEXT_STATE == SEND_STRING_PENDING)
			 && LCD_SENDING_INT_STATE != RUNNING)
	{
		return LCD_STATUS_ERROR_NOK;
	}
	else if(LCD_NEXT_STATE == IDLE)
	{
		if(LCD_SENDING_INT_STATE == RUNNING)
		{
			LCD_NEXT_STATE = SEND_INT_PENDING;
			return LCD_STATUS_ERROR_NOK;
		}
		else
		{
			stringCopy(au8_string, gau8_currentInteger);
			LCD_SENDING_INT_STATE = RUNNING;
		}

	}
	else
	{
		/* RUN */
	}
	
	if(gau8_currentInteger[u8_integerIndexCounter]!='\0')
	{
		if(LCD_SENDING_CHAR_FOR_INT_STATE == IDLE)
		{
			LCD_SENDING_CHAR_FOR_INT_STATE = RUNNING;
			Lcd_sendCharacter(gau8_currentInteger[u8_integerIndexCounter]);
			u8_integerIndexCounter++;
		}
		else
		{
			return LCD_STATUS_ERROR_NOK;
		}

	}
	else
	{
		u8_integerIndexCounter = Initial_Value;
		LCD_SENDING_INT_STATE = IDLE;

		EmptyString(gau8_currentInteger);
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendData_4bitMode(uint8_t u8_data)
{
	Lcd_sendHigherNibble(u8_data);							//send higher nibble
	Lcd_toggleEnable();		//toggle enable
	
	Lcd_sendLowerNibble(u8_data);							//send lower nibble
	Lcd_toggleEnable();		//toggle enable
	
	/* delay after byte sent */
	GptStart_aSync(TIMER_USED_ID, DelayTicks_Commands, LcdDelayFinished);
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendCommand(uint8_t u8_command)
{
	if(LCD_SEND_COMMAND_STATE == RUNNING) return LCD_STATUS_ERROR_NOK;
	LCD_SEND_COMMAND_STATE = RUNNING;
	
	Dio_writePin(RS_DIO_ID, STD_LOW);			//activate command mode
	
	Lcd_sendData_4bitMode(u8_command);
	
	return LCD_STATUS_ERROR_OK;
}

void LcdDelayFinished(uint8_t Id)
{
	if(Lcd_Init == LCD_NOT_INITIALIZED)
	{
		if(gu8_currentlyRunningCommand == LCD_DISPLAY_ON_COMMAND_ID)
		{
			/* if all commands done state module as initialized */
			Lcd_Init_DoneFlag = TRUE;
			LCD_SEND_COMMAND_STATE = IDLE;
		}
		else
		{
			gu8_currentlyRunningCommand++;
			LCD_SEND_COMMAND_STATE = IDLE;
		}
	}
	else
	{
		if(LCD_SET_CURSOR_STATE == RUNNING)
		{
			LCD_SET_CURSOR_STATE = IDLE;
			LCD_SEND_COMMAND_STATE = IDLE;
		}
		else if(LCD_CLEAR_DISPLAY_STATE == RUNNING)
		{
			LCD_CLEAR_DISPLAY_STATE = IDLE;
			LCD_SEND_COMMAND_STATE = IDLE;
		}
		else if(LCD_SEND_STRING_STATE == RUNNING)
		{
			LCD_SENDING_CHAR_FOR_STRING_STATE = IDLE;
		}
		else if(LCD_SENDING_INT_STATE == RUNNING)
		{
			LCD_SENDING_CHAR_FOR_INT_STATE = IDLE;
		}
	}

}

void LcdPoweringUpFinished(uint8_t Id)
{
	Lcd_PoweringUp_Flag = TRUE;
}
#endif





/************************************************************************************************************************/
/*********************************************** COMMON APIS ************************************************************/
/************************************************************************************************************************/


enuLcd_Status_t Lcd_toggleEnable(void)
{
	Dio_writePin(EN_DIO_ID, STD_HIGH);		//set enable ON
	Delay_ms(1);
	Dio_writePin(EN_DIO_ID, STD_LOW);		//set enable OFF
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendCharacter(uint8_t u8_char)
{
	Dio_writePin(RS_DIO_ID, STD_HIGH);		//activate DATA mode
	Lcd_sendData_4bitMode(u8_char);
	return LCD_STATUS_ERROR_OK;
}



enuLcd_Status_t Lcd_sendLowerNibble(uint8_t u8_data)
{
	if((u8_data & 0x01) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x02) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x04) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x08) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;
}

enuLcd_Status_t Lcd_sendHigherNibble(uint8_t u8_data)
{
	if((u8_data & 0x10) != 0)
	{
		Dio_writePin(D4_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D4_DIO_ID, STD_LOW);
	}

	if((u8_data & 0x20) != 0)
	{
		Dio_writePin(D5_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D5_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x40) != 0)
	{
		Dio_writePin(D6_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D6_DIO_ID, STD_LOW);
	}
	
	if((u8_data & 0x80) != 0)
	{
		Dio_writePin(D7_DIO_ID, STD_HIGH);
	}
	else
	{
		Dio_writePin(D7_DIO_ID, STD_LOW);
	}
	
	return LCD_STATUS_ERROR_OK;
}











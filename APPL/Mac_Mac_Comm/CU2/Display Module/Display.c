/*
 * Display.c
 *
 * Created: 13/8/2021 11:15:40 AM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Display.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the state of the Module
 */
#define DISPLAY_STATUS_UNINIT		0U
#define DISPLAY_STATUS_INIT			1U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL SHARED VARIABLES *-*-*-*-*-*/
/* ping pong R1 variables */
uint8_t gau8_pingPongR1String[16] = "SYS LOADING";
uint8_t gu8_pingPongR1NumChars = 11;
/* SS variable */
uint8_t gu8_dual_7SegNum;
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/

/* Holds the status of the Display Module */
Display_State_t DisplayModuleStatus_gu8 = DISPLAY_STATUS_UNINIT;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function to Initialize the Sensing module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to initialize the Display module */
Std_ReturnType Display_init(void)
{
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	if(DisplayModuleStatus_gu8 == DISPLAY_STATUS_INIT)
	{


	}
	else
	{
		/* Initialize the Display Module */
		Lcd_init();
		SS_Init();
		DisplayModuleStatus_gu8 = DISPLAY_STATUS_INIT;	
	}


	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_printString
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DisplayID_u8 - ID for the Display Device to print.
*				   StringToPrint_pu8 - Pointer to a string to be printed on the screen
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to display an input from the application on a Display Screen with the given ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_printString(uint8_t DisplayID_u8, uint8_t *StringToPrint_pu8)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the pointer variable is NULL */
	if (NULL_PTR == StringToPrint_pu8)
	{
		return E_NOT_OK;
	}else{/*Nothing to do here*/}
		
	if(DisplayID_u8 >= DISPLAY_ID_INVALID)
	{
		return E_NOT_OK;
	}

/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	else
	{
		switch(DisplayID_u8)
		{
			case(DISPLAY_LCD_16x2_ID):
			{
				Lcd_sendString(StringToPrint_pu8);
				break;
			}
			case(DISPLAY_7SEG_DUAL_ID):
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	return E_NOT_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_printChar
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DisplayID_u8 - ID for the Display Device to print.
*				   StringToPrint_pu8 - Pointer to a string to be printed on the screen
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to display an input from the application on a Display Screen with the given ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_printChar(uint8_t DisplayID_u8, uint8_t CharToPrint_u8)
{
	/**************************************************************************************/
	/*								Start of Error Checking								  */
	/**************************************************************************************/
		if(DisplayID_u8 >= DISPLAY_ID_INVALID)
		{
			return E_NOT_OK;
		}

		/**************************************************************************************/
		/*								End of Error Checking								  */
		/**************************************************************************************/

		/**************************************************************************************/
		/*								Function Implementation								  */
		/**************************************************************************************/
		else
		{
			switch(DisplayID_u8)
			{
				case(DISPLAY_LCD_16x2_ID):
				{
					Lcd_sendCharacter(CharToPrint_u8);
					break;
				}
				case(DISPLAY_7SEG_DUAL_ID):
				{
					break;
				}
				default:
				{
					break;
				}
			}
		}
		
		return E_NOT_OK;
	}
	
	

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_printChar
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DisplayID_u8 - ID for the Display Device to print.
*				   StringToPrint_pu8 - Pointer to a string to be printed on the screen
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to display an input from the application on a Display Screen with the given ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_clearDisplay(uint8_t DisplayID_u8)
{
	/**************************************************************************************/
	/*								Start of Error Checking								  */
	/**************************************************************************************/
	if(DisplayID_u8 >= DISPLAY_ID_INVALID)
	{
		return E_NOT_OK;
	}

	/**************************************************************************************/
	/*								End of Error Checking								  */
	/**************************************************************************************/

	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	else
	{
		switch(DisplayID_u8)
		{
			case(DISPLAY_LCD_16x2_ID):
			{
				Lcd_clearDisplay();
				break;
			}
			case(DISPLAY_7SEG_DUAL_ID):
			{
				
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	return E_NOT_OK;
}	
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_printInteger
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DisplayID_u8 - ID for the Display Device to print.
*				   u16_number - Decimal Number to print on the LCD
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to display an input from the application on a Display Screen with the given ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_printInteger(uint8_t DisplayID_u8, uint16_t u16_number)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	if(DisplayID_u8 >= DISPLAY_ID_INVALID)
	{
		return E_NOT_OK;
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	else
	{
		switch(DisplayID_u8)
		{
			case(DISPLAY_LCD_16x2_ID):
			{
				Lcd_sendVariableInt(u16_number, DEC);
				break;
			}
			case(DISPLAY_7SEG_DUAL_ID):
			{
				SS_sendNumber_Two7Seg(SEG_1_ID, SEG_1_ID, u16_number, SEG_SWAP_DELAY_MS);
				break;
			}
			default:
			{
				break;
			}
		}
	}
				
	return E_NOT_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_setCursor
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): DisplayID_u8 - ID for the Display Device to print.
*				   u16_number - Decimal Number to print on the LCD
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to set cursor position on a Display Screen with the given ID
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_setCursor(uint8_t DisplayID_u8, uint8_t xAxis, uint8_t yAxis)
{
	/**************************************************************************************/
	/*								Start of Error Checking								  */
	/**************************************************************************************/
	if(DisplayID_u8 >= DISPLAY_ID_INVALID)
	{
		return E_NOT_OK;
		}
		/**************************************************************************************/
		/*								End of Error Checking								  */
		/**************************************************************************************/

		/**************************************************************************************/
		/*								Function Implementation								  */
		/**************************************************************************************/
	else
	{
		switch(DisplayID_u8)
		{
			case(DISPLAY_LCD_16x2_ID):
			{
				Lcd_cursorPosition(xAxis, yAxis);
				break;
			}
			case(DISPLAY_7SEG_DUAL_ID):
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
		
		return E_NOT_OK;
	}
	
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_Lcd_mainFunction
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Periodic function/task of the module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void Display_Lcd_mainFunction(void *pvParameters)
{
	while(TRUE)
	{
		Lcd_pingPongStringR1(gau8_pingPongR1String, gu8_pingPongR1NumChars);
		vTaskDelay(R1_PINGPONG_MS);
	}
}


Std_ReturnType Display_Lcd_setPingPongR1Info(uint8_t* au8_string, uint8_t u8_numChars)
{
	gu8_pingPongR1NumChars = u8_numChars;
	EmptyString(gau8_pingPongR1String);
	stringCopy(au8_string, gau8_pingPongR1String);
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_7Seg_mainFunction
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Periodic function/task of the module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void Display_SS_mainFunction(void *pvParameters)
{
	while(TRUE)
	{
		SS_sendNumber_Two7Seg(SEG_1_ID, SEG_2_ID, gu8_dual_7SegNum, SEG_SWAP_DELAY_MS);
		vTaskDelay(SEG_SWAP_DELAY_MS);
	}
}

Std_ReturnType Display_SS_set7SegInfo(uint8_t u8_num)
{
	gu8_dual_7SegNum = u8_num;
	
	return E_OK;
}


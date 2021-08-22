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
/* Function to initialize the Sensing module */
Std_ReturnType Display_init(uint8_t DisplayID_u8)
{
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	switch(Displays[DisplayID_u8].DisplayDeviceId)
	{
		case LCD_ID_0:
		{
			/* Initialize the Display Module */
			Lcd_init();
		}
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
	else
	{
		/* Nothing to do here*/
	}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	switch(Displays[DisplayID_u8].DisplayDeviceId)
	{
		case LCD_ID_0:
		{
			Lcd_sendString((uint8_t*)StringToPrint_pu8);
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
	}else{/* Nothing to do here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	switch(Displays[DisplayID_u8].DisplayDeviceId)
	{
		case LCD_ID_0:
		{
			Lcd_sendVariableInt(u16_number, DEC);
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
		}else{/* Nothing to do here*/}
		/**************************************************************************************/
		/*								End of Error Checking								  */
		/**************************************************************************************/

		/**************************************************************************************/
		/*								Function Implementation								  */
		/**************************************************************************************/
		switch(Displays[DisplayID_u8].DisplayDeviceId)
		{
			case LCD_ID_0:
			{
				Lcd_cursorPosition(xAxis, yAxis);
			}
		}
		
		return E_NOT_OK;
	}
	
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Display_mainFunction
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Periodic function/task of the module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Display_mainFunction(void)
{
	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	/* Non Blocking Display initialization */
	Display_init(DISPLAY_LCD_16x2_ID);
	/* display string */
	Display_printString(DISPLAY_LCD_16x2_ID, (uint8_t*)"Display:");
	/* set distance position */
	Display_setCursor(DISPLAY_LCD_16x2_ID, 1,9);
	/* display distance */
	Display_printInteger(DISPLAY_LCD_16x2_ID, Displays[DISPLAY_LCD_16x2_ID].integer_u16);
	/* white spaces */
	Display_printString(DISPLAY_LCD_16x2_ID, (uint8_t*)"  ");

	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: set_DisplayInteger
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Function to set integer to be printed on specific display.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType set_DisplayInteger(uint8_t DisplayID_u8, uint16_t integer_u16)
{
	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	Displays[DisplayID_u8].integer_u16 = integer_u16;
	

	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: set_DisplayString
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Function to set string to be printed on specific display.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType set_DisplayString(uint8_t DisplayID_u8, uint8_t* string_au8)
{
	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	stringCopy(string_au8, Displays[DisplayID_u8].string_au8);
	
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: set_DisplayCursorPosition
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Function to set cursor position for specific display.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType set_DisplayCursorPosition(uint8_t DisplayID_u8, uint8_t xAxis_u8, uint8_t yAxis_u8)
{
	/**************************************************************************************/
	/*								Function Implementation								  */
	/**************************************************************************************/
	Displays[DisplayID_u8].xAxis_u8 = xAxis_u8;
	Displays[DisplayID_u8].yAxis_u8 = yAxis_u8;
	

	return E_OK;
}
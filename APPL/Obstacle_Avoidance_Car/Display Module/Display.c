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
	switch(Displays[DisplayID_u8])
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
	}else{/* Nothing to do here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	switch(Displays[DisplayID_u8])
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
	switch(Displays[DisplayID_u8])
	{
		case LCD_ID_0:
		{
			Lcd_cursorPosition(1, 11);
			Lcd_sendVariableInt(u16_number, DEC);
			Lcd_sendString((uint8_t*)"  ");
		}
	}
				
	return E_NOT_OK;
}
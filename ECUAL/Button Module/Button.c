/*****************************************************************************
* Module: Button Module
* File Name: Button.c
* Description: Source file for Button Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Button.h"


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: initialized the modules used by the button module
************************************************************************************/
Std_ReturnType Button_init(void)
{
	Dio_init(strDio_pins);
	return E_OK;
}
/************************************************************************************
* Parameters (in): Button ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: enuBttn_Status_t
* Description: gets the state of a given button pressed or released
************************************************************************************/
Std_ReturnType Button_getState(uint8_t u8_bttnID, uint8_t * pu8_state)
{
	uint8_t pinHighOrLow = Initial_Value;
	
	Dio_readPin(strButton_Config[u8_bttnID].u8_Button_DioId, &pinHighOrLow);
	
	/* check pressed or released according to pulled up or down */
	if(pinHighOrLow == PIN_HIGH)
	{
		if(strButton_Config[u8_bttnID].u8_pullUpOrDown == PULL_DOWN)
		{
			*pu8_state = BUTTON_STATE_PRESSED;
		}
		else
		{
			/* pulled up */
			*pu8_state = BUTTON_STATE_RELEASED;
		}
	}
	else if(pinHighOrLow == PIN_LOW)
	{
		if(strButton_Config[u8_bttnID].u8_pullUpOrDown == PULL_DOWN)
		{
			*pu8_state = BUTTON_STATE_RELEASED;
		}
		else
		{
			/* pulled up */
			*pu8_state = BUTTON_STATE_PRESSED;
		}
	}
	else
	{
		/* ?? */
	}
	return E_OK;
}



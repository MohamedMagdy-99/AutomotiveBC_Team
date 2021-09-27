/*****************************************************************************
* Module: Keypad V2 Module
* File Name: KeypadV2.c
* Description: Source file for Keypad V2 Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "KeypadV2.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define DELAY_IDLE				(0xABU)
#define DELAY_RUN				(0xAAU)
#define DELAY_DONE				(0xACU)

/*- STATIC VARIABLES
-------------------------------*/
const uint8_t au8_rowsDioIds[ROWS_NUM]=
{
	ROW_1_DIO_ID,
	ROW_2_DIO_ID,
	ROW_3_DIO_ID,
	ROW_4_DIO_ID
};

const uint8_t au8_columnsDioIds[COLS_NUM]=
{
	COLUMN_1_DIO_ID,
	COLUMN_2_DIO_ID,
	COLUMN_3_DIO_ID
};

uint8_t u8_delayState = DELAY_IDLE;
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
strKeypadOutput_t Keypad_keyPadOutput;

const uint8_t au8_keysLayout[ROWS_NUM][COLS_NUM] =
{
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{10, 11, 12}	
};

Keypad_keyCurrentState_t Keypad_keyPressedOrNo[ROWS_NUM][COLS_NUM] =
{
	{KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED},
	{KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED},
	{KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED},
	{KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED, KEYPAD_NO_KEY_PRESSED}	
};
/*- STATIC FUNCTIONS
-------------------------------*/
STATIC Std_ReturnType keyPad_OutputReset(void);

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

Std_ReturnType Keypad_Init(void)
{

	keyPad_OutputReset();
	Dio_init(strDio_pins);
	return E_OK;

}

Std_ReturnType Keypad_Scan(void)
{
	STATIC uint8_t u8_loopCounter = Initial_Value;
	STATIC uint8_t u8_row = Initial_Value;
	STATIC uint8_t u8_columnsCounter = Initial_Value;
	STATIC uint8_t u8_columnAsInputValue = KEYPAD_NO_KEY_PRESSED;
	STATIC uint8_t u8_rowAsInputValue = KEYPAD_NO_KEY_PRESSED;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < 2; u8_loopCounter++)
	{
		//loop on rows
		for (u8_row=Initial_Value;u8_row<ROWS_NUM;u8_row++)
		{
			//set one of the rows to logic one each time
			switch(u8_row)
			{
				case(ROW_1):
				{
					/* change row to i/p which will not be used in this iteration */
					Dio_changePinDirection(au8_rowsDioIds[ROW_2], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_3], DIO_PIN_DIR_INPUT, PIN_PUR);	
					Dio_changePinDirection(au8_rowsDioIds[ROW_4], DIO_PIN_DIR_INPUT, PIN_PUR);
					
					Dio_changePinDirection(au8_rowsDioIds[ROW_1], DIO_PIN_DIR_OUTPUT, PIN_LOW);				

					break;				
				}
				case(ROW_2):
				{
					/* change row to i/p which will not be used in this iteration */
					Dio_changePinDirection(au8_rowsDioIds[ROW_1], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_3], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_4], DIO_PIN_DIR_INPUT, PIN_PUR);					

					Dio_changePinDirection(au8_rowsDioIds[ROW_2], DIO_PIN_DIR_OUTPUT, PIN_LOW);

					break;
				}
				case(ROW_3):
				{
					/* change row to i/p which will not be used in this iteration */
					Dio_changePinDirection(au8_rowsDioIds[ROW_1], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_2], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_4], DIO_PIN_DIR_INPUT, PIN_PUR);					

					Dio_changePinDirection(au8_rowsDioIds[ROW_3], DIO_PIN_DIR_OUTPUT, PIN_LOW);


					break;
				}
				case(ROW_4):
				{
					/* change row to i/p which will not be used in this iteration */
					Dio_changePinDirection(au8_rowsDioIds[ROW_1], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_3], DIO_PIN_DIR_INPUT, PIN_PUR);
					Dio_changePinDirection(au8_rowsDioIds[ROW_2], DIO_PIN_DIR_INPUT, PIN_PUR);

					Dio_changePinDirection(au8_rowsDioIds[ROW_4], DIO_PIN_DIR_OUTPUT, PIN_LOW);
					break;
				}			
				default: break;									
			}
			//check input for each column
			for(u8_columnsCounter = Initial_Value; u8_columnsCounter < COLS_NUM; u8_columnsCounter++)
			{
				switch(u8_columnsCounter)
				{
					case(COLUMN_1):
					{
						/* read column value high or low */
						Dio_readPin(au8_columnsDioIds[u8_columnsCounter] ,&u8_columnAsInputValue);
						
						/* swap i/p with o/p */
						/* change column to o/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_OUTPUT, PIN_LOW);
						/* change row to i/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_INPUT, PIN_PUR);
						
						/* read row value high or low */
						Dio_readPin(au8_rowsDioIds[u8_row] ,&u8_rowAsInputValue);
						
						/* swap i/p with o/p to get back to normal state */
						/* change column to i/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_INPUT, PIN_PUR);
						/* change row to o/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_OUTPUT, PIN_LOW);
						
						
						if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH 
						   && Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							Keypad_keyPadOutput.u8_numberOfPressedKeys--;							
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_KEY_PRESSED;
							/* confirmed press */
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = au8_keysLayout[u8_row][u8_columnsCounter];
							Keypad_keyPadOutput.u8_numberOfPressedKeys++;							
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}						
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
							    && Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							/* key is already pressed */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
						}						
						else
						{
							/* ignore */
						}						
						break;
					}
					case(COLUMN_2):
					{
						/* read column value high or low */
						Dio_readPin(au8_columnsDioIds[u8_columnsCounter] ,&u8_columnAsInputValue);
						
						/* swap i/p with o/p */
						/* change column to o/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_OUTPUT, PIN_LOW);
						/* change row to i/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_INPUT, PIN_PUR);
						
						/* read row value high or low */
						Dio_readPin(au8_rowsDioIds[u8_row] ,&u8_rowAsInputValue);
						
						/* swap i/p with o/p to get back to normal state */
						/* change column to i/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_INPUT, PIN_PUR);
						/* change row to o/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_OUTPUT, PIN_LOW);
				
						if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							Keypad_keyPadOutput.u8_numberOfPressedKeys--;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_KEY_PRESSED;
							/* confirmed press */
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = au8_keysLayout[u8_row][u8_columnsCounter];
							Keypad_keyPadOutput.u8_numberOfPressedKeys++;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							/* key is already pressed */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
						}						
						else
						{
							/* ignore */
						}
						break;
					}
					case(COLUMN_3):
					{
						
						/* read column value high or low */
						Dio_readPin(au8_columnsDioIds[u8_columnsCounter] ,&u8_columnAsInputValue);
						
						/* swap i/p with o/p */
						/* change column to o/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_OUTPUT, PIN_LOW);
						/* change row to i/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_INPUT, PIN_PUR);
						
						/* read row value high or low */
						Dio_readPin(au8_rowsDioIds[u8_row] ,&u8_rowAsInputValue);
						
						/* swap i/p with o/p to get back to normal state */
						/* change column to i/p */
						Dio_changePinDirection(au8_columnsDioIds[u8_columnsCounter], DIO_PIN_DIR_INPUT, PIN_PUR);
						/* change row to o/p */
						Dio_changePinDirection(au8_rowsDioIds[u8_row], DIO_PIN_DIR_OUTPUT, PIN_LOW);
												
						if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_HIGH && u8_rowAsInputValue == PIN_HIGH
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
							Keypad_keyPadOutput.u8_numberOfPressedKeys--;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
						&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_NO_KEY_PRESSED && u8_loopCounter == 1)
						{
							Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] = KEYPAD_KEY_PRESSED;
							/* confirmed press */
							/* update keyPadOutput with this row and associated row */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = au8_keysLayout[u8_row][u8_columnsCounter];
							Keypad_keyPadOutput.u8_numberOfPressedKeys++;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 0)
						{
							/* set delay flag to RUN */
							u8_delayState = DELAY_RUN;
						}
						else if(u8_columnAsInputValue == PIN_LOW && u8_rowAsInputValue == PIN_LOW
								&& Keypad_keyPressedOrNo[u8_row][u8_columnsCounter] == KEYPAD_KEY_PRESSED && u8_loopCounter == 1)
						{
							/* key is already pressed */
							Keypad_keyPadOutput.au8_keysPressed[u8_row][u8_columnsCounter] = KEYPAD_NO_KEY_PRESSED;
						}						
						else
						{
							/* ignore */
						}
						break;
					}
					default: break;
				}		
			}
		}

		/* check if any delay flag is set to run */
		if(u8_delayState == DELAY_RUN && u8_loopCounter == 0)
		{
			/* delay fun */
			//Delay_ms(DEBOUNCE_DELAY_MS);
			vTaskDelay(DEBOUNCE_DELAY_MS);
			u8_delayState = DELAY_IDLE;
		}
		else
		{
			/* else return */
			/* reset variables */
			u8_loopCounter = Initial_Value;
			u8_row = Initial_Value;
			u8_columnsCounter = Initial_Value;
			u8_columnAsInputValue = KEYPAD_NO_KEY_PRESSED;
			u8_rowAsInputValue = KEYPAD_NO_KEY_PRESSED;			
			//set ROWs initially to no output state
			Dio_changePinDirection(au8_rowsDioIds[ROW_1], DIO_PIN_DIR_OUTPUT, PIN_HIGH);
			Dio_changePinDirection(au8_rowsDioIds[ROW_2], DIO_PIN_DIR_OUTPUT, PIN_HIGH);
			Dio_changePinDirection(au8_rowsDioIds[ROW_3], DIO_PIN_DIR_OUTPUT, PIN_HIGH);
			Dio_changePinDirection(au8_rowsDioIds[ROW_4], DIO_PIN_DIR_OUTPUT, PIN_HIGH);			
			return E_OK;			
		}
	}
	return E_OK;
}


STATIC Std_ReturnType keyPad_OutputReset(void)
{
	uint8_t u8_rowCounter = Initial_Value;
	uint8_t u8_colCounter = Initial_Value;
	
	for(u8_rowCounter = Initial_Value; u8_rowCounter < ROWS_NUM; u8_rowCounter++)
	{
		for(u8_colCounter = Initial_Value; u8_colCounter < COLS_NUM; u8_colCounter++)
		{
			Keypad_keyPadOutput.au8_keysPressed[u8_rowCounter][u8_colCounter] = KEYPAD_NO_KEY_PRESSED;
		}
		
	}
	Keypad_keyPadOutput.u8_numberOfPressedKeys = Initial_Value;
	
	return E_OK;
}

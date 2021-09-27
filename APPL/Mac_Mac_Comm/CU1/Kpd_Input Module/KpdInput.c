/*
 * KpdInput.c
 *
 * Created: 08-Sep-21 10:23:57 PM
 *  Author: Mohamed Magdy
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "KpdInput.h"
#include "ServiceL/FreeRTOS/Source/include/FreeRTOS.h"
#include "ServiceL\FreeRTOS\Source\include\task.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTATNS *-*-*-*-*-*/
#define KEYPAD_KEYS_NUM		(KEYPAD_ROWS_NUM * KEYPAD_COLS_NUM)
#define PATTERN_LEN			(3U)
#define USER_DATA_LEN		(1U)

#define KEY1_ROW			(ROW_1)
#define KEY1_COL			(COLUMN_1)

#define KEY6_ROW			(ROW_2)
#define KEY6_COL			(COLUMN_3)

#define KEY10_ROW			(ROW_4)
#define KEY10_COL			(COLUMN_1)

#define KEY12_ROW			(ROW_4)
#define KEY12_COL			(COLUMN_3)
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*-  GLOBAL EXTERN VARIABLES *-*-*-*-*-*/
KpdInput_strInputModuleDataInfo_t	InputModuleDataInfo;

/*uint8_t u8_patternCameFlag = FALSE;*/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*-  STATIC FUNCTIONS *-*-*-*-*-*/
STATIC Std_ReturnType KeypadInputModule_Filter(void);
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: KeypadInputModule_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Function to initialize the Keypad Input Module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType KeypadInputModule_Init(void)
{
	Keypad_Init();
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: KeypadInputModule_mainFunction
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: Periodic function/task of the module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void KeypadInputModule_mainFunction(void *pvParameters)
{
	while(TRUE)
	{
 		Keypad_Scan();
 		KeypadInputModule_Filter();
 		vTaskDelay(KPDINPUT_MAIN_FUNCTION_PERIODICITY_MS);		
	}
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: KeypadInputModule_getDataInfo
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: a getter for DataInfo.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType KeypadInputModule_getDataInfo(KpdInput_strInputModuleDataInfo_t* DataInfo)
{
	DataInfo->InputModuleData = InputModuleDataInfo.InputModuleData;
	DataInfo->KeypadScanState = InputModuleDataInfo.KeypadScanState;
	
	InputModuleDataInfo.InputModuleData = KEYPAD_NO_KEY_PRESSED;
	InputModuleDataInfo.KeypadScanState = KPDINPUT_IDLE;	
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: KeypadInputModule_Filter
* Sync/Async: ASynchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOT_OK
* Description: filters data according to application.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
STATIC Std_ReturnType KeypadInputModule_Filter(void)
{
	uint8_t u8_rowsCounter = Initial_Value;
	uint8_t u8_colsCounter = Initial_Value;
	uint8_t u8_oneKeyPressedFlag = FALSE;
	STATIC uint8_t u8_passResetFlag = FALSE;
	STATIC uint8_t u8_deviceEraseFlag = FALSE;
	
	STATIC uint8_t u8_patternVerificationCounter = Initial_Value;

	switch(Keypad_keyPadOutput.u8_numberOfPressedKeys)
	{
		case(USER_DATA_LEN):
		{	
			for(u8_rowsCounter = Initial_Value; u8_rowsCounter < KPDINPUT_KEYPAD_ROWS_NUM; u8_rowsCounter++)
			{
				for(u8_colsCounter = Initial_Value; u8_colsCounter < KPDINPUT_KEYPAD_COLS_NUM; u8_colsCounter++)
				{
					if(Keypad_keyPadOutput.au8_keysPressed[u8_rowsCounter][u8_colsCounter] != KEYPAD_NO_KEY_PRESSED)
					{
						InputModuleDataInfo.InputModuleData = Keypad_keyPadOutput.au8_keysPressed[u8_rowsCounter][u8_colsCounter];
						u8_rowsCounter = KPDINPUT_KEYPAD_ROWS_NUM;
						InputModuleDataInfo.KeypadScanState = KPDINPUT_DATA;
						u8_oneKeyPressedFlag = TRUE;
						break;
					}
				}
				if(u8_oneKeyPressedFlag == TRUE)
				{
					break;
				}
			}
			if(u8_oneKeyPressedFlag == FALSE)
			{
				InputModuleDataInfo.KeypadScanState = KPDINPUT_IDLE;
			}
			u8_passResetFlag = FALSE;
			u8_deviceEraseFlag = FALSE;
			u8_patternVerificationCounter = Initial_Value;
			
/*			u8_patternCameFlag = FALSE;*/
			break;
		}
		case(PATTERN_LEN):
		{
			
			if(Keypad_keyPressedOrNo[KEY1_ROW][KEY1_COL] == KEYPAD_KEY_PRESSED && Keypad_keyPressedOrNo[KEY6_ROW][KEY6_COL] == KEYPAD_KEY_PRESSED 
			   && Keypad_keyPressedOrNo[KEY10_ROW][KEY10_COL] == KEYPAD_KEY_PRESSED && u8_passResetFlag == FALSE)
			{
// 				if(u8_patternCameFlag == FALSE)
// 				{
// 					u8_patternCameFlag = TRUE;
// 				}
				u8_patternVerificationCounter++;
				if(u8_patternVerificationCounter == KPDINPUT_PATTERN_CONFIRMATION_COUNTS)
				{
					InputModuleDataInfo.KeypadScanState = KPDINPUT_PASS_RESET;
					u8_passResetFlag = TRUE;
					u8_patternVerificationCounter = Initial_Value;
					
/*					u8_patternCameFlag = FALSE;*/
				}
				
			}
			else if(Keypad_keyPressedOrNo[KEY1_ROW][KEY1_COL] == KEYPAD_KEY_PRESSED && Keypad_keyPressedOrNo[KEY6_ROW][KEY6_COL] == KEYPAD_KEY_PRESSED 
					&& Keypad_keyPressedOrNo[KEY12_ROW][KEY12_COL] == KEYPAD_KEY_PRESSED && u8_deviceEraseFlag == FALSE)
			{
				u8_patternVerificationCounter++;
				if(u8_patternVerificationCounter == KPDINPUT_PATTERN_CONFIRMATION_COUNTS)
				{				
					InputModuleDataInfo.KeypadScanState = KPDINPUT_ERASE_DEVICE;
					u8_deviceEraseFlag = TRUE;
					u8_patternVerificationCounter = Initial_Value;
				}				
					
			}
			else
			{
				InputModuleDataInfo.KeypadScanState = KPDINPUT_IDLE;
			}				
			break;
		}
		default: 
		{
			InputModuleDataInfo.KeypadScanState = KPDINPUT_IDLE;
			u8_passResetFlag = FALSE;
			u8_deviceEraseFlag = FALSE;	
			u8_patternVerificationCounter = Initial_Value;
			
/*			u8_patternCameFlag = FALSE;*/
			break;	
		}		
	}

	return E_OK;
}
/*****************************************************************************
* Module: Data Manager Module
* File Name: DataManager.c
* Description:Source file for Data Manager Module
* Author: Shady Mamdouh
* Date: 12/9/2021
******************************************************************************/
/**************************************INCLUDES*********************************************/
#include "Microcontroller\Platform_Types.h"
#include "Microcontroller\Std_types.h"
#include "APPL\Mac_Mac_Comm\CU1\Animation Module\Animation.h"
#include "APPL\Mac_Mac_Comm\CU1\Kpd_Input Module\KpdInput.h"
#include "ServiceL\FreeRTOS\Source\include\FreeRTOS.h"
#include "ServiceL\FreeRTOS\Source\include\task.h"
#include "APPL\Mac_Mac_Comm\CU1\Wireless Com Master Module\WrlsCom.h"

/******************************************************************************************/
/************************************CONSTANTS****************************************/
#define FIXED_PACKET_HEADER				0xAA
#define KEYPAD_DATA_REQ_TYPE			0x03
#define KEYPAD_DATA_LENGTH				0x01
#define KEYPAD_DATA_PACKET_SIZE			0x04

#define KEYPAD_PASS_CHANGE_REQ_TYPE     0x04
#define KEYPAD_PASS_CHANGE_LENGTH       0x00
#define KEYPAD_PASS_CHANGE_PACKET_SIZE  0x03


/******************************************************************************************/
/************************************Global variables****************************************/

uint8_t WrlsCom_OldState ;
uint8_t WrlsCom_CurrentState ;

#define MAX_PACKET_SIZE  50U
uint8_t PacketBuffer[MAX_PACKET_SIZE];
/*Pointer to struct of Keypad input */
KpdInput_strInputModuleDataInfo_t *KeyPadDataInfo ;
/*****************************************************************************************/
/***************************************States*******************************************/
uint8_t OldState ;
uint8_t CurrentState ;
/***************************************************************************************/
static void GetState(void)
{
	/* Get wireless comm state */
	uint8_t State;
	WrlsCom_getState(&State);
	WrlsCom_CurrentState =State;
	
	/*Get keypad input state */
	KeypadInputModule_getDataInfo(KeyPadDataInfo);
	
}
/**********************************************************************************************************
* Parameters (in): DataType
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to transmit packet using wireless comm
***********************************************************************************************************/
static void DataTransmit(uint8_t DataType)
{
	switch(DataType)
	{
		case KPDINPUT_DATA :
		{
			/* Data frame*/
			
			/*Fixed Packet Header */
			PacketBuffer[0] = FIXED_PACKET_HEADER;
			/*Request type */
			PacketBuffer[1] = KEYPAD_DATA_REQ_TYPE;
			/*Request length */
			PacketBuffer[2] = KEYPAD_DATA_LENGTH;
			/*Data */
			PacketBuffer[3]= KeyPadDataInfo->InputModuleData;
			
			/* Set data to be transmitted */
			WrlsCom_TransmitData(PacketBuffer,KEYPAD_DATA_PACKET_SIZE);
			break;
		}
		case KPDINPUT_PASS_RESET :
		{
			/* Data framming */
			
			/*Fixed Packet Header */
			PacketBuffer[0] = FIXED_PACKET_HEADER;
			/*Request type */
			PacketBuffer[1] = KEYPAD_PASS_CHANGE_REQ_TYPE;
			/*Request length */
			PacketBuffer[2] = KEYPAD_PASS_CHANGE_LENGTH;
			/* Set data to be transmitted */
			WrlsCom_TransmitData(PacketBuffer,KEYPAD_PASS_CHANGE_PACKET_SIZE);
			
			break;
		}
	}
}
static void UpdateState(void)
{
	switch(WrlsCom_CurrentState)
	{
		case WRLSCOM_STATE_MALFUNCTION :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with MALFunction Pattern */
				ANI_Start(LED_DEVICE_ID,0,MAL_FUN_PATTERN);
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
			 
			
		}
		case WRLSCOM_STATE_DEVICE_SEARCH :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device search pattern Pattern */
				ANI_Start(LED_DEVICE_ID,0,DEVICE_SEARCH_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_VERIFICATION :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device Verification pattern  */
				ANI_Start(LED_DEVICE_ID,0,VER_SEARCH_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_CONNECTED :
		{
			if (WrlsCom_CurrentState==WrlsCom_OldState)
			{
				break;
			}
			else
			{
				/* Animate LED with Device Connection ON pattern  */
				ANI_Start(LED_DEVICE_ID,0,CONNECTION_ON_PATTERN);
				
				/* Update old state to current state to avoid execute the same line every time */
				WrlsCom_CurrentState=WrlsCom_OldState;
				break;
			}
		}
		case WRLSCOM_STATE_IDLE :
		{
			
			
				WrlsCom_CurrentState=WrlsCom_OldState;
				/* Check if Data need to be Transmitted */
				switch(KeyPadDataInfo->KeypadScanState)
				{
					case KPDINPUT_IDLE :
					{
						/*No Data */
						break;
					}
					case KPDINPUT_ERASE_DEVICE :
					{
						/*Set wireless Comm in Erase device to switch to advertising mode */
						WrlsCom_setState(WRLSCOM_STATE_DEVICE_ERASE);
						
						/*Update current state to Searching */
						WrlsCom_CurrentState = WRLSCOM_STATE_DEVICE_SEARCH;
						break;
					}
					case KPDINPUT_PASS_RESET :
					{
						DataTransmit(KPDINPUT_PASS_RESET);
						break;
					}
					case KPDINPUT_DATA :
					{
						DataTransmit(KPDINPUT_DATA);
						break;
					}
					
				}
				
		
				break;
			
		}
		
	}
}

/**********************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function is the module main function 
***********************************************************************************************************/
void DataMngr_mainFunction(void* pvParam)
{
	while (1)
	{
		GetState();
		UpdateState();
		vTaskDelay(100);
	}
}

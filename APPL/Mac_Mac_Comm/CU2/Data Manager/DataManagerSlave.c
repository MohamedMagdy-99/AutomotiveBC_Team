/*****************************************************************************
* Module: Data Manager Module
* File Name: DataManagerSlave.c
* Description:Source file for Data Manager Slave Module
* Author: Shady Mamdouh
* Date: 12/9/2021
******************************************************************************/
/**************************************INCLUDES*********************************************/
#include "..\..\..\Microcontroller\Platform_Types.h"
#include "..\..\..\Microcontroller\Std_types.h"
#include "..\Animation Module\Animation.h"
#include "APPL/Mac_Mac_Comm/CU2/Wireless Com Slave Module/SlvWrlsCom.h"
#include "ServiceL/MemM Module/MemM.h"
#include "APPL/Mac_Mac_Comm/CU2/Display Module/Display.h"
#include "ServiceL/FreeRTOS/Source/include/FreeRTOS.h"
#include "ServiceL\FreeRTOS\Source\include\task.h"
/*************LCD INCLUDE & 7-SEG include***************************/

/******************************************************************************************/
/************************************Global variables****************************************/
#define FIXED_PACKET_HEADER				0xAA
#define KEYPAD_DATA_REQ_TYPE			0x03
#define KEYPAD_DATA_LENGTH				0x01
#define KEYPAD_DATA_PACKET_SIZE			0x04

#define KEYPAD_PASS_CHANGE_REQ_TYPE     0x04
#define KEYPAD_PASS_CHANGE_LENGTH       0x00
#define KEYPAD_PASS_CHANGE_PACKET_SIZE  0x03
#define MAX_PASS_TRIALS					5U


#define PASS_SIZE		6U
uint8_t PASSBuffer[PASS_SIZE];
uint8_t SavedPassword[PASS_SIZE];
uint8_t PASSCounter = 0;
uint8_t gu8_ReceivedData ;
uint8_t trialsCounter=0;
#define PASS_ENTERED		1U
#define PASS_NOT_ENTERED	0U
uint8_t PASSCurrentState  = PASS_NOT_ENTERED;  

#define FLAG_HIGH   1U
#define FLAG_LOW	0U
uint8_t PASSChangeflag =FLAG_LOW ;

uint8_t WrlsCom_OldState ;
uint8_t WrlsCom_CurrentState ;

#define MAX_PACKET_SIZE  50U
uint8_t PacketBuffer[MAX_PACKET_SIZE];
/*****************************************************************************************/
/***************************************States*******************************************/
uint8_t OldState ;
uint8_t CurrentState ;
/***************************************************************************************/
static void DataMngr_GetState(void)
{
	/* Get wireless comm state */
	uint8_t State;
	WrlsCom_getState(&State);
	WrlsCom_CurrentState =State;
	
}
static void DataMngr_UpdateState(void)
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
				
				/* Display Loading message on LCD */
				Display_Lcd_setPingPongR1Info("Loading",7);
				break;
			}
		}
		case WRLSCOM_STATE_DATA_READY :
		{
			
			WrlsCom_CurrentState=WrlsCom_OldState;
			/*Received Data handler */
			DataReceiveHandler();
			
			
			
			
			
			break;
			
		}
		
	}
}
static void DataReceiveHandler(void)
{
	uint8_t u8_size ;
	uint8_t *DataArr;
	uint8_t u8_counter;
	WrlsCom_ReceiveData(DataArr,u8_size);
	
	/* KeyPad Data packet */
	if (DataArr[0]==FIXED_PACKET_HEADER && DataArr[1]==KEYPAD_DATA_REQ_TYPE && DataArr[2] == 1)
	{
		if (PASSChangeflag==FLAG_LOW)
		{
			/* Check if the Password is entered before */
			if (PASSCurrentState==PASS_ENTERED)
			{
				/* Means that Data will be displayed on 7-SEG */
			  Display_SS_set7SegInfo(DataArr[3]);
			}
			else if (PASSCurrentState ==PASS_NOT_ENTERED)
			{
				/* Means that is password entering Case*/
				Display_Lcd_setPingPongR1Info("Password:",9);
				/*Password element entered */
				if (DataArr[3] >= 1 && DataArr[3] <= 9 && PASSCounter < 6)
				{
					PASSBuffer[PASSCounter] = DataArr[3] ;
					PASSCounter++;
					/*LCD Display message on nxt position */
					Display_setCursor(DISPLAY_LCD_16x2_ID,2,PASSCounter+1);
					Display_printChar(DISPLAY_LCD_16x2_ID,'*');
				
				
				}
				 /* Receive element with exceed pass element count will ignore the packet */
				else if (DataArr[3] >= 1 && DataArr[3] <= 9 && PASSCounter == 6)
				{
					/*Ignore Packet */
				}  
				  /* Delete packet while there is no elements. will ignore*/
				else if (DataArr[3]==10  && PASSCounter == 0)
				{
					/*Ignore Packet */
				}
				/* Delete packet while there is elements will delete the previous entered element*/
				else if (DataArr[3]==10  && PASSCounter > 0)
				{
					/*Decrement pass counter */
					PASSCounter--;
					/* Display space on the current cursor*/
					Display_setCursor(DISPLAY_LCD_16x2_ID,2,PASSCounter+1);
					Display_printChar(DISPLAY_LCD_16x2_ID,' ');
				
				}
				/* Pass confirm packet while elements < 6 will ignore the packet */	
				else if (DataArr[3]==12  && PASSCounter < 6)
				{
					/*Ignore Packet */
				}
				 /* Pass confirm packet while elements == 6 will Check password */
				else if (DataArr[3]==12  && PASSCounter == 6)
				{
					/***************************************/
					/*read password from EEPROM*/
					MemM_readBlock(MEMM_CONNECTED_PROG_PASSWORD_ID, SavedPassword);
					/*Compare passwords*/
					if(stringCmp(SavedPassword, PASSBuffer) == TRUE)
					{
						/* If the received pass is equal to the saved pass */
						/*Initialize pass counter */
						PASSCounter =0;
						/* Display Pass Ok for 2 seconds */
						Display_Lcd_setPingPongR1Info("Pass OK",7);
						vTaskDelay(2000);
					
						PASSCurrentState = PASS_ENTERED;
						Display_clearDisplay(DISPLAY_LCD_16x2_ID);
						Display_Lcd_setPingPongR1Info("System is ON",12);
					}
					else
					{
						Display_Lcd_setPingPongR1Info("Wrong PASS",12);
						/*Initialize pass counter */
						PASSCounter =0;
						trialsCounter++;
						if(trialsCounter == MAX_PASS_TRIALS)
						{
							vTaskDelay(10000);
							trialsCounter=0;
						}
						else
						{
							vTaskDelay(1000);
						}
					
						/* still not entered */
					}
				
				}
			}
		}
		else if (PASSChangeflag==FLAG_HIGH)
		{
			/*Password element entered */
			if (DataArr[3] >= 1 && DataArr[3] <= 9 && PASSCounter < 6)
			{
				PASSBuffer[PASSCounter] = DataArr[3] ;
				PASSCounter++;
				/*LCD Display message on nxt position */
				Display_setCursor(DISPLAY_LCD_16x2_ID,2,PASSCounter+1);
				Display_printChar(DISPLAY_LCD_16x2_ID,'*');
			}
			 /* Receive element with exceed pass element count will ignore the packet */
			else if (DataArr[3] >= 1 && DataArr[3] <= 9 && PASSCounter == 6)
			{
				/*Ignore Packet */
			}  
			  /* Delete packet while there is no elements. will ignore*/
			else if (DataArr[3]==10  && PASSCounter == 0)
			{
				/*Ignore Packet */
			}
			/* Delete packet while there is elements will delete the previous entered element*/
			else if (DataArr[3]==10  && PASSCounter > 0)
			{
				/*Decrement pass counter */
				PASSCounter--;
				/* Display space on the current cursor*/
				Display_setCursor(DISPLAY_LCD_16x2_ID,2,PASSCounter+1);
				Display_printChar(DISPLAY_LCD_16x2_ID,' ');
				
			}
			/* Pass confirm packet while elements < 6 will ignore the packet */	
			else if (DataArr[3]==12  && PASSCounter < 6)
			{
				/*Ignore Packet */
			}
			 /* Pass confirm packet while elements == 6 will Check password */
			else if (DataArr[3]==12  && PASSCounter == 6)
			{
				/***************************************/
				/*WRITE password INTO EEPROM*/
				MemM_writeBlock(MEMM_CONNECTED_PROG_PASSWORD_ID, PASSBuffer,MEMM_CONNECTED_PROG_PASSWORD_SIZE);
				/*Clr LCD*/
				Display_clearDisplay(DISPLAY_LCD_16x2_ID);
				Display_Lcd_setPingPongR1Info("System is ON",12);
				/*Initialize pass counter */
				PASSCounter =0;
				/* recover state */
				PASSChangeflag =FLAG_LOW ;
				PASSCurrentState = PASS_ENTERED;
			}
		}
	}
	 /* Pass change Packet */
	else if (DataArr[0]==FIXED_PACKET_HEADER && DataArr[1]== KEYPAD_PASS_CHANGE_REQ_TYPE&& DataArr[2] == 0)
	{
		/* Check if the Password is entered before */
		if (PASSCurrentState==PASS_ENTERED)
		{
			/* Reset pass counter to start receive the new Pass */
			PASSCounter =0;
			/* Rising Pass change flag */
			 PASSChangeflag =FLAG_HIGH ;
			/*New pass LCD Message*/
			Display_Lcd_setPingPongR1Info("Changing Pass",13);
			
		}
		else if (PASSCurrentState == PASS_NOT_ENTERED)
		{
			/*LCD Display enter the old pass first or sign in first*/
			Display_Lcd_setPingPongR1Info("OLD PASS",8);
		}
	}
	
}

void DataMngr_mainFunction(void* pvParam)
{
	while(1)
	{
		DataMngr_GetState();
		DataMngr_UpdateState();
		vTaskDelay(100);
	}
}
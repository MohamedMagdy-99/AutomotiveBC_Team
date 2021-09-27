/*
 * SevenSegment.c
 *
 * Created: 08-Sep-21 6:39:54 PM
 *  Author: Mohamed Magdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "SevenSegment.h"

/*- CONSTANTS
-------------------------------*/
#define MAX_NUM_1SEG			(9U)
#define MAX_NUM_2SEG			(99U)
#define MIN_NUM					(0U)
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initialize the 7seg module
******************************************************************************************/
Std_ReturnType SS_Init()
{
	Dio_init(strDio_pins);

	uint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < NUM_7SEG_USED; u8_loopCounter++)
	{
		Dio_writePin(str7Seg_config[u8_loopCounter].u8_segEN_DioId, PIN_HIGH);
	}
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): seg id, number
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: sends a number to 1 7seg
******************************************************************************************/
Std_ReturnType SS_sendNumber_One7Seg(uint8_t segId, uint8_t u8_num)
{
	
	if(u8_num > MAX_NUM_1SEG || u8_num < MIN_NUM)
	{
		return E_NOT_OK;
	}
	else
	{
		switch(u8_num)
		{
// 			/* disable seg pin */
// 			Dio_writePin(str7Seg_config[segId].u8_segEN_DioId, PIN_LOW);
			
			case(0):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);
				break;
			}
			case(1):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(2):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(3):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(4):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(5):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(6):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(7):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_LOW);				
				break;
			}
			case(8):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_HIGH);				
				break;
			}
			case(9):
			{
				Dio_writePin(str7Seg_config[segId].u8_segA_DioId, PIN_HIGH);
				Dio_writePin(str7Seg_config[segId].u8_segB_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segC_DioId, PIN_LOW);
				Dio_writePin(str7Seg_config[segId].u8_segD_DioId, PIN_HIGH);				
				break;
			}																											
		}
		/* enable seg pin */
		Dio_writePin(str7Seg_config[segId].u8_segEN_DioId, PIN_HIGH);
	}
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): seg 1 id, seg 2 id, number, swap delay
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: sends a number to 2 7seg
******************************************************************************************/
Std_ReturnType SS_sendNumber_Two7Seg(uint8_t firstSegId, uint8_t secondSegId, uint8_t u8_num, uint8_t u8_swapDelay_ms)
{
	if(u8_num > MAX_NUM_2SEG || u8_num < MIN_NUM)
	{
		return E_NOT_OK;
	}
	else
	{
		 uint8_t u8_unitsNum = Initial_Value;
		 uint8_t u8_tensNum = Initial_Value;
		
		u8_unitsNum = u8_num % 10;
		u8_tensNum =  u8_num / 10;
		
		/* send units */
		Dio_writePin(str7Seg_config[secondSegId].u8_segEN_DioId, PIN_LOW);
		SS_sendNumber_One7Seg(firstSegId, u8_unitsNum);
		/* delay swap */
		//Delay_ms(u8_swapDelay_ms);
		vTaskDelay(u8_swapDelay_ms);
		
		/* send tens */
		Dio_writePin(str7Seg_config[firstSegId].u8_segEN_DioId, PIN_LOW);
		SS_sendNumber_One7Seg(secondSegId, u8_tensNum);
		
		/* delay swap */
		//Delay_ms(u8_swapDelay_ms);		
	}
	return E_OK;	
}

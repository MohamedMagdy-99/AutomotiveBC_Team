/*
 * Sensing.c
 *
 * Created: 13/8/2021 11:15:40 AM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Sensing.h"


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the state of the Module
 */
#define SENSING_STATUS_UNINIT		0U
#define SENSING_STATUS_INIT			1U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/

/* Holds the status of the Sensing Module */
Sensing_State_t SensingModuleStatus_gu8 = SENSING_STATUS_UNINIT;
Sensing_Distance_t distanceBetFrontSensorAndOBstacle = Initial_Value;
static uint16_t  DistanceValuesPerSensor[SENSORS_USED_NUM]={Initial_Value};
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Sensing_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function to Initialize the Sensing module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to initialize the Sensing module */
Std_ReturnType Sensing_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the module is already initialized */
	if(SensingModuleStatus_gu8 == SENSING_STATUS_INIT)
	{
		return E_OK;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Initialize the Ultrasonic Module */
	Ultrasonic_Init();
	
	/* Change the state of the module to initialized */
	SensingModuleStatus_gu8 = SENSING_STATUS_INIT;
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Sensing_getReading
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): SensorID_u8 - ID for the distance to be read.
* Parameters (inout): None
* Parameters (out): Sensor_Value - pointer to a variable to hold the returned distance
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Getter function used to get a reading from the Sensing Module
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


Std_ReturnType Sensing_getReading(uint8_t SensorID_u8, uint16_t *Sensor_Value)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the module is not initialized */
	if(SensingModuleStatus_gu8 != SENSING_STATUS_INIT)
	{
		return E_NOT_OK;
	}
	else{/*Nothing to do here*/}
		
	/* Check if the pointer variable is NULL */
	if (NULL_PTR == Sensor_Value)
	{
		return E_NOT_OK;
	}
	else{/*Nothing to do here*/}
		
	if(SensorID_u8 >= SENSORS_USED_NUM)
	{
		return E_NOT_OK;
	}
	else{/* Nothing to do here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	
	switch(Sensors[SensorID_u8])
	{
		case US_CHANNEL_FRONT:
		{
			*Sensor_Value = DistanceValuesPerSensor[SensorID_u8];
			break;	
    }
		default:
		{
			return E_NOT_OK;
		}
	}
	return E_OK ;
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Sensing_mainFunction
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): SensorID_u8 - ID for the distance to be read.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: It is the sensing module main function that called by APP 
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Sensing_mainFunction(void)
{
	uint8_t u8_Counter=0;
	for(u8_Counter=0;u8_Counter<SENSORS_USED_NUM;u8_Counter++)
	{
		switch(Sensors[u8_Counter])
		{
			uint16_t tempDistance_u16 = 0;
			/* Read Ultrasonic Distance */
			case US_CHANNEL_FRONT :
			{
				if(Ultrasonic_GetDistance(US_CHANNEL_FRONT, &tempDistance_u16) == E_OK)
				{
					if(tempDistance_u16 > ULTRASONIC_MAX_DISTANCE_RANGE)
					{
						DistanceValuesPerSensor[u8_Counter] = ULTRASONIC_MAX_DISTANCE_RANGE;
					}
					else
					{
						DistanceValuesPerSensor[u8_Counter] = tempDistance_u16;
					}
				}
				else
				{
				
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return E_OK;
}
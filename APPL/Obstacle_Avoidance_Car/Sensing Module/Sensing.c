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
* Service Name: Sensing_getObstcleDistance
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): SensorID_u8 - ID for the distance to be read.
* Parameters (inout): None
* Parameters (out): Sensor_Value - pointer to a variable to hold the returned distance
* Return value: Std_ReturnType - return the status of the function E_OK or E_NOK
* Description: Function used to get reading of a sensor with the given ID
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
	}else{/*Nothing to do here*/}
		
	/* Check if the pointer variable is NULL */
	if (NULL_PTR == Sensor_Value)
	{
		return E_NOT_OK;
	}else{/*Nothing to do here*/}
		
	if(SensorID_u8 >= SENSORS_USED_NUM)
	{
		return E_NOT_OK;
	}else{/* Nothing to do here*/}
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
			uint16_t tempDistance_u16 = 0;
			/* Read Ultrasonic Distance */
			if(Ultrasonic_GetDistance(US_CHANNEL_FRONT, &tempDistance_u16) == E_OK)
			{
				if(tempDistance_u16 > ULTRASONIC_MAX_DISTANCE_RANGE)
				{
					*Sensor_Value = ULTRASONIC_MAX_DISTANCE_RANGE;
				}
				else
				{
					*Sensor_Value = tempDistance_u16;
				}
				return E_OK;
			}
			else
			{
				return E_NOT_OK;
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return E_NOT_OK;
}
/*****************************************************************************
* Module: Observer Pattern
* File Name: Observer.c
* Description: Source file for observer pattern module
* Author: Shady Mamdouh
* Date: 8/20/2021
******************************************************************************/
/********************************INCLUDES**************************************/
#include "..\..\Microcontroller\Std_types.h"
#include "..\..\Microcontroller\Platform_Types.h"
#include "Observer.h"
#include "..\..\APPL\Obstacle_Avoidance_Car\Sensing Module\Sensing.h"
#include "..\..\APPL\Obstacle_Avoidance_Car\Sensing Module\Sensing_Cfg.h"
/******************************************************************************/
uint8_t CurrentSubscribersNum = 0;
/* Array of subscribers */
SubscriberData_t Subscribers[MAX_SUBSCRIBER_NUM]={{0}};
/******************************************************************************/
/*****************************Shared Databuffer*********************************/
uint32_t SharedDataBuffer[NumberOfDataShared];
/********************************************************************************/

/***********************************************************************************************************************
* Parameters (in): OB_InSubData
* Parameters (out): ObserverReturn_t value
* Return value: ObserverReturn_t
* Description: This function used by Subscriber to request a subscription 
************************************************************************************************************************/
ObserverReturn_t OB_Subscribe(SubscriberData_t *OB_InSubData)
{
	/*********************************************************Safety Handling***************************************************/
	if (OB_InSubData==0)  // check NULL Pointer
	{
		return OB_InvalidPointer;
	}
	if (OB_InSubData->CallBackFunction == 0) // check NULL Pointer
	{
		return OB_InvalidPointer;
	}
	/* Check if passing wrong Data Shared ID */
	if (  ( (OB_InSubData->DistanceSubscription) >NumberOfDataShared) || ( (OB_InSubData->SpeedSubscription) >NumberOfDataShared) || ( (OB_InSubData->DistanceSubscription) >NumberOfDataShared)   )
	{
		return OB_InvaledDataSubID;
	}   
	  /* Check of exceed the allowed Number Of subscription */
	if (CurrentSubscribersNum == MAX_SUBSCRIBER_NUM)
	{
		return OB_CompleteSubscribers ;
	}
	/**********************************************************************************************************************************/
	uint8_t u8_counter =0;
	/* Assign the subscription into an empty location */
	for (u8_counter=0;u8_counter<MAX_SUBSCRIBER_NUM;u8_counter++)
	{
		if (Subscribers[u8_counter].CallBackFunction == 0   ) // Empty location 
		{
			
			Subscribers[u8_counter] = *OB_InSubData ;
			/* increment the current subscribers Number */
			CurrentSubscribersNum ++ ;
			return OB_SubSuccessfull ;
			break;
		}
		
	}
	return OB_SubSuccessfull ;
}
/********************************************************************************************************************************************/
/***********************************************************************************************************************
* Parameters (in): OB_InSubIdFunction
* Parameters (out): ObserverReturn_t value
* Return value: ObserverReturn_t
* Description: This function used by Subscriber to delete a subscription
************************************************************************************************************************/
ObserverReturn_t OB_UnSubscribe(SubscribePtr OB_InSubIdFunction)
{
	/*********************************************************Safety Handling***************************************************/
	if (OB_InSubIdFunction==0) // check NULL Pointer
	{
		return OB_InvalidPointer;
	}
	/**************************************************************************************************************************/
	uint8_t u8_counter =0;
	for (u8_counter=0;u8_counter<MAX_SUBSCRIBER_NUM;u8_counter++)
	{
		if (Subscribers[u8_counter].CallBackFunction == OB_InSubIdFunction)
		{
			/* Assign Null */
			Subscribers[u8_counter].CallBackFunction = 0;
			/* Decrement the Current subscribers number */
			CurrentSubscribersNum -- ;
			break;
		}
	}
	return OB_UnSubSuccessfull;
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: ObserverReturn_t
* Description: This function is the main function of the Observer Module
************************************************************************************************************************/
void OB_notify(void)
{
	uint16_t Distance;
	/* read distance form Sensing module */
	Sensing_getReading(SENSING_FRONT_OBSTACLE_DISTANCE,&Distance);	
	/* update Data buffer with the new Distance value */
	SharedDataBuffer[OB_Distance]= Distance;
	/*loop on distance subscribes */
	uint8_t u8_counter =0;
	for (u8_counter=0;u8_counter<MAX_SUBSCRIBER_NUM;u8_counter++)
	{
		/**********safety check on null pointer*********/
		if (Subscribers[u8_counter].CallBackFunction !=0)
		{
			if (Subscribers[u8_counter].DistanceSubscription==SUBSCRIPED)
			{
				/* call back the subscriber */
				Subscribers[u8_counter].CallBackFunction();
			}
		}
		
		
	}
	
}
/*************************************************************************************************************************/
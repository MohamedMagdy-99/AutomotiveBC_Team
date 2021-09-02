/*****************************************************************************
* Module: Observer Pattern
* File Name: Observer.c
* Description: Header file for observer pattern module
* Author: Shady Mamdouh
* Date: 8/20/2021
******************************************************************************/



#ifndef OBSERVER_H_
#define OBSERVER_H_
/*********************************************************************************/
/* It represents the Array size of subscribers*/
#define  MAX_SUBSCRIBER_NUM 5
/*********************************************************************************/
/* It represents the Number of Data types or sensors Data shared between modules*/
#define NumberOfDataShared 3
/*Data Shared indices used by the user to get the data from the shared buffer */
#define OB_Distance		0U
#define OB_Temperature	1U
#define OB_Speed		2U
/********************************************************************************/
/* Pointer to function is a data type of call back functions of the subscribers*/
typedef void(*SubscribePtr)(void);
/*******************************************************************************/
/*********************Subscription State***************************************/
#define SUBSCRIPED	0U
#define NOT_SUBSCRIPED	0U
/* Subscription Data per subscriber */
typedef struct SubscriberData_t
{
	SubscribePtr CallBackFunction;
	uint8_t DistanceSubscription;
	uint8_t TemperatureSubscription;
	uint8_t SpeedSubscription;
}SubscriberData_t;
/***********************************Return Handling******************************/
typedef enum ObserverReturn_t
{
	OB_CompleteSubscribers,
	OB_SubSuccessfull,
	OB_UnSubSuccessfull,
	OB_InvaledDataSubID,
	OB_EEROR_OK,
	OB_EEROR_NOK,
	OB_InvalidPointer
}ObserverReturn_t;



extern uint32_t SharedDataBuffer[NumberOfDataShared];

void OB_notify(void);
ObserverReturn_t OB_Subscribe(SubscriberData_t *OB_InSubData);
ObserverReturn_t OB_UnSubscribe(SubscribePtr OB_InSubIdFunction);



#endif /* OBSERVER_H_ */
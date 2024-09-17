/*
 * Bcm.c
 *
 * Created: 8/25/2021
 *  Authors: Mohamed Magdy & Ahmed Nabil 
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Bcm.h"

/*- CONSTANTS
----------------------------------------------*/
#define BCM_ID			        (99U)
#define RUNNING					(51U)
#define IDLE					(52U)
#define RECEIVED				(53U)
#define NOT_RECEIVED_YET		(55U)



/*- GLOBAL EXTERN VARIABLES -------------------------------------*/
strRxComChannels_Data_t	arrStr_RxComChannels[BCM_RX_COM_DEVICES_USED];
BCM_TxRequestData_t BCM_TxRequests[BCM_TX_COM_DEVICES_USED][BCM_MAX_TX_REQUESTS];
BCM_TxRequestData_t *BCM_TxCurrentRequest[BCM_TX_COM_DEVICES_USED];
uint16_t BCM_TxRequests_Counter[BCM_TX_COM_DEVICES_USED] = {0};
uint16_t BCM_TxRequests_Available[BCM_TX_COM_DEVICES_USED] = {0};
uint16_t BCM_TxRequest_Index[BCM_TX_COM_DEVICES_USED] = {0};
BCM_mainState_t BCM_TxCurrentChannelsState[BCM_TX_COM_DEVICES_USED] = {BCM_MAINFUNC_STATE_IDLE};
uint16_t BCM_dataCounter[BCM_TX_COM_DEVICES_USED] = {0};



/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initialized BCM module.
************************************************************************************/
Std_ReturnType BCM_init(void)
{
	uint8_t BCM_channelCounter=0;
	
	
	/* Initialize the Receiver Channels */
	for(BCM_channelCounter=0; BCM_channelCounter<BCM_RX_COM_DEVICES_USED; BCM_channelCounter++)
	{
		strRxComChannels_Config[BCM_channelCounter].BCM_RxIntEnable(strRxComChannels_Config[BCM_channelCounter].channelId);
		Interrupt_install(strRxComChannels_Config[BCM_channelCounter].BCM_Rx_INTVector_ID, BCM_RxCallBack);
	}
	
	/* Initialize the Transmitter Channels */
	for(BCM_channelCounter=0; BCM_channelCounter<BCM_TX_COM_DEVICES_USED; BCM_channelCounter++)
	{
		Interrupt_install(BCM_TxConfigurations[BCM_channelCounter].BCM_Tx_INTVector_ID, BCM_TxCallBack_Function);
	}
	
	return E_OK;
}

/************************************************************************************
* Parameters (in): comChannelId
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: ask BCM to get any received data from a certain com. channel
************************************************************************************/
Std_ReturnType BCM_getData(uint8_t comChannelId, uint8_t* BCM_RxData_ptr, uint8_t BCM_RxData_size)
{
	/* get the currently saved data from the given com. channel buffer at BCM */
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < BCM_RxData_size; u8_loopCounter++)
	{
		BCM_RxData_ptr[u8_loopCounter] = arrStr_RxComChannels[comChannelId].BCM_ComChannelRxBuffer[u8_loopCounter];
	}
	return E_OK;
}
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state BCM Rx.
************************************************************************************/
Std_ReturnType BCM_RxMainFunction()
{
	return E_OK;
}
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
void BCM_RxCallBack(uint8_t IntVector_ID)
{
	uint8_t u8_RxData;
	static uint8_t u8_frameState = NOT_RECEIVED_YET;
	static uint8_t u8_dataSizeState = NOT_RECEIVED_YET;
	static uint8_t u8_dataSize = Initial_Value;
	static uint8_t u8_frameReceiveState = IDLE;
	static uint8_t u8_dataCounter = Initial_Value;
	
	/* read byte from HW buffer */
	strRxComChannels_Config[COM_CHANNEL_0_ID].channelReadFun(strRxComChannels_Config[COM_CHANNEL_0_ID].channelId, &u8_RxData);
	
	/* check for BCM ID */
	if(u8_frameState == NOT_RECEIVED_YET)
	{
		if(u8_RxData == BCM_ID)
		{
			u8_frameState = RECEIVED;
			return;
		}
		else
		{
			return;
		}
	}
	
	/* confirm size state */
	if(u8_dataSizeState == NOT_RECEIVED_YET && u8_frameState == RECEIVED)
	{
		/* save frame size */
		u8_dataSize = u8_RxData - '0';
		/* change state */
		u8_dataSizeState = RECEIVED;
		return;
	}
	
	/* start receiving data */
	if(u8_dataSizeState == RECEIVED && u8_frameState == RECEIVED && u8_frameReceiveState != RECEIVED)
	{
		/* change state to running */
		u8_frameReceiveState = RUNNING;
		/* save current byte into buffer using channelReadFun */
		arrStr_RxComChannels[COM_CHANNEL_0_ID].BCM_ComChannelRxBuffer[u8_dataCounter] = u8_RxData;
		/* increment data counter */
		u8_dataCounter++;
		/* check if last byte of data received then change state to RECEIVED */
		if(u8_dataCounter == u8_dataSize)
		{
			u8_frameReceiveState = RECEIVED;
			return;
		}

	}
	
	/* get check sum */
	if(u8_frameReceiveState == RECEIVED)
	{
		/* calculate check sum of data and save it */
		arrStr_RxComChannels[COM_CHANNEL_0_ID].BCM_ComChannelRxBuffer_Chksum = u8_RxData;
		/* reset states */
		u8_frameState = NOT_RECEIVED_YET;
		u8_dataSizeState = NOT_RECEIVED_YET;
		u8_dataSize = Initial_Value;
		u8_frameReceiveState = IDLE;
		u8_dataCounter = Initial_Value;
	}
}

Std_ReturnType BCM_Transmit(BCM_DeviceID_t BCM_Channel_ID,
							uint8_t *BCM_TxData_ptr,
							uint16_t BCM_TxData_Size, BCM_CallBack_t BCM_CB_Ptr)
{
	uint16_t currentRqCounter = BCM_TxRequests_Counter[BCM_Channel_ID];
	
	if(BCM_TxRequests_Counter[BCM_Channel_ID] == BCM_MAX_TX_REQUESTS)
	{
		if(BCM_TxRequests_Available[BCM_Channel_ID] < BCM_MAX_TX_REQUESTS)
		{
			BCM_TxRequests_Counter[BCM_Channel_ID] = 0;
			currentRqCounter = BCM_TxRequests_Counter[BCM_Channel_ID];
		}
		else
		{
			/* Request will be rejected */
			return E_NOT_OK;
		}
	}
	else
	{
		
	}
	
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_ChannelID = BCM_Channel_ID;
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_Data_ptr = BCM_TxData_ptr;
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_Data_Size = BCM_TxData_Size;
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_CB_Ptr = BCM_CB_Ptr;
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame[BCM_ID_INDEX] = BCM_ID;
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame[BCM_ID_INDEX+1] = '\0';
		
	uint8_t dataSize_string[5] = {0};
	integerToString(BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_Data_Size, dataSize_string, DEC);
	stringConcatenate(BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame ,dataSize_string);
	stringConcatenate(BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame
						, BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_Data_ptr);
// 		stringConcatenate(BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame
// 						, (uint8_t*)"\r");
	BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_FrameSize = stringLength(BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_DataFrame) -1;
	if (BCM_TxCurrentChannelsState[BCM_Channel_ID] == BCM_MAINFUNC_STATE_IDLE)
	{
		BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_State = BCM_REQUEST_TX_SENDING;
		BCM_TxCurrentRequest[BCM_Channel_ID] = &BCM_TxRequests[BCM_Channel_ID][currentRqCounter];
		BCM_TxCurrentChannelsState[currentRqCounter] = BCM_MAINFUNC_STATE_BYTE_SEND;
	}
	else
	{
		BCM_TxRequests[BCM_Channel_ID][currentRqCounter].BCM_TxRq_State = BCM_REQUEST_TX_PENDING;
	}
		
	BCM_TxConfigurations[BCM_Channel_ID].BCM_TxIntEnable(BCM_TxConfigurations[BCM_Channel_ID].BCM_Com_ID);
	BCM_TxRequests_Counter[BCM_Channel_ID]++;
	BCM_TxRequests_Available[BCM_Channel_ID]++;
	
	return E_OK;
}

Std_ReturnType BCM_TxMainFunction(void)
{
	uint8_t BCM_channelCounter=0;
	
	for(BCM_channelCounter=0; BCM_channelCounter<BCM_TX_COM_DEVICES_USED; BCM_channelCounter++)
	{
		switch(BCM_TxCurrentChannelsState[BCM_channelCounter])
		{
			case (BCM_MAINFUNC_STATE_IDLE):
			{
				break;
			}
			case (BCM_MAINFUNC_STATE_BYTE_SEND):
			{
				if(BCM_dataCounter[BCM_channelCounter] != BCM_TxCurrentRequest[BCM_channelCounter]->BCM_TxRq_FrameSize)
				{
					BCM_TxConfigurations[BCM_channelCounter].BCM_TxSender(BCM_TxConfigurations[BCM_channelCounter].BCM_Com_ID
													,BCM_TxCurrentRequest[BCM_channelCounter]->BCM_TxRq_DataFrame[BCM_dataCounter[BCM_channelCounter]]);
					BCM_TxCurrentChannelsState[BCM_channelCounter] = BCM_MAINFUNC_STATE_ISR_WAIT;
				}
				else
				{
					BCM_TxCurrentChannelsState[BCM_channelCounter] = BCM_MAINFUNC_STATE_TX_COMPLETE;
				}
				break;
			}
			case (BCM_MAINFUNC_STATE_ISR_WAIT):
			{
				/* Time Out Looping */
				break;
			}
			case (BCM_MAINFUNC_STATE_TX_COMPLETE):
			{
				BCM_TxRequests_Available[BCM_channelCounter]--;
				BCM_TxCurrentRequest[BCM_channelCounter]->BCM_TxRq_CB_Ptr(NULL);
				BCM_dataCounter[BCM_channelCounter] = 0;
				BCM_cleanRequestData(BCM_TxCurrentRequest[BCM_channelCounter]);
				if(BCM_TxRequests_Available[BCM_channelCounter] > 0)
				{
					if(BCM_TxRequest_Index[BCM_channelCounter] == BCM_MAX_TX_REQUESTS-1)
					{
						BCM_TxRequest_Index[BCM_channelCounter] = 0;
					}
					else
					{
						BCM_TxRequest_Index[BCM_channelCounter]++;
					}
					uint16_t currentRqIndex = BCM_TxRequest_Index[BCM_channelCounter];
					if(BCM_TxRequests[BCM_channelCounter][currentRqIndex].BCM_TxRq_State == BCM_REQUEST_TX_PENDING)
					{
						BCM_TxCurrentRequest[BCM_channelCounter] = &BCM_TxRequests[BCM_channelCounter][currentRqIndex];
						BCM_TxCurrentChannelsState[BCM_channelCounter] = BCM_MAINFUNC_STATE_BYTE_SEND;
					}
					else
					{
						
					}
				}
				else
				{
					BCM_TxCurrentChannelsState[BCM_channelCounter] = BCM_MAINFUNC_STATE_IDLE;
				}
				break;
			}
			default:
			{
				return E_NOT_OK;
			}
		}
	}
	
	return E_OK;
}


void BCM_TxCallBack_Function(uint8_t IntVector_ID)
{
	uint8_t BCM_channelCounter=0;
	
	for(BCM_channelCounter=0; BCM_channelCounter<BCM_TX_COM_DEVICES_USED; BCM_channelCounter++)
	{
		if(BCM_TxConfigurations[BCM_channelCounter].BCM_Tx_INTVector_ID == IntVector_ID)
		{
			BCM_TxCurrentChannelsState[BCM_channelCounter] = BCM_MAINFUNC_STATE_BYTE_SEND;
			BCM_dataCounter[BCM_channelCounter]++;
			return;
		}
		else
		{
			
		}
	}
}

Std_ReturnType BCM_cleanRequestData(BCM_TxRequestData_t *BCM_requestDataPtr)
{
	BCM_requestDataPtr->BCM_ChannelID = 0;
	BCM_requestDataPtr->BCM_TxRq_CB_Ptr = NULL_PTR;
	//BCM_requestDataPtr->BCM_TxRq_Data_ptr = NULL_PTR;
	BCM_requestDataPtr->BCM_TxRq_Data_Size = 0;
	EmptyString(BCM_requestDataPtr->BCM_TxRq_DataFrame);
	BCM_requestDataPtr->BCM_TxRq_State = BCM_REQUEST_TX_CLOSED;
	
	return E_OK;
}
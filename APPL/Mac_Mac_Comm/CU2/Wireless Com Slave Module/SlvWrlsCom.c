/*
 * SlvWrlsCom.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "SlvWrlsCom.h"
#include "APPL/Mac_Mac_Comm/MemM Module/MemM.h"
#include "Microcontroller/Delay Module/Delay.h"
#include "ServiceL/FreeRTOS/Source/include/FreeRTOS.h"
#include "ServiceL\FreeRTOS\Source\include\task.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define MAX_POSSIBLE_BR							5U
#define WRLS_COM_VALID_DEVICE_FLAG_VALUE		0xDDU
#define WRLS_COM_UNIQUE_PACKET_ID				0xAAU
#define WRLS_COM_DEVICE_DATA_REQ_TYPE			0x02U
#define WRLS_COM_CONNECTED_DEVICE_MAC_SIZE		12
#define WRLS_COM_MAX_DEVICES_TO_INQUIRE			2U
#define WRLS_COM_MAX_DEVICE_DATA_TRIALS			5U
#define HANDSHAKE_SEND							0U
#define HANDSHAKE_RCV							1U
#define HANDSHAKE_FAIL							2U
#define DEVICE_DATA_SEND						0U
#define DEVICE_DATA_RCV							1U
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
uint8_t DeviceMACAddress[WRLS_COM_CONNECTED_DEVICE_MAC_SIZE];
uint8_t WrlsCom_ValidDevFlag = 0;
static uint32_t WrlsCom_PossibleBaudRates[MAX_POSSIBLE_BR] = {38400, 9600, 19200, 57600, 115200};
static uint8_t WrlsCom_State = WRLSCOM_STATE_UNINIT;
uint8_t AvailableDevices[WRLS_COM_MAX_DEVICES_TO_INQUIRE][WRLS_COM_CONNECTED_DEVICE_MAC_SIZE] = {0};
WrlsCom_Data_t Data_Info;
uint8_t RX_DataBuffer[WRLS_COM_MAX_DATA_SIZE] = {0};
	
uint8_t WrlsCom_DeviceDataPacket[23] = {0};
/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS LIKE MACROS -*-*-*-*-*-*/


/*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- STATIC FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

static Std_ReturnType WrlsCom_checkBluetoothConfiguaration(void)
{
	uint8_t DeviceRole=0;
	/* Get the current role of the device */
	if(Blth_getRole(&DeviceRole) == E_NOT_OK)
	{
	}
	if(DeviceRole != WrlsCom_BlthDevice_constConfig.Device_Role)
	{
		Blth_setRole(WrlsCom_BlthDevice_constConfig.Device_Role);
	}
	else
	{
		/* Successful */
	}
	
	/* Check the name of the device */
	uint8_t currentName[WRLS_COM_MAX_NAME_SIZE] = {0};
	if(Blth_getName(currentName) == E_NOT_OK)
	{
	}
	if(stringCmp(currentName, (uint8_t*)WrlsCom_BlthDevice_constConfig.Device_Name) == FALSE)
	{
		/* If the name is not equal */
		/* Set the device with the new name */
		Blth_RenameDevice((uint8_t*)WrlsCom_BlthDevice_constConfig.Device_Name);
	}
	else
	{
		/* Successful */
	}
	
	/* Check the name of the device */
	uint8_t currentPass[WRLS_COM_MAX_PSWRD_SIZE] = {0};
	if(Blth_getPassword(currentPass) == E_NOT_OK)
	{
	}
	if(stringCmp(currentPass, (uint8_t*)WrlsCom_BlthDevice_constConfig.Device_Pswrd) == FALSE)
	{
		/* If the password is not equal */
		/* Set the device with the new password */
		Blth_setPassword((uint8_t*)WrlsCom_BlthDevice_constConfig.Device_Pswrd);
	}
	else
	{
		/* Successful */
	}
	return E_OK;
}

/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/
Std_ReturnType WrlsCom_init(void)
{
	uint32_t currentBaudRate = 0;
	uint8_t BR_index=0;
	/* Enable Command Mode */
	Blth_EnableCommandMode();
	
	/* Self Test Baudrate settings */
	while (BR_index != MAX_POSSIBLE_BR)
	{
		currentBaudRate = WrlsCom_PossibleBaudRates[BR_index];
		Uart_setBaudRate(currentBaudRate);
		if((Blth_testDevice() == E_OK) || (Blth_testDevice() == E_OK))
		{
			break;
		}
		else
		{
			
		}
		BR_index++;
	}
	
	/* Check if all baudrates failed */
	if(BR_index == MAX_POSSIBLE_BR)
	{
		/* If all baud rates failed */
		/* Raise state to MALFUNCTION */
		WrlsCom_State = WRLSCOM_STATE_MALFUNCTION;
		return E_NOT_OK;
	}
	else if(BR_index != 0)
	{
		
	}
	
	/* Set the bluetooth to the required baudrate */
	Blth_setBaudRate(WrlsCom_BlthDevice_constConfig.Device_BaudRate);
	
	/* Set the Uart to the required baudrate */
	Uart_setBaudRate(WrlsCom_BlthDevice_constConfig.Device_BaudRate);
	
	/* Check the device's latest configurations */
	WrlsCom_checkBluetoothConfiguaration();
	
	uint8_t DeviceOwnMacAddr[13]={0};
	Blth_getOwnMacAddress(DeviceOwnMacAddr);
	WrlsCom_DeviceDataPacket[0] = WRLS_COM_UNIQUE_PACKET_ID;
	WrlsCom_DeviceDataPacket[1] = WRLS_COM_DEVICE_DATA_REQ_TYPE;
	WrlsCom_DeviceDataPacket[2] = 0x13;
	stringConcatenate(WrlsCom_DeviceDataPacket, WrlsCom_BlthDevice_constConfig.Device_Name);
	stringConcatenate(WrlsCom_DeviceDataPacket,DeviceOwnMacAddr);
	
	Blth_EnableDataMode();
	/* Set Animation LED to Device Search Pattern */
	
	WrlsCom_State = WRLSCOM_STATE_DEVICE_SEARCH;

	return E_OK;
}

void WrlsCom_mainFunction(void *pvParam)
{
	uint8_t verifyState = HANDSHAKE_RCV;
	uint8_t deviceDataState = DEVICE_DATA_RCV;
	uint8_t receivedData[10] = {0};
	while (1)
	{
		switch(WrlsCom_State)
		{
			case WRLSCOM_STATE_DEVICE_SEARCH:
			{
				if(Blth_isConnected() == E_OK)
				{
					Blth_Data();
					WrlsCom_State = WRLSCOM_STATE_VERIFICATION;
				}
				else
				{
				}
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_RECEIVING:
			{
				Blth_readData(RX_DataBuffer);
				WrlsCom_State = WRLSCOM_STATE_DATA_READY;
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_DATA_READY:
			{
				
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_IDLE:
			{
				/* Waiting for Orders after connection is successful */
				if(Blth_isDataAvailable() == E_OK)
				{
					WrlsCom_State = WRLSCOM_STATE_RECEIVING;
				}
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_MALFUNCTION:
			{
				/* Notify with MALFUNTION Pattern */
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
/*--*/		case WRLSCOM_STATE_CONNECTED:
			{
				/* Send Device Data Packet */
				switch(deviceDataState)
				{
					case DEVICE_DATA_SEND:
					{
						Blth_Data();
						Blth_sendData((uint8_t*)WrlsCom_DeviceDataPacket);
						MemM_writeBlock(MEMM_CONNECTED_DEVICE_DATA_PACK_ID, receivedData, MEMM_CONNECTED_DEVICE_DATA_PACK_SIZE);
						WrlsCom_State = WRLSCOM_STATE_IDLE;
						EmptyString(receivedData);
						/* Get Tick Count */
						entryTick = xTaskGetTickCount();
					}
					case DEVICE_DATA_RCV:
					{
						if(Blth_readDataAsync(receivedData) == E_OK)
						{
							if((receivedData[0] = WRLS_COM_UNIQUE_PACKET_ID) && (receivedData[1] = WRLS_COM_DEVICE_DATA_REQ_TYPE))
							{
								deviceDataState = DEVICE_DATA_SEND;
							}
							else
							{
							}
						}
						else
						{
						}
					}
					default:
					{
						break;
					}
				}
				
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
/*--*/		case WRLSCOM_STATE_VERIFICATION:
			{
				/* Verify the device connection by sending Handshake */
				switch(verifyState)
				{
					case HANDSHAKE_SEND:
					{
						Blth_Data();
						Blth_sendData((uint8_t*)WrlsCom_BlthDevice_Handshake_Packet);
						WrlsCom_State = WRLSCOM_STATE_CONNECTED;
					}
					case HANDSHAKE_RCV:
					{
						if(Blth_readDataAsync(receivedData) == E_OK)
						{
							if(stringCmp(receivedData, (uint8_t*)WrlsCom_BlthDevice_Handshake_Packet) == TRUE)
							{
								verifyState = HANDSHAKE_RCV;
								EmptyString(receivedData);
							}
						}
						else
						{
						}
					}
					default:
					{
					}
				}
				
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_DEVICE_ERASE:
			{
				/* Erase */
				/* Act as there is no device */
				WrlsCom_ValidDevFlag = 0xFF;
				MemM_writeBlock(MEMM_VALID_DEVICE_FLAG_ID, &WrlsCom_ValidDevFlag, MEMM_VALID_DEVICE_FLAG_SIZE);
				/* Advertising Mode */
				WrlsCom_State = WRLSCOM_STATE_IDLE;
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			case WRLSCOM_STATE_UNINIT:
			{
				break;
			}
			/************************************************************************************
			 ------------------------------------------------------------------------------------
			 ************************************************************************************/
			default:
			{
				break;
			}
		}
		
		/* FreeRTOS vTaskDelay Function */
		vTaskDelay(50);
	}
}

Std_ReturnType WrlsCom_TransmitData(uint8_t *Data_Ptr, uint8_t Data_Size)
{
	WrlsCom_State = WRLSCOM_STATE_SENDING;
	Data_Info.DataSize = Data_Size;
	stringCopy(Data_Ptr, Data_Info.DataToBeSent);
	Data_Info.Transmitting_State = WRLS_COM_DATA_SENDING;
	
	return E_OK;
}

Std_ReturnType WrlsCom_ReceiveData(uint8_t *Data_Ptr, uint8_t *Data_Size)
{
	WrlsCom_State = WRLSCOM_STATE_IDLE;
	*Data_Size = stringLength(RX_DataBuffer);
	stringCopy(RX_DataBuffer, Data_Ptr);
	EmptyString(RX_DataBuffer);
	
	return E_OK;
}

Std_ReturnType WrlsCom_GetDataState(uint8_t *transmissionState)
{
	*transmissionState = Data_Info.Transmitting_State;
	return E_OK;
}

Std_ReturnType WrlsCom_getState(uint8_t *DeviceState)
{
	*DeviceState = WrlsCom_State;
	
	return E_OK;
}

Std_ReturnType WrlsCom_setState(uint8_t DeviceState)
{
	if((WrlsCom_State == WRLSCOM_STATE_IDLE) || (WrlsCom_State == WRLSCOM_STATE_MALFUNCTION))
	{
		WrlsCom_State = DeviceState;
	}
	else
	{
		return E_NOT_OK;
	}	
	return E_OK;
}
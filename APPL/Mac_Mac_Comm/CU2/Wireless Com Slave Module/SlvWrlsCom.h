/*
 * SlvWrlsCom.h
 *
 * Created: 9/8/2021 1:58:48 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef SLVWRLSCOM_H_
#define SLVWRLSCOM_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "ECUAL/Bluetooth Module/Bluetooth.h"
#include "SlvWrlsCom_LCfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

#define WRLSCOM_STATE_UNINIT				0U
#define WRLSCOM_STATE_MALFUNCTION			1U
#define WRLSCOM_STATE_DEVICE_SEARCH			2U
#define WRLSCOM_STATE_IDLE					3U
#define WRLSCOM_STATE_VERIFICATION			4U
#define WRLSCOM_STATE_CONNECTED				5U
#define WRLSCOM_STATE_DATA_READY			6U
#define WRLSCOM_STATE_DEVICE_ERASE			7U
#define WRLSCOM_STATE_RECEIVING				9U
#define WRLSCOM_STATE_SENDING				10U

#define WRLS_COM_MAX_DATA_SIZE				30U
#define WRLS_COM_DATA_SENDING				0U
#define WRLS_COM_DATA_SENT					1U
#define WRLS_COM_DATA_FAIL					2U
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- Data Types -*-*-*-*-*-*-*-*-*/

typedef struct  
{
	uint8_t	Transmitting_State;
	uint8_t DataToBeSent[WRLS_COM_MAX_DATA_SIZE];
	uint8_t DataSize;
}WrlsCom_Data_t;

typedef struct
{
	uint32_t Device_BaudRate; 
	uint8_t Device_Role;
	uint8_t Device_Name[WRLS_COM_MAX_NAME_SIZE];
	uint8_t Device_Pswrd[WRLS_COM_MAX_PSWRD_SIZE];
}WrlsCom_Config;


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*-*-*-*/

Std_ReturnType WrlsCom_init(void);

void WrlsCom_mainFunction(void *pvParam);

Std_ReturnType WrlsCom_getState(uint8_t *DeviceState);

Std_ReturnType WrlsCom_setState(uint8_t DeviceState);

Std_ReturnType WrlsCom_TransmitData(uint8_t *Data_Ptr, uint8_t Data_Size);


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*-*- Extern Variables -*-*-*-*-*-*-*-*-*-*/
extern const WrlsCom_Config WrlsCom_BlthDevice_constConfig;

extern const uint8_t WrlsCom_BlthDevice_Handshake_Packet[6];
#endif /* SLVWRLSCOM_H_ */
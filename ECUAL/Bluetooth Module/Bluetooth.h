/*
 * Bluetooth.h
 *
 * Created: 9/8/2021 1:58:48 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "MCAL\Uart Module\Uart.h"
#include "MCAL\Dio Module\Dio.h"
#include "Bluetooth_Cfg.h"
#include "Libraries/Utility Module/Utility.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

#define BLTH_ROLE_SLAVE			0U
#define BLTH_ROLE_MASTER		1U
#define BLTH_MAX_MAC_ADDR_SIZE				13U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- Data Types -*-*-*-*-*-*-*-*-*/



/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS LIKE MACROS -*-*-*-*-*-*/
#define Blth_Cmd()					Dio_writePin(BLTH_ENABLE_PIN, PIN_HIGH)
#define Blth_Data()		 			Dio_writePin(BLTH_ENABLE_PIN, PIN_LOW)
#define Blth_powerON()				Dio_writePin(BLTH_POWER_PIN,PIN_HIGH)
#define Blth_powerOFF()				Dio_writePin(BLTH_POWER_PIN, PIN_LOW)


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*-*-*-*/

Std_ReturnType Blth_EnableCommandMode(void);

Std_ReturnType Blth_EnableDataMode(void);

Std_ReturnType Blth_init(void);

Std_ReturnType Blth_isConnected(void);

Std_ReturnType Blth_Disconnect(void);

Std_ReturnType Blth_sendData(uint8_t *DataPtr);

Std_ReturnType Blth_isDataAvailable(void);

Std_ReturnType Blth_readData(uint8_t *DataPtr);

Std_ReturnType Blth_readDataAsync(uint8_t *DataPtr);

Std_ReturnType Blth_sendCommand(uint8_t* CommandPtr, uint8_t CommandSize);

Std_ReturnType Blth_getName(uint8_t *currentName);

Std_ReturnType Blth_RenameDevice(uint8_t *newName);

Std_ReturnType Blth_getRole(uint8_t *currentRole);

Std_ReturnType Blth_setRole(uint8_t Blth_Role);

Std_ReturnType Blth_setSlave(void);

Std_ReturnType Blth_setMaster(void);

Std_ReturnType Blth_setBaudRate(uint32_t newBaudRate);

Std_ReturnType Blth_getBaudRate(uint32_t *currentBaudRate);

Std_ReturnType Blth_getOwnMacAddress(uint8_t *ownMacAddress);

Std_ReturnType Blth_InquiryMode(uint8_t DeviceMacAddress[][BLTH_MAX_MAC_ADDR_SIZE], uint8_t devicesNum, uint8_t timeOut);

Std_ReturnType Blth_LinkWithDevice(uint8_t *deviceMacAddress);

Std_ReturnType Blth_getPassword(uint8_t *currentPassword);

Std_ReturnType Blth_setPassword(uint8_t *newPassword);

Std_ReturnType Blth_checkOK(void);

Std_ReturnType Blth_testDevice(void);

Std_ReturnType Blth_restoreDefault(void);




#endif /* BLUETOOTH_H_ */
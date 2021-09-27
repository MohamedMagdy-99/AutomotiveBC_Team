/*
 * Dio.h
 *
 * Created: 7/13/2021 7:54:25 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef DIO_H_
#define DIO_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Dio_LCfg.h"
#include "Platform_Types.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*-* PIN NUMBERS *-*/
#define PIN_0		0
#define PIN_1		1
#define PIN_2		2
#define PIN_3		3
#define PIN_4		4
#define PIN_5		5
#define PIN_6		6
#define PIN_7		7
/*-* PORT NUMBERS *-*/
#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

/*-* PIN VALUES *-*/
#define PIN_LOW		0U
#define PIN_HIGH	1U
/*-* PIN RESISTOR *-*/
#define PIN_PDR		0U /* Pull Down Resistor */
#define PIN_PUR		1U /* Pull Up Resistor */
/*-* DIO Module Status *-*/
#define DIO_NOT_INITIALIZED			0U
#define DIO_INITIALIZED				1U
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- PRIMITIVE TYPES -*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- ENUMS -*-*-*-*-*-*/

typedef enum{
	DIO_STATUS_ERROR_NOK,
	DIO_STATUS_ERROR_OK,
	DIO_STATUS_PIN_ID_INVALID,
	DIO_STATUS_PIN_NUM_INVALID,
	DIO_STATUS_PORT_NUM_INVALID,
	DIO_STATUS_NULL_ARGUMENT,
	DIO_STATUS_NOT_INIT,
	DIO_STATUS_ALREADY_INIT
}enuDio_Status_t;

typedef enum{
	DIO_PIN_DIR_INPUT,
	DIO_PIN_DIR_OUTPUT
}enuDio_Direction_t;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- STRUCTS -*-*-*-*-*-*/

typedef struct
{
	uint8_t u8_PortNum;
	uint8_t u8_PinNum;
	enuDio_Direction_t u8_Direction;
	uint8_t u8_InitState; /* 1 or 0 for output pin // Pull Down or Pull Up for Input pin*/
}strDio_Config_t;


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*/

/*- Initialize DIO Pins -*/
enuDio_Status_t Dio_init(strDio_Config_t* pstrDio_pins);

/*- Write DIO Pin -*/
enuDio_Status_t Dio_writePin(uint8_t u8_pinID, uint8_t u8_pinValue);

/*- Toggle DIO Pin -*/
enuDio_Status_t Dio_togglePin(uint8_t u8_pinID);

/*- Read DIO Pin -*/
enuDio_Status_t Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue);

/*- Change Pin Direction -*/
enuDio_Status_t Dio_changePinDirection(uint8_t u8_pinID, enuDio_Direction_t u8_pinDirection, uint8_t u8_pinInitialState);

/* ToDo *//*
enuDio_Status_t Dio_readPort(uint8_t u8_PortNum, uint8_t *pu8_portValue);
enuDio_Status_t Dio_writePort(uint8_t u8_PortNum, uint8_t u8_portValue);
*//***************/

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Dio and other modules */
extern strDio_Config_t strDio_pins[DIO_USED_PINS_NUM];

#endif /* DIO_H_ */
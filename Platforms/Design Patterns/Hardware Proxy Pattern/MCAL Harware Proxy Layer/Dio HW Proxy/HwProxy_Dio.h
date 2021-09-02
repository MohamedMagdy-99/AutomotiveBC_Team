/*
 * HwProxt_Dio.h
 *
 * Created: 9/2/2021 7:54:01 PM
 *  Author: Mohamed Magdy
 */ 


#ifndef HWP_DIO_H_
#define HWP_DIO_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Dio.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*/

/*- Initialize DIO Pins -*/
Std_ReturnType HwP_Dio_init(strDio_Config_t* pstrDio_pins);

/*- Write DIO Pin -*/
Std_ReturnType  HwP_Dio_writePin(uint8_t u8_pinID, uint8_t u8_pinValue);

/*- Toggle DIO Pin -*/
Std_ReturnType  HwP_Dio_togglePin(uint8_t u8_pinID);

/*- Read DIO Pin -*/
Std_ReturnType  HwP_Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Dio and other modules */
extern strDio_Config_t strDio_pins[DIO_USED_PINS_NUM];

#endif /* HWP_DIO_H_ */
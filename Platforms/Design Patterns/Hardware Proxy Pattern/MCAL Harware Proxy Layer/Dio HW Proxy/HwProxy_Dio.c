/*
 * HwProxt_Dio.c
 *
 * Created: 9/2/2021 7:54:01 PM
 *  Author: Mohamed Magdy
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "HwProxy_Dio.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/
/*- Initialize DIO Pins -*/
Std_ReturnType HwP_Dio_init(strDio_Config_t* pstrDio_pins)
{
	Dio_init(pstrDio_pins);
	
	return E_OK;
}

/*- Write DIO Pin -*/
Std_ReturnType  HwP_Dio_writePin(uint8_t u8_pinID, uint8_t u8_pinValue)
{
	Dio_writePin(u8_pinID, u8_pinValue);
	
	return E_OK;
}

/*- Toggle DIO Pin -*/
Std_ReturnType  HwP_Dio_togglePin(uint8_t u8_pinID)
{
	Dio_togglePin(u8_pinID);
	
	return E_OK;
}

/*- Read DIO Pin -*/
Std_ReturnType  HwP_Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue)
{
	Dio_readPin(u8_pinID, pu8_pinValue);
	
	return E_OK;
}

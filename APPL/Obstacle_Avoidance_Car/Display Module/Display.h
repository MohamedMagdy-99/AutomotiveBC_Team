/*
 * Display.h
 *
 * Created: 13/8/2021 11:16:10 AM
 *  Author: Ahmed Nabil
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../../ECUAL/Lcd Module/Lcd.h"
#include "Display_LCfg.h"


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Display module state
 */
typedef uint8_t Display_State_t;

/*******************************************************************************
 *                              Structs										   *
 *******************************************************************************/
typedef struct
{
	uint8_t DisplayDeviceId;
	uint8_t xAxis_u8;
	uint8_t yAxis_u8;
	uint16_t integer_u16;
	uint8_t string_au8[16];
	
}str_DisplayDevicesData_t; 
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the module */
Std_ReturnType Display_init(uint8_t DisplayID_u8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printString(uint8_t DisplayID_u8, uint8_t *StringToPrint_pu8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printInteger(uint8_t DisplayID_u8, uint16_t u16_number);

/* Function used to set cursor position on a Display Screen with the given ID */
Std_ReturnType Display_setCursor(uint8_t DisplayID_u8, uint8_t xAxis, uint8_t yAxis);

/* Display module main periodic function */
Std_ReturnType Display_mainFunction(void);

/* functions to set Display parameters with a given ID */
Std_ReturnType set_DisplayInteger(uint8_t DisplayID_u8, uint16_t integer_u16);
Std_ReturnType set_DisplayString(uint8_t DisplayID_u8, uint8_t* string_au8);
Std_ReturnType set_DisplayCursorPosition(uint8_t DisplayID_u8, uint8_t xAxis_u8, uint8_t yAxis_u8);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern str_DisplayDevicesData_t Displays[DISPLAY_USED_NUM];

#endif /* DISPLAY_H_ */
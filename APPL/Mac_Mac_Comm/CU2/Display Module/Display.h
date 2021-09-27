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
#include "Lcd.h"
#include "SevenSegment.h"
#include "Display_LCfg.h"


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Display module state
 */
typedef uint8_t Display_State_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the module */
Std_ReturnType Display_init();

/* Function used to display an input string from the application on a Display Screen with the given ID */
Std_ReturnType Display_printString(uint8_t DisplayID_u8, uint8_t *StringToPrint_pu8);

/* Function used to display an input char from the application on a Display Screen with the given ID */
Std_ReturnType Display_printChar(uint8_t DisplayID_u8, uint8_t CharToPrint_u8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printInteger(uint8_t DisplayID_u8, uint16_t u16_number);

/* Function used to set cursor position on a Display Screen with the given ID */
Std_ReturnType Display_setCursor(uint8_t DisplayID_u8, uint8_t xAxis, uint8_t yAxis);

/* Function used to Clear Display Screen with the given ID */
Std_ReturnType Display_clearDisplay(uint8_t DisplayID_u8);

/* Display module main periodic functions */
void Display_SS_mainFunction(void *pvParameters);
void Display_Lcd_mainFunction(void *pvParameters);
/* Functions to set Lcd and 7Seg parameters */
Std_ReturnType Display_Lcd_setPingPongR1Info(uint8_t* au8_string, uint8_t u8_numChars);
Std_ReturnType Display_SS_set7SegInfo(uint8_t u8_num);
#endif /* DISPLAY_H_ */
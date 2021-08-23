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

/*
 * Data Type for Displays
 */
typedef uint8_t Displays_List_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the module */
Std_ReturnType Display_init(uint8_t DisplayID_u8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printString(uint8_t DisplayID_u8, uint8_t *StringToPrint_pu8);

/* Function used to display an input from the application on a Display Screen with the given ID */
Std_ReturnType Display_printInteger(uint8_t DisplayID_u8, uint16_t u16_number);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
const Displays_List_t Displays[DISPLAY_USED_NUM];

#endif /* DISPLAY_H_ */
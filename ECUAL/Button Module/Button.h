/*****************************************************************************
* Module: Button Module
* File Name: Button.h
* Description: Header file for Button Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/ 

#ifndef BUTTON_H_
#define BUTTON_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Button_Cfg.h"
#include "Dio.h"
#include "Std_Types.h"
#include "Common_Macros.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
/* Button State  */
#define BUTTON_STATE_RELEASED		(9U)
#define BUTTON_STATE_PRESSED		(10U)
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_Button_DioId;
	uint8_t u8_pullUpOrDown;
}strButton_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the button module */
Std_ReturnType Button_init(void);

/* Function to get the logic state of the button */
Std_ReturnType Button_getState(uint8_t u8_bttnID, uint8_t* pu8_state);

/* configuration variable */
extern strButton_Config_t strButton_Config[BUTTONS_USED];
#endif /* BUTTON_H_ */
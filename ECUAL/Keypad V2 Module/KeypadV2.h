/*****************************************************************************
* Module: Keypad V2 Module
* File Name: KeypadV2.h
* Description: Header file for Keypad V2 Module
* Author: Mohamed Magdy
* Date: 24-July-2021
******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_


/* INCLUDES */

#include "Std_Types.h"
#include "Common_Macros.h"
#include "Dio.h"
#include "KeypadV2_Cfg.h"
#include "Delay.h"

/* CONSTANTS */
#define KEYPAD_NO_KEY_PRESSED			(0xAAU)
#define KEYPAD_NO_KEY_PRESSED_CHAR     (0xDAU) 
#define KEYPAD_KEY_PRESSED				(10U)

#define KEYPAD_BUTTONS_NUM		(ROWS_NUM * COLS_NUM)


#define ROW_1					0
#define ROW_2					1
#define ROW_3					2
#define ROW_4					3

#define COLUMN_1				0
#define COLUMN_2				1
#define COLUMN_3				2
/*- TYPEDEFS --------------------------------------------------*/
typedef uint8_t Keypad_keyCurrentState_t;
/*- STRUCTS --------------------------------------------------*/
typedef struct
{
	uint8_t au8_keysPressed[ROWS_NUM][COLS_NUM];
	uint8_t u8_numberOfPressedKeys;
}strKeypadOutput_t;
/*************************/
/*- FUNCTION DECLARATIONS ----------------------------------*/


Std_ReturnType Keypad_Init(void);
Std_ReturnType Keypad_Scan(void);

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern strKeypadOutput_t Keypad_keyPadOutput;
extern Keypad_keyCurrentState_t Keypad_keyPressedOrNo[ROWS_NUM][COLS_NUM];
#endif /* KEYPAD_H_ */
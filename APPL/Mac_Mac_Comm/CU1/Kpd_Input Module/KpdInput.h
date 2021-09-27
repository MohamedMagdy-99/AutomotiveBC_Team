/*
 * KpdInput.h
 *
 * Created: 08-Sep-21 10:23:44 PM
 *  Author: Mohamed Magdy
 */ 


#ifndef KPDINPUT_H_
#define KPDINPUT_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "ECUAL/Keypad V2 Module/KeypadV2.h"
#include "KpdInput_Cfg.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define KPDINPUT_PATTERN_DURATION_CONFIRMED_SECS		(3000U)
#define KPDINPUT_TASK_PERIODICITY						(125U)
#define KPDINPUT_PATTERN_CHECK_PERIODICITY				(KPDINPUT_TASK_PERIODICITY + DEBOUNCE_DELAY_MS)

#define KPDINPUT_PATTERN_CONFIRMATION_COUNTS			(KPDINPUT_PATTERN_DURATION_CONFIRMED_SECS/KPDINPUT_PATTERN_CHECK_PERIODICITY)
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- PRIMITIVE TYPES -*-*-*-*-*-*/
typedef uint8_t KpdInput_userInputModuleData_t;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- ENUMS -*-*-*-*-*-*/
typedef enum
{
	KPDINPUT_DATA,
	KPDINPUT_ERASE_DEVICE,
	KPDINPUT_PASS_RESET,
	KPDINPUT_IDLE	
}KpdInput_enuKeypadScanUserState_t;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- STRUCTS -*-*-*-*-*-*/
typedef struct
{
	KpdInput_userInputModuleData_t    InputModuleData;
	KpdInput_enuKeypadScanUserState_t KeypadScanState;
}KpdInput_strInputModuleDataInfo_t;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*/
/* Function to initialize the Keypad Input Module */
Std_ReturnType KeypadInputModule_Init(void);

/* Periodic Function of the Keypad Input Module */
void KeypadInputModule_mainFunction(void *pvParameters);

/* Getter Function for DataInfo to be used in other modules */
Std_ReturnType KeypadInputModule_getDataInfo(KpdInput_strInputModuleDataInfo_t* DataInfo);







#endif /* KPDINPUT_H_ */
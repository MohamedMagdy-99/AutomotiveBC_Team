/*
 * Ext_INT.h
 *
 * Created: 7/27/2021 3:03:04 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_


#include "ISR_Regs.h"
#include "Std_Types.h"
#include "Common_Macros.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef void (*pfExtINT_CallBack_t)(uint8_t);

/* CONSTANTS */

#define LOW_LEVEL			0			//The low level of INT0 generates an interrupt request.
#define LOGIC_CHANGE		1			//Any logical change on INT0 generates an interrupt request.
#define FALLING_EDGE		2			//The falling edge of INT0 generates an interrupt request.
#define RISING_EDGE			3			//The rising edge of INT0 generates an interrupt request.
/*************************************************************************************/
#define EXT_INTERRUPT_PINS	3U
#define EXT_INT0			0U
#define EXT_INT1			1U
#define EXT_INT2			2U
/*************************************************************************************/
/*- Function Declarations
-------------------------------*/

void DisableExtINT(uint8_t ExtINT_ID);
void EnableExtINT(uint8_t ExtINT_ID, uint8_t senseControl);
void setExtINTCallback(uint8_t ExtINT_ID, pfExtINT_CallBack_t FunToBeCalledInISR);



#endif /* EXT_INT_H_ */

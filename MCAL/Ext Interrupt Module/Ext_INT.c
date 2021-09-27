/*
 * Ext_INT.c
 *
 * Created: 7/27/2021 3:02:47 PM
 *  Author: Ahmed Nabil
 */ 
#include "Ext_INT.h"
#include "../../Microcontroller/Interrupt Handler/Interrupt_Interface.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

//static pfExtINT_CallBack_t ExtIntCallback[EXT_INTERRUPT_PINS]={NULL_PTR};

/*- Function Definitions
-------------------------------*/
void EnableExtINT(uint8_t ExtINT_ID, uint8_t senseControl)
{
	switch(senseControl)
	{
		case(LOW_LEVEL):
		{
			if(ExtINT_ID == EXT_INT0)
			{
				CLEAR_BIT(MCUCR_R, ISC00_B);
				CLEAR_BIT(MCUCR_R, ISC01_B);
				SET_BIT(GICR_R, INT0_B);
			}
			else if (ExtINT_ID == EXT_INT1)
			{
				CLEAR_BIT(MCUCR_R, ISC10_B);
				CLEAR_BIT(MCUCR_R, ISC11_B);
				SET_BIT(GICR_R, INT1_B);
			}
			else
			{
				
			}
			break;
		}
		case(LOGIC_CHANGE):
		{
			if(ExtINT_ID == EXT_INT0)
			{
				SET_BIT(MCUCR_R, ISC00_B);
				CLEAR_BIT(MCUCR_R, ISC01_B);
				
				SET_BIT(GICR_R, INT0_B);
			}
			else if (ExtINT_ID == EXT_INT1)
			{
				SET_BIT(MCUCR_R, ISC10_B);
				CLEAR_BIT(MCUCR_R, ISC11_B);
				SET_BIT(GICR_R, INT1_B);
			}
			else
			{
				
			}
			break;
		}
		case(FALLING_EDGE):
		{
			if(ExtINT_ID == EXT_INT0)
			{
				SET_BIT(MCUCR_R, ISC00_B);
				CLEAR_BIT(MCUCR_R, ISC01_B);
				SET_BIT(GICR_R, INT0_B);
			}
			else if (ExtINT_ID == EXT_INT1)
			{
				SET_BIT(MCUCR_R, ISC10_B);
				CLEAR_BIT(MCUCR_R, ISC11_B);
				SET_BIT(GICR_R, INT1_B);
			}
			else if (ExtINT_ID == EXT_INT2)
			{
				CLEAR_BIT(MCUCSR_R, ISC2_B);
				SET_BIT(GICR_R, INT2_B);
			}
			else
			{
				
			}
			break;
		}
		case(RISING_EDGE):
		{
			if(ExtINT_ID == EXT_INT0)
			{
				SET_BIT(MCUCR_R, ISC00_B);
				SET_BIT(MCUCR_R, ISC01_B);
				SET_BIT(GICR_R, INT0_B);
			}
			else if (ExtINT_ID == EXT_INT1)
			{
				SET_BIT(MCUCR_R, ISC10_B);
				SET_BIT(MCUCR_R, ISC11_B);
				SET_BIT(GICR_R, INT1_B);
			}
			else if (ExtINT_ID == EXT_INT2)
			{
				SET_BIT(MCUCSR_R, ISC2_B);
				SET_BIT(GICR_R, INT2_B);
			}
			else
			{
				
			}
			break;
		}
		default: break;
	}
	EnableGlobalInterrupts();
}

void DisableExtINT(uint8_t ExtINT_ID)
{
	switch(ExtINT_ID)
	{
		case EXT_INT0:
		{
			CLEAR_BIT(GICR_R, INT0_B);
			break;
		}
		case EXT_INT1:
		{
			CLEAR_BIT(GICR_R, INT1_B);
			break;
		}
		case EXT_INT2:
		{
			CLEAR_BIT(GICR_R, INT2_B);
			break;
		}
		default:
		{
			break;
		}
	}
}

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by external interrupt 0 ISR
******************************************************************************************/
void setExtINTCallback(uint8_t ExtINT_ID, pfExtINT_CallBack_t FunToBeCalledInISR)
{
	switch(ExtINT_ID)
	{
		case EXT_INT0:
		{
			Interrupt_install(INT0_IRQ, FunToBeCalledInISR);
			break;
		}
		case EXT_INT1:
		{
			Interrupt_install(INT1_IRQ, FunToBeCalledInISR);
		    break;
		}
		case EXT_INT2:
		{
			Interrupt_install(INT2_IRQ, FunToBeCalledInISR);
			break;
		}
		default:
		{
			break;
		}
	}
}
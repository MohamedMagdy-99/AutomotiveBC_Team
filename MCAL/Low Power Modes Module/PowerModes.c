/*****************************************************************************
* Module: Low Power Modes Module
* File Name: PowerModes.c
* Description: Source file for Low Power Modes Module
* Author: Mohamed Magdy
* Date: 30-Aug-2021
******************************************************************************/
#include "PowerModes.h"


/*- Function Definitions
-------------------------------*/

/*****************************************************************************************
* Parameters (in): low power mode
* Parameters (out): error state
* Return value: Std_ReturnType
* Description: sets a given low power mode
******************************************************************************************/
Std_ReturnType LPM_EnterLowPowerMode(LPM_LowPowerMode_t sleepMode)
{

	switch(sleepMode)
	{
		case(IDLE_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);
			CLEAR_BIT(MCUCR_R, SM0_B);
			CLEAR_BIT(MCUCR_R, SM1_B);
			CLEAR_BIT(MCUCR_R, SM2_B);
			break;
		}
		case(POWER_DOWN_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);			
			CLEAR_BIT(MCUCR_R, SM0_B);
			SET_BIT(MCUCR_R, SM1_B);
			CLEAR_BIT(MCUCR_R, SM2_B);
			break;
		}
		case(POWER_SAVE_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);			
			SET_BIT(MCUCR_R, SM0_B);
			SET_BIT(MCUCR_R, SM1_B);
			CLEAR_BIT(MCUCR_R, SM2_B);			
			break;
		}
		case(STANDBY_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);			
			CLEAR_BIT(MCUCR_R, SM0_B);
			SET_BIT(MCUCR_R, SM1_B);
			SET_BIT(MCUCR_R, SM2_B);			
			break;
		}
		case(EXTENDED_STANDBY_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);			
			SET_BIT(MCUCR_R, SM0_B);
			SET_BIT(MCUCR_R, SM1_B);
			SET_BIT(MCUCR_R, SM2_B);			
			break;
		}	
		case(ADC_NOISE_REDUCTION_MODE):
		{
			/* enable low power mode */
			SET_BIT(MCUCR_R, SE_B);			
			SET_BIT(MCUCR_R, SM0_B);
			CLEAR_BIT(MCUCR_R, SM1_B);
			CLEAR_BIT(MCUCR_R, SM2_B);
			break;
		}
		default: return E_NOT_OK;									
	}
	
	return E_OK;
}


/*****************************************************************************************
* Parameters (in): none
* Parameters (out): error state
* Return value: Std_ReturnType
* Description: disables low power mode
******************************************************************************************/
Std_ReturnType LPM_DisableLowPowerMode(void)
{
	/* disable low power mode */
	CLEAR_BIT(MCUCR_R, SE_B);	
	
	return E_OK;
}
/*****************************************************************************
* Module: Led Module
* File Name: Led.c
* Description:Source file for Led Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
/********************************INCLUDES************************************/
/*#include "..\..\Microcontroller\Platform_Types.h"
#include "..\..\Microcontroller\Std_types.h"*/
#include "..\..\MCAL\SWPwm Module\SWPwm.h"
#include "..\..\MCAL\Dio Module\Dio.h"
#include "LED.h"
/****************************************************************************/
/* Module initialization states */
#define LED_INITIALIZED         1U
#define LED_NOT_INITIALIZED     0U
uint8_t LEDInitState = LED_NOT_INITIALIZED ;
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to initialize LEDs
************************************************************************************************************************/
LEDReturn_t LED_Init(void)
{
   /*************************************ERROR HANDLING******************************************************/
   	if(LEDInitState == LED_INITIALIZED)
	   {
		   return LEDModuleIntialized ;
	   }
	   SWPwm_Init();
	   Dio_init(strDio_pins);
	   LEDInitState = LED_INITIALIZED;
	   return LED_E_OK;
	  
	
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Turn LED ON
************************************************************************************************************************/
LEDReturn_t LED_ON(LEDId_t LEDId)
{
	/***************ERROR HANDLEING***************************************/
	if (LEDId>=NUM_OF_LEDS_USED)
	{
		return LED_InvlidLEDId ;
	}
	/* check if ordinary or animated LED */
	if (LEDConfigArr[LEDId].LEDMode == ANIMATED_LED)
	{
		/* here the frequency is don't care and the duty cycle is 100 that means the LED will be High along the cycle */
		SWPwm_Start(LEDConfigArr[LEDId].LEDChannel,50,100);
		return LED_E_OK;
	}
	else if (LEDConfigArr[LEDId].LEDMode == ORDINARY_LED)
	{
		Dio_writePin(LEDConfigArr[LEDId].LEDChannel, PIN_HIGH);
		 return LED_E_OK;
		
	}
	else
	{
		/*Invalid LED Mode */
		return LED_InvalidMode ;
		
	}
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Turn LED OFF
************************************************************************************************************************/
LEDReturn_t LED_OFF(LEDId_t LEDId)
{
	/***************ERROR HANDLEING***************************************/
	if (LEDId>=NUM_OF_LEDS_USED)
	{
		return LED_InvlidLEDId ;
	}
	/* check if ordinary or animated LED */
	if (LEDConfigArr[LEDId].LEDMode == ANIMATED_LED)
	{
		/* Stop LED with its PWM Channel ID */
		SWPwm_Stop(LEDConfigArr[LEDId].LEDChannel);
		return LED_E_OK;
	}
	else if (LEDConfigArr[LEDId].LEDMode == ORDINARY_LED)
	{
		Dio_writePin(LEDConfigArr[LEDId].LEDChannel, PIN_LOW);
		return LED_E_OK;
		
	}
	else
	{
		/*Invalid LED Mode */
		return LED_InvalidMode ;
		
	}
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Toggle ordinary LED
************************************************************************************************************************/
LEDReturn_t LED_Toggle(LEDId_t LEDId)
{
	/***************ERROR HANDLEING***************************************/
	if (LEDId>=NUM_OF_LEDS_USED)
	{
		return LED_InvlidLEDId ;
	}
	/* Check if the LED is not Ordinary LED */
	
	if (LEDConfigArr[LEDId].LEDMode == ANIMATED_LED)
	{
		return LED_E_NOK;
	}
	else if (LEDConfigArr[LEDId].LEDMode == ORDINARY_LED)
	{
		Dio_writePin(LEDConfigArr[LEDId].LEDChannel, PIN_LOW);
		return LED_E_OK;
		
	}
	else
	{
		/*Invalid LED Mode */
		return LED_InvalidMode ;
		
	}
	
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Animate LED with specific frequency and duty cycle
************************************************************************************************************************/
LEDReturn_t LED_AnimationStrat(LEDId_t LEDId,uint32_t u32_Freq, uint8_t u8_DutyCycle)
{
	/****************************ERROR Handling ***********************************************/
	if (LEDId>=NUM_OF_LEDS_USED)
	{
		return LED_InvlidLEDId ;
	}
	/* Check if the LED is Not configured as Animated LED */
	if (LEDConfigArr[LEDId].LEDMode != ANIMATED_LED)
	{
		/* Return error */
		return LED_E_NOK;
	}
	else if (LEDConfigArr[LEDId].LEDMode == ANIMATED_LED)
	{
		SWPwm_Start(LEDConfigArr[LEDId].LEDChannel,u32_Freq,u8_DutyCycle);
		return LED_E_OK;
		
	}
	return LED_E_NOK;
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDConfig_t
* Description: This function used to Stop Animated
************************************************************************************************************************/
LEDReturn_t LED_AnimationStop(LEDId_t LEDId)
{
	/****************************ERROR Handling ***********************************************/
	if (LEDId>=NUM_OF_LEDS_USED)
	{
		return LED_InvlidLEDId ;
	}
	/* Check if the LED is Not configured as Animated LED */
	if (LEDConfigArr[LEDId].LEDMode != ANIMATED_LED)
	{
		/* Return error */
		return LED_E_NOK;
	}
	else if (LEDConfigArr[LEDId].LEDMode == ANIMATED_LED)
	{
		SWPwm_Stop(LEDConfigArr[LEDId].LEDChannel);
		return LED_E_OK;
		
	}
	return LED_E_NOK;
}
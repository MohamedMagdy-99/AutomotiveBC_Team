/*****************************************************************************
* Module: Gpt Module
* File Name: Gpt.c
* Description: Source file for GPT Module
* Author: Mohamed Magdy
* Date: 14-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "Gpt.h"
#include "../../Microcontroller/Atmega32 Registers/Gpt_Regs.h"

#define GPT_CHANNELS			3
/* it will be used to stop the timer1 if it started and didn't stop till reach this value */
#define MAX_TICKS_T1			100000000UL
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static volatile uint32_t gu32_T0_OvfCounts = 0;
static volatile uint32_t gu32_T1_OvfCounts = 0;
static volatile uint32_t gu32_T2_OvfCounts = 0;

static pfGpt_CallBack_t T0ovfCallback;
static pfGpt_CallBack_t T1ovfCallback;
static pfGpt_CallBack_t T2ovfCallback;

static uint32_t gu32_T1_OVF_TICKS =0;

enuGpt_Status_t Gpt_Status[GPT_CHANNELS] = {GPT_STATUS_ERROR_NOK};
enuGpt_initStatus_t Gpt_Init = GPT_NOT_INITIALIZED;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: initialize the gpt module according to the cfg file
******************************************************************************************/
enuGpt_Status_t GptInit(void) 
{
	if(Gpt_Init == GPT_INITIALIZED) return GPT_STATUS_ERROR_ALREADY_INIT;
	
	Gpt_Init = GPT_INITIALIZED;
		
	uint8_t u8_LoopCounter = 0;
	for(u8_LoopCounter=0 ; u8_LoopCounter < GPT_USED_CHANNELS ; u8_LoopCounter++)
	{
		switch(strGpt_Channels[u8_LoopCounter].u8_TimerNumber)
		{
			case(TIMER_0):
			{
				switch(strGpt_Channels[u8_LoopCounter].u8_Mode)
				{
					case(NORMAL_MODE):
					{
						/* making sure timer is OFF */
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);

						/* set to Normal mode */
						CLEAR_BIT(TCCR0_R, WGM01_B);
						CLEAR_BIT(TCCR0_R, WGM00_B);

						/* Initialize the timer count register */
						TCNT0_R = 0x00;
						
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
				break;
			}
			/*******************************************************************/
			case(TIMER_1):
			{
				switch(strGpt_Channels[u8_LoopCounter].u8_Mode)
				{
					case(NORMAL_MODE):
					{
						/* making sure timer is OFF */
						CLEAR_BIT(TCCR1B_R, CS10_B);
						CLEAR_BIT(TCCR1B_R, CS11_B);
						CLEAR_BIT(TCCR1B_R, CS12_B);

						/* set to Normal mode */
						CLEAR_BIT(TCCR1A_R, WGM10_B);
						CLEAR_BIT(TCCR1A_R, WGM11_B);
						CLEAR_BIT(TCCR1B_R, WGM12_B);
						CLEAR_BIT(TCCR1B_R, WGM13_B);
						/* Initialize the timer count register */
						TCNT1_R = 0x0000;
						
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
				break;
			}
			/************************************************************************/
			
			
			case(TIMER_2):
			{
				switch(strGpt_Channels[u8_LoopCounter].u8_Mode)
				{
					case(NORMAL_MODE):
					{
						/* making sure timer is OFF */
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);

						/* set to Normal mode */
						CLEAR_BIT(TCCR2_R, WGM21_B);
						CLEAR_BIT(TCCR2_R, WGM20_B);

						/* Initialize the timer count register */
						TCNT2_R = 0x00;
						
						break;
					}
					default: 
						return GPT_STATUS_ERROR_NOK;
				}
				break;
			}
			default: 
				return GPT_STATUS_ERROR_NOK;
		}
	}
	
	return GPT_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: starts the given gpt timer id in synchronous mode (polling)
******************************************************************************************/
enuGpt_Status_t GptStart_Sync(uint8_t ChannelId, uint32_t u32_Ticks)
{
	
	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_0):
		{
			if((u32_Ticks <= TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
				/* set ticks */
				TCNT0_R = TIMER_0_MAX_TICKS - u32_Ticks;
				
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
							
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);	
							
						TCNT0_R = 0x00;		
													
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																		
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);		
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);	
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																	
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);	
						
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
						
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;
																	
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;																															
				}
			}
			else if((u32_Ticks > TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
				uint32_t u32_OvfCounter = 0;
				float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_0_MAX_TICKS;
				uint32_t u32_OvfCounts = f32_TempValue;
				f32_TempValue -= u32_OvfCounts;
				uint32_t u32_CountRemanider = f32_TempValue * TIMER_0_MAX_TICKS;
				
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}				
					while(u32_OvfCounter < u32_OvfCounts)
					{
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						u32_OvfCounter++;
						SET_BIT(TIFR_R, TOV0_B);							
					}
					
					if(u32_CountRemanider != 0)
					{
						TCNT0_R = TIMER_0_MAX_TICKS - u32_CountRemanider;
						while(BIT_IS_CLEAR(TIFR_R, TOV0_B) == 1);
						SET_BIT(TIFR_R, TOV0_B);
					}
					
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						
						TCNT0_R = 0x00;				
			}
			else
			{
				return GPT_STATUS_ERROR_NOK;
			}
			
			break;
		}
/**************************************************************************************************/
case(TIMER_1):
{
	if((u32_Ticks <= TIMER_1_MAX_TICKS) && (u32_Ticks != 0))
	{
		/* set ticks */
		TCNT1_R = TIMER_1_MAX_TICKS - u32_Ticks;
		
		/* set to prescaler */
		switch(strGpt_Channels[ChannelId].u8_Prescaler)
		{
			case(PRESCALER_1):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
				SET_BIT(TIFR_R, TOV1_B);
				
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				TCNT1_R = 0x0000;
				
				break;
			}
			case(PRESCALER_8):
			{
				CLEAR_BIT(TCCR1B_R, CS10_B);
				SET_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
				SET_BIT(TIFR_R, TOV1_B);
				
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				TCNT1_R = 0x0000;
				
				break;
			}
			case(PRESCALER_64):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				SET_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
				SET_BIT(TIFR_R, TOV1_B);
				
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				TCNT1_R = 0x0000;
				
				break;
			}
			case(PRESCALER_256):
			{
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				SET_BIT(TCCR1B_R, CS12_B);
				
				while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
				SET_BIT(TIFR_R, TOV1_B);
				
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				TCNT1_R = 0x0000;
				
				break;
			}
			case(PRESCALER_1024):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				SET_BIT(TCCR1B_R, CS12_B);
				
				while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
				SET_BIT(TIFR_R, TOV1_B);
				
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				
				TCNT1_R = 0x0000;
				
				break;
			}
			default: return GPT_STATUS_ERROR_NOK;
		}
	}
	else if((u32_Ticks > TIMER_1_MAX_TICKS) && (u32_Ticks != 0))
	{
		uint32_t u32_OvfCounter = 0;
		float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_1_MAX_TICKS;
		uint32_t u32_OvfCounts = f32_TempValue;
		f32_TempValue -= u32_OvfCounts;
		uint32_t u32_CountRemanider = f32_TempValue * TIMER_1_MAX_TICKS;
		
		/* set to prescaler */
		switch(strGpt_Channels[ChannelId].u8_Prescaler)
		{
			case(PRESCALER_1):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				break;
			}
			case(PRESCALER_8):
			{
				CLEAR_BIT(TCCR1B_R, CS10_B);
				SET_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				break;
			}
			case(PRESCALER_64):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				SET_BIT(TCCR1B_R, CS11_B);
				CLEAR_BIT(TCCR1B_R, CS12_B);
				break;
			}
			case(PRESCALER_256):
			{
				CLEAR_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				SET_BIT(TCCR1B_R, CS12_B);
				break;
			}
			case(PRESCALER_1024):
			{
				SET_BIT(TCCR1B_R, CS10_B);
				CLEAR_BIT(TCCR1B_R, CS11_B);
				SET_BIT(TCCR1B_R, CS12_B);
				break;
			}
			default: return GPT_STATUS_ERROR_NOK;
		}
		while(u32_OvfCounter < u32_OvfCounts)
		{
			while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
			u32_OvfCounter++;
			SET_BIT(TIFR_R, TOV1_B);
		}
		
		if(u32_CountRemanider != 0)
		{
			TCNT1_R = TIMER_1_MAX_TICKS - u32_CountRemanider;
			while(BIT_IS_CLEAR(TIFR_R, TOV1_B) == 1);
			SET_BIT(TIFR_R, TOV1_B);
		}
		
		CLEAR_BIT(TCCR1B_R, CS10_B);
		CLEAR_BIT(TCCR1B_R, CS11_B);
		CLEAR_BIT(TCCR1B_R, CS12_B);
		
		TCNT1_R = 0x0000;
	}
	else
	{
		return GPT_STATUS_ERROR_NOK;
	}
	
	break;
}

/************************************************************************************************/		
		
		
		
		case(TIMER_2):
		{
			if((u32_Ticks <= TIMER_2_MAX_TICKS) && (u32_Ticks != 0))
			{
				/* set ticks */
				TCNT2_R = TIMER_2_MAX_TICKS - u32_Ticks;
			
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
					
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						TCNT2_R = 0x00;
					
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
					
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						TCNT2_R = 0x00;
					
						break;
					}
					case(PRESCALER_32):
					{
						SET_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
						
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						
						TCNT2_R = 0x00;
						
						break;
					}
					case(PRESCALER_64):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
					
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
					
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						TCNT2_R = 0x00;
					
						break;
					}
					case(PRESCALER_128):
					{
						SET_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
						
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
						
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						
						TCNT2_R = 0x00;
						
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
					
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
					
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						TCNT2_R = 0x00;
					
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
					
						while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
						SET_BIT(TIFR_R, TOV2_B);
					
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
					
						TCNT2_R = 0x00;
					
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
			}
			else if((u32_Ticks > TIMER_2_MAX_TICKS) && (u32_Ticks != 0))
			{
				uint32_t u32_OvfCounter = 0;
				float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_2_MAX_TICKS;
				uint32_t u32_OvfCounts = f32_TempValue;
				f32_TempValue -= u32_OvfCounts;
				uint32_t u32_CountRemanider = f32_TempValue * TIMER_2_MAX_TICKS;
			
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_32):
					{
						SET_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						CLEAR_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_64):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_128):
					{
						SET_BIT(TCCR2_R, CS20_B);
						CLEAR_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR2_R, CS20_B);
						SET_BIT(TCCR2_R, CS21_B);
						SET_BIT(TCCR2_R, CS22_B);
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
				while(u32_OvfCounter < u32_OvfCounts)
				{
					while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
					u32_OvfCounter++;
					SET_BIT(TIFR_R, TOV2_B);
				}
			
				if(u32_CountRemanider != 0)
				{
					TCNT2_R = TIMER_2_MAX_TICKS - u32_CountRemanider;
					while(BIT_IS_CLEAR(TIFR_R, TOV2_B) == 1);
					SET_BIT(TIFR_R, TOV2_B);
				}
			
				CLEAR_BIT(TCCR2_R, CS20_B);
				CLEAR_BIT(TCCR2_R, CS21_B);
				CLEAR_BIT(TCCR2_R, CS22_B);
			
				TCNT2_R = 0x00;
			}
			else
			{
				return GPT_STATUS_ERROR_NOK;
			}
		
			break;
		}
		default: return GPT_STATUS_ERROR_NOK;
		
	}
	return GPT_STATUS_ERROR_OK;
}

/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: starts the given gpt timer id in Asynchronous mode (interrupts)
******************************************************************************************/
enuGpt_Status_t GptStart_aSync(uint8_t ChannelId, uint32_t u32_Ticks, pfGpt_CallBack_t FunToBeCalledInISR)
{

	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_0):
		{
			if(Gpt_Status[TIMER_0] == GPT_STATUS_ALREADY_RUNNING)
			{
				return GPT_STATUS_ALREADY_RUNNING;
			}
			Gpt_Status[TIMER_0] = GPT_STATUS_ALREADY_RUNNING;
			T0ovfCallback = FunToBeCalledInISR;
			if((u32_Ticks <= TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
				/* set ticks */
				TCNT0_R = TIMER_0_MAX_TICKS - u32_Ticks;
						
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
								
						SET_BIT(TIMSK_R, TOIE0_B);
								
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
								
						SET_BIT(TIMSK_R, TOIE0_B);
								

								
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
								
						SET_BIT(TIMSK_R, TOIE0_B);
								
								
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
								
						SET_BIT(TIMSK_R, TOIE0_B);
						
								
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
								
						SET_BIT(TIMSK_R, TOIE0_B);
								
								
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
			}
			else if((u32_Ticks > TIMER_0_MAX_TICKS) && (u32_Ticks != 0))
			{
						
				float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_0_MAX_TICKS;
				gu32_T0_OvfCounts = f32_TempValue;
				f32_TempValue -= gu32_T0_OvfCounts;
				uint32_t u32_CountRemanider = f32_TempValue * TIMER_0_MAX_TICKS;
						
				TCNT0_R = u32_CountRemanider;
						
				/* set to prescaler */
				switch(strGpt_Channels[ChannelId].u8_Prescaler)
				{
					case(PRESCALER_1):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_8):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_64):
					{
						SET_BIT(TCCR0_R, CS00_B);
						SET_BIT(TCCR0_R, CS01_B);
						CLEAR_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_256):
					{
						CLEAR_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					case(PRESCALER_1024):
					{
						SET_BIT(TCCR0_R, CS00_B);
						CLEAR_BIT(TCCR0_R, CS01_B);
						SET_BIT(TCCR0_R, CS02_B);
						break;
					}
					default: return GPT_STATUS_ERROR_NOK;
				}
						
				SET_BIT(TIMSK_R, TOIE0_B);
							
				
			}
			else
			{
				return GPT_STATUS_ERROR_NOK;
			}
					
			break;
		}
	/****************************************************************/
		case(TIMER_2):
		{
			if(Gpt_Status[TIMER_2] == GPT_STATUS_ALREADY_RUNNING)
			{
				return GPT_STATUS_ALREADY_RUNNING;
			}
			Gpt_Status[TIMER_2] = GPT_STATUS_ALREADY_RUNNING;
			T2ovfCallback = FunToBeCalledInISR;
			if((u32_Ticks <= TIMER_2_MAX_TICKS) && (u32_Ticks != 0))
			{
				/* set ticks */
				TCNT2_R = TIMER_2_MAX_TICKS - u32_Ticks;
					
				/* set to prescaler */
					switch(strGpt_Channels[ChannelId].u8_Prescaler)
					{
						case(PRESCALER_1):
						{

							SET_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							break;
						}
						case(PRESCALER_8):
						{
							CLEAR_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							break;
						}
						case(PRESCALER_32):
						{
							SET_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							break;
						}
						case(PRESCALER_64):
						{

							CLEAR_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							
							

							break;
						}
						case(PRESCALER_128):
						{

							SET_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							
							

							break;
						}
						case(PRESCALER_256):
						{

							CLEAR_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							
							

							break;
						}
						case(PRESCALER_1024):
						{

							SET_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);
							
							SET_BIT(TIMSK_R, TOIE2_B);
							
							

							break;
						}
						default: return GPT_STATUS_ERROR_NOK;
					}
				}
				else if((u32_Ticks > TIMER_2_MAX_TICKS) && (u32_Ticks != 0))
				{
					
					float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_2_MAX_TICKS;
					gu32_T2_OvfCounts = f32_TempValue;
					f32_TempValue -= gu32_T2_OvfCounts;
					uint32_t u32_CountRemanider = f32_TempValue * TIMER_2_MAX_TICKS;
					
					TCNT2_R = u32_CountRemanider;
					
					/* set to prescaler */
					switch(strGpt_Channels[ChannelId].u8_Prescaler)
					{
						case(PRESCALER_1):
						{

							SET_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_8):
						{

							CLEAR_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_32):
						{

							SET_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							CLEAR_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_64):
						{

							CLEAR_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_128):
						{

							SET_BIT(TCCR2_R, CS20_B);
							CLEAR_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_256):
						{

							CLEAR_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);

							break;
						}
						case(PRESCALER_1024):
						{

							SET_BIT(TCCR2_R, CS20_B);
							SET_BIT(TCCR2_R, CS21_B);
							SET_BIT(TCCR2_R, CS22_B);

							break;
						}
						default: return GPT_STATUS_ERROR_NOK;
					}

					
					SET_BIT(TIMSK_R, TOIE2_B);
					
					

				}
				else
				{
					return GPT_STATUS_ERROR_NOK;
				}

					
				break;
			}
	/******************************************************************************/
	case(TIMER_1):
	{
		if(Gpt_Status[TIMER_1] == GPT_STATUS_ALREADY_RUNNING)
		{
			return GPT_STATUS_ALREADY_RUNNING;
		}
		Gpt_Status[TIMER_1] = GPT_STATUS_ALREADY_RUNNING;
		
		T1ovfCallback = FunToBeCalledInISR;
		if((u32_Ticks <= TIMER_1_MAX_TICKS) && (u32_Ticks != 0))
		{
			/* set ticks */
			TCNT1_R = TIMER_1_MAX_TICKS - u32_Ticks;
			
			/* set to prescaler */
			switch(strGpt_Channels[ChannelId].u8_Prescaler)
			{
				case(PRESCALER_1):
				{
					
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					
					SET_BIT(TIMSK_R, TOIE1_B);
					
					break;
				}
				case(PRESCALER_8):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					
					SET_BIT(TIMSK_R, TOIE1_B);
					

					
					break;
				}
				case(PRESCALER_64):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					
					SET_BIT(TIMSK_R, TOIE1_B);
					
					
					break;
				}
				case(PRESCALER_256):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
					
					SET_BIT(TIMSK_R, TOIE1_B);
					
					
					break;
				}
				case(PRESCALER_1024):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
					
					SET_BIT(TIMSK_R,TOIE1_B);
					
					
					break;
				}
				default: return GPT_STATUS_ERROR_NOK;
			}
		}
		else if((u32_Ticks > TIMER_1_MAX_TICKS) && (u32_Ticks != 0))
		{
			
			float32_t f32_TempValue = (float32_t)u32_Ticks/TIMER_1_MAX_TICKS;
			gu32_T1_OvfCounts = f32_TempValue;
			f32_TempValue -= gu32_T1_OvfCounts;
			uint32_t u32_CountRemanider = f32_TempValue * TIMER_1_MAX_TICKS;
			
			TCNT1_R = u32_CountRemanider;
			
			/* set to prescaler */
			switch(strGpt_Channels[ChannelId].u8_Prescaler)
			{
				case(PRESCALER_1):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					break;
				}
				case(PRESCALER_8):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					break;
				}
				case(PRESCALER_64):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
					break;
				}
				case(PRESCALER_256):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
					break;
				}
				case(PRESCALER_1024):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
					break;
				}
				default: return GPT_STATUS_ERROR_NOK;
			}
			
			SET_BIT(TIMSK_R, TOIE1_B);
			
			
		}
		else
		{
			return GPT_STATUS_ERROR_NOK;
		}
		
		break;
	}
	
	default: return GPT_STATUS_ERROR_NOK;
				
	}
	return GPT_STATUS_ERROR_OK;
	
}


/*******************************************************************************/
/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: stops a given timer
******************************************************************************************/
enuGpt_Status_t GptStop(uint8_t ChannelId)
{
	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_0):
		{
			CLEAR_BIT(TCCR0_R, CS00_B);
			CLEAR_BIT(TCCR0_R, CS01_B);
			CLEAR_BIT(TCCR0_R, CS02_B);
			TCNT0_R = 0x00;
			CLEAR_BIT(TIMSK_R, TOIE0_B);
			
			Gpt_Status[TIMER_0] = GPT_STATUS_NOT_RUNNING;
			
			break;
		}

case(TIMER_1):
{
	
	CLEAR_BIT(TCCR1B_R, CS10_B);
	CLEAR_BIT(TCCR1B_R, CS11_B);
	CLEAR_BIT(TCCR1B_R, CS12_B);
	TCNT1_R = 0x0000;
	CLEAR_BIT(TIMSK_R, TOIE1_B);
	
	Gpt_Status[TIMER_1] = GPT_STATUS_NOT_RUNNING;
	
	break;
}

		
		case(TIMER_2):
		{
			CLEAR_BIT(TCCR2_R, CS20_B);
			CLEAR_BIT(TCCR2_R, CS21_B);
			CLEAR_BIT(TCCR2_R, CS22_B);
			TCNT2_R = 0x00;
			CLEAR_BIT(TIMSK_R, TOIE2_B);
			
			Gpt_Status[TIMER_2] = GPT_STATUS_NOT_RUNNING;
			
			break;
		}
		default: return GPT_STATUS_ERROR_NOK;
	}
	
	return GPT_STATUS_ERROR_OK;
}
/**************************************************************/
/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: this function will stop the timer if the timer starts and exceeds the max numbers 
			   of counts allowed 
******************************************************************************************/
#if 0
void T1ExpireFunc(void)
{
	GptStop(TIMER_1);
}
#endif
/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: Starts a given timer
******************************************************************************************/
enuGpt_Status_t Gpt_StartTimer(uint8_t ChannelId)
{
	switch(strGpt_Channels[ChannelId].u8_TimerNumber)
	{
		case(TIMER_1):
		{
			//GptStart_aSync(TIMER_1,MAX_TICKS_T1,T1ExpireFunc);
			if(Gpt_Status[TIMER_1] == GPT_STATUS_ALREADY_RUNNING)
			{
				return GPT_STATUS_ALREADY_RUNNING;
			}
			Gpt_Status[TIMER_1] = GPT_STATUS_ALREADY_RUNNING;
			
			/*T1ovfCallback = FunToBeCalledInISR;*/
			
			/* set ticks */
			TCNT1_R = 0x00;
				
			/* set to prescaler */
			switch(strGpt_Channels[ChannelId].u8_Prescaler)
			{
				case(PRESCALER_1):
				{
						
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
						
					SET_BIT(TIMSK_R, TOIE1_B);
						
					break;
				}
				case(PRESCALER_8):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
						
					SET_BIT(TIMSK_R, TOIE1_B);
						

						
					break;
				}
				case(PRESCALER_64):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					SET_BIT(TCCR1B_R, CS11_B);
					CLEAR_BIT(TCCR1B_R, CS12_B);
						
					SET_BIT(TIMSK_R, TOIE1_B);
						
						
					break;
				}
				case(PRESCALER_256):
				{
					CLEAR_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
						
					SET_BIT(TIMSK_R, TOIE1_B);
						
						
					break;
				}
				case(PRESCALER_1024):
				{
					SET_BIT(TCCR1B_R, CS10_B);
					CLEAR_BIT(TCCR1B_R, CS11_B);
					SET_BIT(TCCR1B_R, CS12_B);
						
					SET_BIT(TIMSK_R,TOIE1_B);
						
						
					break;
				}
				default: return GPT_STATUS_ERROR_NOK;
			}
			
			break;
		}
		default: return GPT_STATUS_ERROR_NOK;
	}
	
	return GPT_STATUS_ERROR_OK;
}
/*****************************************************************************************
* Parameters (in): Channel Id
* Parameters (out): Error Status
* Return value: enuGpt_Status_t
* Description: Returns counter val after Start 
******************************************************************************************/
void Gpt_ReturnCounterVal(uint8_t ChannelId , uint32_t *u32_CounterVal)
{
	uint32_t u32_Temp;
	switch(ChannelId)
	{
		case TIMER_1 :
		{
			
				u32_Temp =((gu32_T1_OVF_TICKS*TIMER_1_MAX_TICKS)+TCNT1_R);
				*u32_CounterVal=u32_Temp;
				gu32_T1_OVF_TICKS=0;
				
			break;
		}
		
	}
	
}

/***********************************************************/
/* Interrupts */

/*****************************************************************************************
* Parameters (in): pointer to function to be called from ISR
* Parameters (out): None
* Return value: None
* Description: sets the function to be called by overflow timer  ISR
******************************************************************************************/
void setOvfCallback(pfGpt_CallBack_t FunToBeCalledInISR)
{
	T0ovfCallback = FunToBeCalledInISR;
	
}


/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for timer 0 overflow
******************************************************************************************/
ISR(TIMER0_OVF)
{
	if(gu32_T0_OvfCounts == 0)
	{
		 Gpt_Status[TIMER_0] = GPT_STATUS_NOT_RUNNING;
		 GptStop(TIMER_0);
		 T0ovfCallback();
	}
	else
	{
		gu32_T0_OvfCounts--;
	}
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for timer 1 overflow
******************************************************************************************/
ISR(TIMER1_OVF)
{
	gu32_T1_OVF_TICKS++;
	#if 0
	if(gu32_T1_OvfCounts == 0)
	{
		Gpt_Status[TIMER_1] = GPT_STATUS_NOT_RUNNING;
		GptStop(TIMER_1);
		/* Reset  gu32_T1_OVF_TICKS */
		gu32_T1_OVF_TICKS=0;
		T1ovfCallback();
		
	}
	else
	{
		gu32_T1_OvfCounts--;
	}
	#endif
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for timer 2 overflow
******************************************************************************************/
ISR(TIMER2_OVF)
{
	if(gu32_T2_OvfCounts == 0)
	{
		Gpt_Status[TIMER_2] = GPT_STATUS_NOT_RUNNING;
		GptStop(TIMER_2);
		T2ovfCallback();
	}
	else
	{
		gu32_T2_OvfCounts--;
	}
}


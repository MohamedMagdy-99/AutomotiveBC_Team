/*****************************************************************************
* Module: Animation Module
* File Name: Animation.c
* Description: Source file for Animation Module
* Author: Shady Mamdouh
* Date: 6/9/2021
******************************************************************************/
/******************************INCLUDES***************************************/
#include "Microcontroller\Platform_Types.h"
#include "Microcontroller\Std_types.h"
#include "Animation.h"
#include "ECUAL\LED Module\LED.h"
#include "ServiceL\FreeRTOS\Source\include\FreeRTOS.h"
#include "ServiceL\FreeRTOS\Source\include\task.h"

/*****************************************************************************/
/* Module initialization states */
#define ANI_INITIALIZED         1U
#define ANI_NOT_INITIALIZED     0U
uint8_t ANIInitState = ANI_NOT_INITIALIZED ;
/********************************************GLOBAL VAR***************************************************/
TickType_t CurrentSysTick =0;
TickType_t OldSysTick =0;
/* States */
#define IDLE_STATE       0U
#define LOW_STATE        1U
#define RISING_STATE     2U
#define HIGH_STATE       3U
#define FALLING_STATE    4U
#define SERVING          1U
#define NOT_SERVING      0U
#define STOPED           2U
/* structure of serving device */
typedef struct ServingDevice_t
{
	uint8_t ServingState;
	uint8_t DeviceId ;
	uint8_t DeviceSubId ;
	uint8_t CurrentSate ;
	uint8_t PreviousState;
	uint8_t Pattern ;
	uint32_t Counter ;
	uint16_t TotalNumOfSteps ;
	uint16_t CurrentStepNum ;
	uint16_t StepCounter ;
}ServingDevice_t;
/* Array of currently serving devices Data */
ServingDevice_t CurrentServBuffer[NUM_OF_DEVICES_USED][MAX_SERVING_NUM];

/* Counter per device for total number of currently serving devices */
uint8_t CurrentServCounter[NUM_OF_DEVICES_USED];
/********************************************************************************************************/
/*****************TEST********************/
#if 0
void GetSystick(uint32_t *ticks)
{
	*ticks =systickss;
}
#endif
/**********************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to initialize Animation Module
************************************************************************************************************************/
ANReturn_t ANI_Init(void)
{
	/*Check if initialized before */
	if (ANIInitState==ANI_INITIALIZED)
	{
		return ANI_InitializedBefore;
	}
	else
	{
		uint8_t u8_counter ;
		for (u8_counter=0;u8_counter<NUM_OF_DEVICES_USED;u8_counter++)
		{
			switch(ANIDeviceArr[u8_counter])
			{
				case LED_DEVICE_ID :
				{
					LED_Init();
					break;
				}
			}
		}
		return ANI_initialized ;
	}
	return ANI_E_NOK ;
}
/***********************************************************************************************************************
* Parameters (in): DeviceId,SubId,AnimationPattern
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Start animation for a device
************************************************************************************************************************/
ANReturn_t ANI_Start(uint8_t DeviceId , uint8_t SubId, uint8_t AnimationPattern)
{
	/****************************ERROR Handling*******************************/
	if (DeviceId >=NUM_OF_DEVICES_USED)
	{
		return InvlidDeviceId ;
	}
	/*************************************************************************/
	uint8_t u8_counter ;
	uint8_t ExistFlag =0;
	/* Check if the Device was serving before to overwrite and avoid creating a new serving */
	for (u8_counter=0;u8_counter<CurrentServCounter[DeviceId];u8_counter++)
	{
		if (CurrentServBuffer[DeviceId][u8_counter].ServingState==SERVING ||CurrentServBuffer[DeviceId][u8_counter].ServingState== STOPED)
		{
			/* Check on Device id and sub id*/
			if (CurrentServBuffer[DeviceId][u8_counter].DeviceId == DeviceId && CurrentServBuffer[DeviceId][u8_counter].DeviceSubId == SubId)
			{
				/* OverWrite the same device */
				CurrentServBuffer[DeviceId][u8_counter].ServingState =SERVING;
				CurrentServBuffer[DeviceId][u8_counter].Counter=0;
				CurrentServBuffer[DeviceId][u8_counter].DeviceId = DeviceId ;
				CurrentServBuffer[DeviceId][u8_counter].DeviceSubId= SubId;
				CurrentServBuffer[DeviceId][u8_counter].Pattern = AnimationPattern;
				CurrentServBuffer[DeviceId][u8_counter].CurrentSate=IDLE_STATE;
				
				CurrentServBuffer[DeviceId][u8_counter].TotalNumOfSteps = (ANIPatternsArr[AnimationPattern].RisingPeriod)/(ANIPatternsArr[AnimationPattern].IncreaseStepPeriod);
				ExistFlag =1;
				break;
			}
		}
		
	}
	/* means the data is recorded on a previous recorded data */
	if (ExistFlag==1)
	{
		return ANI_E_OK;
	}
	else
	{
		/* means the device is not served before and we will record a new data */
		/* check on max serving requests */
		if (CurrentServCounter[DeviceId]==MAX_SERVING_NUM)
		{
			return ANI_ExceedMaxServing ;
		}
		else
		{ /* Record new serving data */
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].ServingState =SERVING;
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].Counter=0;
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].DeviceId = DeviceId ;
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].DeviceSubId= SubId;
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].Pattern = AnimationPattern;
			CurrentServBuffer[DeviceId][ CurrentServCounter[DeviceId] ].CurrentSate=IDLE_STATE;
			CurrentServBuffer[DeviceId][u8_counter].TotalNumOfSteps = (ANIPatternsArr[AnimationPattern].RisingPeriod)/(ANIPatternsArr[AnimationPattern].IncreaseStepPeriod);
			/* increment counter */
			CurrentServCounter[DeviceId]++;
			return ANI_E_OK;
		}
	}
	return ANI_E_OK;
}
/*************************************************************************************************************************/
/***********************************************************************************************************************
* Parameters (in): DeviceId,SubId
* Parameters (out): None
* Return value: LEDReturn_t
* Description: This function used to Stop animation for a device
************************************************************************************************************************/
ANReturn_t ANI_Stop(uint8_t DeviceId , uint8_t SubId)
{
	/****************************ERROR Handling*******************************/
	if (DeviceId >=NUM_OF_DEVICES_USED)
	{
		return InvlidDeviceId ;
	}
	/*************************************************************************/
	uint8_t u8_counter ;
	for (u8_counter=0;u8_counter<CurrentServCounter[DeviceId];u8_counter++)
	{
		if (CurrentServBuffer[DeviceId][u8_counter].ServingState==SERVING)
		{
			/* Check on Device id and sub id*/
			if (CurrentServBuffer[DeviceId][u8_counter].DeviceId == DeviceId && CurrentServBuffer[DeviceId][u8_counter].DeviceSubId == SubId)
			{
				/*Clear serving state */
				CurrentServBuffer[DeviceId][u8_counter].ServingState = STOPED;
				/* Disable pin */
				LED_OFF(SubId);
				break;
				
			}
		}
	}
	return ANI_E_OK;
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function used to increment the Module counters by the new sysTick
************************************************************************************************************************/
void IncrementCounters(void)
{
	uint8_t DeviceConter ;
	uint8_t CurrentCounter ;
	
	CurrentCounter = xTaskGetTickCount();
	
	//GetSystick(&CurrentSysTick);
	
	/* Means that Systick counter over flow */
	if (OldSysTick > CurrentSysTick)
	{
		
		for(DeviceConter=0;DeviceConter<NUM_OF_DEVICES_USED;DeviceConter++)
		{
			for(CurrentCounter=0; CurrentCounter<CurrentServCounter[DeviceConter] ; CurrentCounter++)
			{
				CurrentServBuffer[DeviceConter][CurrentCounter].Counter=0;
				CurrentServBuffer[DeviceConter][CurrentCounter].CurrentSate=IDLE_STATE;
				
			}
		}
		OldSysTick =0;
	}
	else
	{
		TickType_t Temp = CurrentSysTick - OldSysTick;
		/* Increment serving devices counters */
		
		for(DeviceConter=0;DeviceConter<NUM_OF_DEVICES_USED;DeviceConter++)
		{
			for(CurrentCounter=0; CurrentCounter<CurrentServCounter[DeviceConter] ; CurrentCounter++)
			{
				CurrentServBuffer[DeviceConter][CurrentCounter].Counter +=Temp;
				CurrentServBuffer[DeviceConter][CurrentCounter].StepCounter +=Temp;
				
				
			}
		}
		
		OldSysTick = CurrentSysTick;
		
	}
}
/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function used to Get New Device state according to counters calculations
************************************************************************************************************************/
void ANI_GetState(void)
{
	uint8_t DeviceCounter ;
	uint8_t CurrentCounter ;
	uint8_t PatternId ;
	uint16_t LowPeriod;
	uint16_t RisingPeriod;
	uint16_t HighPeriod;
	uint16_t StepPeriod;
	for(DeviceCounter=0;DeviceCounter<NUM_OF_DEVICES_USED;DeviceCounter++)
	{
		for(CurrentCounter=0; CurrentCounter<CurrentServCounter[DeviceCounter] ; CurrentCounter++)
		{
			if (CurrentServBuffer[DeviceCounter][CurrentCounter].ServingState==SERVING)
			{
				PatternId = CurrentServBuffer[DeviceCounter][CurrentCounter].Pattern;
				LowPeriod = ANIPatternsArr[PatternId].LOWPeriod;
				RisingPeriod = ANIPatternsArr[PatternId].RisingPeriod;
				HighPeriod   = ANIPatternsArr[PatternId].HighPeriod;
				StepPeriod    = ANIPatternsArr[PatternId].IncreaseStepPeriod;
				
				if (CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate == IDLE_STATE)
				{
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate = LOW_STATE;
				}
				
				/* Check if exceeds Total period */
				if(CurrentServBuffer[DeviceCounter][CurrentCounter].Counter >= ANIPatternsArr[PatternId].ToltalPeriod )
				{
					/* Update State to Idle */
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate=LOW_STATE;
					/* Reset The counter to restart the Pattern */
					CurrentServBuffer[DeviceCounter][CurrentCounter].Counter =0;
					/* to not enter the coming conditions */
					/* Reset rising and falling step counters because its expected that Rising is coming after high */
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum=0;
					CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter =0;
					continue;
					
				}
				/* Check if Falling period is now*/
				if (CurrentServBuffer[DeviceCounter][CurrentCounter].Counter >=(LowPeriod+RisingPeriod+HighPeriod))
				{
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate = FALLING_STATE;
					/* Get Current step state */
					if (CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter >= StepPeriod)
					{
						CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=IDLE_STATE;
						CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum++;
						CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter =0;
					}
					
					/* to not enter the coming conditions */
					continue;
				}
				/* Check if High period is now*/
				if (CurrentServBuffer[DeviceCounter][CurrentCounter].Counter >=(LowPeriod+RisingPeriod))
				{
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate = HIGH_STATE;
					/* Reset rising and falling step counter because its expected that falling is coming after high */
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum=0;
					CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter =0;
					/* to not enter the coming conditions */
					continue;
				}
				/* Check if Rising period is now*/
				if (CurrentServBuffer[DeviceCounter][CurrentCounter].Counter >=(LowPeriod))
				{
					CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate = RISING_STATE;
					if (CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter >= StepPeriod)
					{
						CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=IDLE_STATE;
						CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum++;
						CurrentServBuffer[DeviceCounter][CurrentCounter].StepCounter =0;
					}
					/* to not enter the coming conditions */
					continue;
				}
			}
			
			
			
		}
	}
}

/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function used to Take actions acoording to Device State
************************************************************************************************************************/
uint16_t DutyCycle ;
void ANI_UpdateState(void)
{
	uint8_t DeviceCounter ;
	uint8_t CurrentCounter ;
	for(DeviceCounter=0;DeviceCounter<NUM_OF_DEVICES_USED;DeviceCounter++)
	{
		for(CurrentCounter=0; CurrentCounter<CurrentServCounter[DeviceCounter] ; CurrentCounter++)
		{
			switch(ANIDeviceArr[DeviceCounter])
			{
				case LED_DEVICE_ID :
				{
					uint8_t DeviceSubId = CurrentServBuffer[DeviceCounter][CurrentCounter].DeviceSubId;
					switch(CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentSate)
					{
						case LOW_STATE :
						{
							if (CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState==LOW_STATE)
							{
								break;
							}
							else
							{
								LED_OFF(DeviceSubId);
								CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=LOW_STATE;
								break;
								
							}
							
						}
						case  RISING_STATE :
						{
							if (CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState==RISING_STATE)
							{
								
								break;
							}
							else
							{
								uint16_t CurrStepNum = CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum;
								uint16_t TotalSteps  = CurrentServBuffer[DeviceCounter][CurrentCounter].TotalNumOfSteps;
								DutyCycle = ((float32_t)CurrStepNum / TotalSteps)*100;
								if (DutyCycle >100)
								{
									DutyCycle =100;
								}
								LED_OFF(DeviceSubId);
								LED_AnimationStrat(DeviceSubId,150,DutyCycle);
								CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=RISING_STATE;
								break;
							}
							
						}
						case HIGH_STATE :
						{
							if (CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState==HIGH_STATE)
							{
								
								break;
							}
							else
							{
								
								LED_OFF(DeviceSubId);
								LED_AnimationStrat(DeviceSubId,150,100);
								CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=HIGH_STATE;
								//LED_ON(DeviceSubId);
								break;
							}
							
						}
						case FALLING_STATE :
						{
							if (CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState==FALLING_STATE)
							{
								
								break;
							}
							else
							{
								uint16_t CurrStepNum = CurrentServBuffer[DeviceCounter][CurrentCounter].CurrentStepNum;
								uint16_t TotalSteps  = CurrentServBuffer[DeviceCounter][CurrentCounter].TotalNumOfSteps;
								DutyCycle =    ((float32_t)CurrStepNum / TotalSteps)*100;
								if (DutyCycle >100)
								{
									DutyCycle =100;
								}
								LED_OFF(DeviceSubId);
								DutyCycle = 100 - DutyCycle ;
								LED_AnimationStrat(DeviceSubId,150,DutyCycle);
								CurrentServBuffer[DeviceCounter][CurrentCounter].PreviousState=FALLING_STATE;
								break;
							}
							
						}
						
					}
					
					break;
				}
				
				
			}
			
			
		}
		
	}
}

/***********************************************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function Is the main dispatcher of the Animation module
************************************************************************************************************************/
void ANI_MainFunction(void* pvParam)
{
	while(1)
	{
		/* Increment counters */
		IncrementCounters();
		/* Get devices state */
		ANI_GetState();
		/* Update Devices States */
		ANI_UpdateState();
		
		vTaskDelay(10);
	}
}



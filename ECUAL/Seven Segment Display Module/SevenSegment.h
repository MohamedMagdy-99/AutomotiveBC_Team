/*
 * SevenSegment.h
 *
 * Created: 08-Sep-21 6:40:13 PM
 *  Author: Mohamed Magdy
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Dio.h"
#include "SevenSegment_Cfg.h"
#include "Delay.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- PRIMITIVE TYPES -*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- ENUMS -*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- STRUCTS -*-*-*-*-*-*/

typedef struct
{
	uint8_t u8_segA_DioId;
	uint8_t u8_segB_DioId;
	uint8_t u8_segC_DioId;
	uint8_t u8_segD_DioId;
	uint8_t u8_segEN_DioId;
	
}str7Seg_Config_t;


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*-*- FUNCTIONS PROTOTYPES -*-*-*-*-*-*/
/* Initialization function */
Std_ReturnType SS_Init();
/* send to single */
Std_ReturnType SS_sendNumber_One7Seg(uint8_t segId, uint8_t u8_num);
/* sent to double */
Std_ReturnType SS_sendNumber_Two7Seg(uint8_t firstSegId, uint8_t secondSegId, uint8_t u8_num, uint8_t u8_swapDelay_ms);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by 7seg and other modules */
extern str7Seg_Config_t str7Seg_config[NUM_7SEG_USED];



#endif /* SEVENSEGMENT_H_ */
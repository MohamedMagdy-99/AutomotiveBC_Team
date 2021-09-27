/*
 * SevenSegment_Cfg.c
 *
 * Created: 08-Sep-21 6:41:13 PM
 *  Author: Mohamed Magdy
 */ 



#include "SevenSegment.h"

str7Seg_Config_t str7Seg_config[NUM_7SEG_USED]=
{	/* seg_A dio Id */		/* seg_B dio Id */	/* seg_C dio Id */		/* seg_D dio Id */		/* seg EN Id */
	{DIO_SEG_A_CHANNEL_ID, DIO_SEG_B_CHANNEL_ID, DIO_SEG_C_CHANNEL_ID, DIO_SEG_D_CHANNEL_ID, DIO_SEG_1_EN_CHANNEL_ID},
	{DIO_SEG_A_CHANNEL_ID, DIO_SEG_B_CHANNEL_ID, DIO_SEG_C_CHANNEL_ID, DIO_SEG_D_CHANNEL_ID, DIO_SEG_2_EN_CHANNEL_ID}	
};
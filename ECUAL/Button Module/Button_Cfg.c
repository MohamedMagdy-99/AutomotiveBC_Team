/*****************************************************************************
* Module: Button Module
* File Name: Button_Cfg.c
* Description: Source file for Button Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Button.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* here you adjust the buttons configurations */
strButton_Config_t strButton_Config[BUTTONS_USED]=
{
	/*Button Dio Pin Id*/	/* Pull up or down */
	{ BUTTON_1_DIO_ID	, PULL_UP },
	{ BUTTON_2_DIO_ID	, PULL_UP },
	{ BUTTON_3_DIO_ID	, PULL_UP }
			
};

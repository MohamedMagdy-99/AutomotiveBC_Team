/*
 * ObstacleAvoid_Car.c
 *
 * Created: 8/9/2021 12:31:18 PM
 * Author : Ahmed Nabil
 */ 


#include "App Component/App.h"

int main(void)
{

	App_start();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}























// #include "APPL/Robot Module/Robot.h"
// #include "MCAL/Delay Module/Delay.h"
// #include "ECUAL/Lcd Module/Lcd.h"
// #include "APPL/App Component/App.h"
// 
// int main(void)
// {
// 	Lcd_init();
// 	EnableGlobalInterrupts();
// 	//Lcd_sendCharacter('B');
// 	
// 	
// 	
// 	
// 	
// 	GptInit();
//  	
// 	DIO_PORTB_DIR |= 1<<0;
// 	GptStart_aSync(TIMER_CHANNEL_0_ID, 125000, ISRCallback);
// 	
// 	
// 	
// 	DIO_PORTB_DIR |= 1<<0;
// 	if(RobotApp_start() == APP_STATUS_ERROR_NOK)
// 	{
// 	}
//     /* Replace with your application code */
//     while (1) 
//     {
// 	    //Lcd_asyncSendString((uint8_t*)"ABC");
// 		Lcd_sendString((uint8_t*)"ABC");
//     }
// }


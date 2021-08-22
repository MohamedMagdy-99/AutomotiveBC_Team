/*
 * Motor_Cfg.c
 *
 * Created: 7/15/2021 11:12:52 PM
 *  Author: Ahmed Nabil
 */ 

#include "Motor.h"

/*
 * Array of Structures, each holds the SWPWM Channel, The two Direction pins, 
 * and the Operating frequency connected with the Motor
 */
const Motor_Config_t MotorsConfigurations_str[MOTORS_USED_NUM] =
{
	{MOTOR_R_SWPWM_CHANNEL,       MOTOR_R_DIO1_CHANNEL,       MOTOR_R_DIO2_CHANNEL,       MOTOR_R_OPERATING_FREQ},
	{MOTOR_L_SWPWM_CHANNEL,       MOTOR_L_DIO1_CHANNEL,       MOTOR_L_DIO2_CHANNEL,       MOTOR_L_OPERATING_FREQ}
};
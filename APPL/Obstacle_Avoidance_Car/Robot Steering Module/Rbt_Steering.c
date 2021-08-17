/*
 * Rbt_Steering.c
 *
 * Created: 9/8/2021 11:15:40 AM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Rbt_Steering.h"
#include "..\..\..\Microcontroller\Delay Module\Delay.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the state of the Robot
 */
#define ROBOT_STOPPED				0U
#define ROBOT_RUNNING				1U
#define DATA_NOT_CHANGED			0U
#define DATA_CHANGED				1U

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
/* Indicator of the data changed */
uint8_t DataChange_Flag = DATA_NOT_CHANGED;

/* Holds the current state of the Robot */
RobotState_t RobotState_gau8 = ROBOT_STOPPED;

/* Holds the status of the Robot Module */
uint8_t RobotModuleStatus_gu8 = ROBOT_STATUS_UNINIT;

static Rbt_DataInput_t Robot_Data_Input = {ROBOT_DIR_NEUTRAL, 0};
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*--*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RbtSteering_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Robot_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Initialize the Robot module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to initialize the Robot module */
Std_ReturnType RbtSteering_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Robot module is already initialized */
	if(RobotModuleStatus_gu8 == ROBOT_STATUS_INIT)
	{
		return E_OK;
	}else{/*Nothing to here*/}
		
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/
/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Initialize the ROBOT Module */
	if(Motor_init() != MOTOR_STATUS_ERROR_OK)
	{
		return E_NOT_OK;
	}
	
	/* Change the state of the module to initialized */
	RobotModuleStatus_gu8 = ROBOT_STATUS_INIT;
	return E_OK;
}



/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RbtSteering_mainFunction
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Robot_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Main Function || Dispatcher of the Robot Steering Module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType RbtSteering_mainFunction(void)
{
	if (DataChange_Flag == DATA_CHANGED)
	{
		DataChange_Flag = DATA_NOT_CHANGED;
		if((Robot_Data_Input.RbtSpeed == 0) || (Robot_Data_Input.RbtDirection >= ROBOT_DIR_NEUTRAL))
		{
			RbtSteering_stop();
		}else
		{
			RbtSteering_move(Robot_Data_Input.RbtDirection, Robot_Data_Input.RbtSpeed);
		}
	}else
	{
		
	}
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RbtSteering_Dir_Spd_Setter
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8_speed - Speed of the robot in %
*				   u8_direction - Direction of the robot (Forward - Backward - Left - Right)
* Parameters (inout): None
* Parameters (out): None
* Return value: Robot_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Set the data of the Robot in the global shared variable.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType RbtSteering_Dir_Spd_Setter(RobotDir_t u8_direction, RobotSpeed_t u8_speed)
{
	DataChange_Flag = DATA_CHANGED;
	Robot_Data_Input.RbtDirection = u8_direction;
	Robot_Data_Input.RbtSpeed = u8_speed;
	
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RbtSteering_move
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8_speed - Speed of the robot in %
*				   u8_direction - Direction of the robot (Forward - Backward - Left - Right)
* Parameters (inout): None
* Parameters (out): None
* Return value: Robot_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Move the Robot in the given direction with a given speed in %.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to move the Robot forward with given speed in % */
Std_ReturnType RbtSteering_move(RobotDir_t u8_direction, RobotSpeed_t u8_speed)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the ROBOT module is not initialized */
	if(RobotModuleStatus_gu8 != ROBOT_STATUS_INIT)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
		
	/* Check if the speed is out of range */
	if (100 < u8_speed)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
		
	/* Check if the Robot direction is invalid */
	if (ROBOT_DIR_INVALID <= u8_direction)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
	
	/* Check if the Robot is already running */
	if(RobotState_gau8 == ROBOT_RUNNING)		
	{
		/* Stop the Robot to Run again with the new speed and direction */
		RbtSteering_stop();
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	if(u8_speed == 0) 
	{
		RbtSteering_stop();
		return E_OK;
	}
	switch (u8_direction)
	{	/* If the give Direction is Forward */
		case ROBOT_DIR_FRWRD:
			/* Run Left Motor in Forward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_leftMotorID, u8_speed, MOTOR_FRWRD))
				return ROBOT_STATUS_ERROR_NOK;
			/* Run Right Motor in Forward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_rightMotorID, u8_speed, MOTOR_FRWRD))
				return ROBOT_STATUS_ERROR_NOK;
			break;
		/* If the give Direction is Forward */
		case ROBOT_DIR_BKWRD:
			/* Run Left Motor in Backward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_leftMotorID, u8_speed, MOTOR_BKWRD))
				return ROBOT_STATUS_ERROR_NOK;
			/* Run Right Motor in Backward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_rightMotorID, u8_speed, MOTOR_BKWRD))
				return ROBOT_STATUS_ERROR_NOK;
			break;
		/* If the give Direction is Forward */
		case ROBOT_DIR_LEFT:
			/* Run Left Motor in Backward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_leftMotorID, u8_speed, MOTOR_BKWRD))
				return ROBOT_STATUS_ERROR_NOK;
			/* Run Right Motor in Forward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_rightMotorID, u8_speed, MOTOR_FRWRD))
				return ROBOT_STATUS_ERROR_NOK;
			Delay_ms(STEERING_LEFT_DELAY);
			break;
		/* If the give Direction is Forward */
		case ROBOT_DIR_RIGHT:
			/* Run Left Motor in Forward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_leftMotorID, u8_speed, MOTOR_FRWRD))
				return ROBOT_STATUS_ERROR_NOK;
			/* Run Right Motor in Backward Direction */
			if( MOTOR_STATUS_ERROR_OK != Motor_run(RbtSteering_Configuratons.Rbt_rightMotorID, u8_speed, MOTOR_BKWRD))
				return ROBOT_STATUS_ERROR_NOK;
			Delay_ms(STEERING_RIGHT_DELAY);
			break;
		default:
			return ROBOT_STATUS_ERROR_NOK;
	}
	
	/* Change the state of the Motor to Running */
	RobotState_gau8 = ROBOT_RUNNING;
	
	return E_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: RbtSteering_stop
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Robot_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Stop the Robot.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/* Function to stop robot */
Std_ReturnType RbtSteering_stop()
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the motor index is invalid */
	if (ROBOT_STOPPED == RobotModuleStatus_gu8)
	{
		return E_OK;
	}else{/*Nothing to here*/}
				
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Stop Left and Right Motors */
	Motor_stop(RbtSteering_Configuratons.Rbt_leftMotorID);
	Motor_stop(RbtSteering_Configuratons.Rbt_rightMotorID);
	/* Change the state of the Robot to Stopped */
	RobotState_gau8 = ROBOT_STOPPED;
	return E_OK;
}
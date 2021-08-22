/*
 * Rbt_Steering.h
 *
 * Created: 9/8/2021 11:16:10 AM
 *  Author: Ahmed Nabil
 */ 


#ifndef RBT_STEERING_H_
#define RBT_STEERING_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../../ECUAL/Motor Module/Motor.h"
#include "Rbt_Steering_Cfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*
 * MACROs to determine the directions used by the Robot_move API
 */
#define ROBOT_DIR_FRWRD				0U
#define ROBOT_DIR_BKWRD				1U
#define ROBOT_DIR_LEFT				2U
#define ROBOT_DIR_RIGHT				3U
#define ROBOT_DIR_NEUTRAL			4U
#define ROBOT_DIR_INVALID			5U


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Robot state
 */
typedef uint8_t RobotState_t;

/*
 * Data Type for Robot direction
 */
typedef uint8_t RobotDir_t;

/*
 * Data Type for Robot Speed
 */
typedef uint8_t RobotSpeed_t;

typedef struct
{
	RobotDir_t	Direction;
	RobotSpeed_t Speed;
}RbtSteering_Data;

/*
 * Data Type for Module's Input
 */
typedef struct
{
	RobotDir_t	RbtDirection;
	RobotSpeed_t  RbtSpeed;
}Rbt_DataInput_t;

/*
 * Data Type for Robot return status
 */
typedef enum
{
	ROBOT_STATUS_ERROR_NOK,
	ROBOT_STATUS_ERROR_OK,
	ROBOT_STATUS_ERROR_ID_INVALID,
	ROBOT_STATUS_ERROR_SPD_INVALID,
	ROBOT_STATUS_ERROR_DIR_INVALID,
	ROBOT_STATUS_ERROR_RUNNING,
	ROBOT_STATUS_ERROR_STOPPED,
	ROBOT_STATUS_INIT,
	ROBOT_STATUS_UNINIT
}Robot_Status_t;

/*
 * Data Type for Robot configurations
 */
typedef struct  
{
	MotorChannel_t Rbt_leftMotorID; //Variable holds the left motor index from the MOTOR Module
	MotorChannel_t Rbt_rightMotorID; //Variable holds the right motor index from the MOTOR Module
}RbtSteering_Config_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the Robot module */
Robot_Status_t RbtSteering_init(void);

/* Function to move the Robot a given direction with given speed in % */
Robot_Status_t RbtSteering_move(RobotDir_t u8_direction, RobotSpeed_t u8_speed);

/* Function to stop Robot */
Robot_Status_t RbtSteering_stop(void);

/* Periodic Function || Dispatcher of the Robot Steering Module */
Robot_Status_t RbtSteering_mainFunction(void);

/* Robot Steering Module Setter */
Robot_Status_t RbtSteering_setData(RobotDir_t u8_direction, RobotSpeed_t u8_speed);

/* Robot Steering Module Getter */
Robot_Status_t RbtSteering_getData(RobotDir_t *pu8_direction, RobotSpeed_t *pu8_speed);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const RbtSteering_Config_t RbtSteering_Configuratons;

#endif /* RBT_STEERING_H_ */
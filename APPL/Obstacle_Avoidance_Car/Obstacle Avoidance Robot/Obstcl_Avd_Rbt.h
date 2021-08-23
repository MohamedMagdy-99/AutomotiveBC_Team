/*
 * App.h
 *
 * Created: 7/16/2021 1:22:44 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef OBSTCL_AVD_RBT_H_
#define OBSTCL_AVD_RBT_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../Robot Steering Module/Rbt_Steering.h"
#include "../Sensing Module/Sensing.h"
#include "../Display Module/Display.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define OBSTCLE_AVD_MOD_UNINITIALIZED			0U
#define OBSTCLE_AVD_MOD_INITIALIZED				1U
#define OB_AVD_DISTANCE_UNDER_THRSHOLD			2U
#define OB_AVD_DISTANCE_EQUAL_THRSHOLD			3U
#define OB_AVD_DISTANCE_OVER_THRSHOLD			4U
#define OB_AVD_HIGH_THRESHOLD					55U
#define OB_AVD_LOW_THRESHOLD					45U
#define OB_RBT_FRWRD_SPEED						20U
#define OB_RBT_BKWRD_SPEED						20U
#define OB_RBT_RIGHT_SPEED						20U
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
* Data Type for App return status
*/
typedef uint8_t ModuleState_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the Obstacle Avoidance Module */
Std_ReturnType ObstacleAvoidance_init(void);

/* Periodic Function of the Obstacle Avoidance Module */
Std_ReturnType ObstacleAvoidance_mainFunction(void);

#endif /* OBSTCL_AVD_RBT_H_ */
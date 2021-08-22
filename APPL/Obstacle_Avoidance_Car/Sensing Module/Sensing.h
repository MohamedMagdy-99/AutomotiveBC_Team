/*
 * Sensing.h
 *
 * Created: 13/8/2021 11:16:10 AM
 *  Author: Ahmed Nabil
 */ 


#ifndef SENSING_H_
#define SENSING_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../../../ECUAL/Ultrasonic Module/Ultrasonic.h"
#include "Sensing_Cfg.h"


/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Distance Value
 */
typedef uint16_t Sensing_Distance_t;

/*
 * Data Type for Sensing module state
 */
typedef uint8_t Sensing_State_t;

/*
 * Data Type for Sensing Module configurations
 */
typedef uint8_t Sensor_list_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the module */
Std_ReturnType Sensing_init(void);

/* Function used to get reading of a sensor with the given ID */
Std_ReturnType Sensing_getReading(uint8_t SensorID_u8, uint16_t *Sensor_Value);

/*  Sensing module main function */
Std_ReturnType Sensing_mainFunction(void);
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const Sensor_list_t Sensors[SENSORS_USED_NUM];

#endif /* SENSING_H_ */
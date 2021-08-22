/*
 * Motor_LCfg.h
 *
 * Created: 7/15/2021 11:13:13 PM
 *  Author: Ahmed Nabil
 */ 

#ifndef MOTOR_LCFG_H_
#define MOTOR_LCFG_H_

/* Number of Motors Used */
#define MOTORS_USED_NUM				2U //LCfg.h

/* Motor Right Configurations */
#define MOTOR_R_OPERATING_FREQ		100U				/* Opearting Frequency */
#define MOTOR_R_SWPWM_CHANNEL		SWPWM_CHANNEL_0_ID  /* 1st Direction Pin for the Motor */
#define MOTOR_R_DIO1_CHANNEL		DIO_IN1_CHANNEL_ID	/* 2nd Direction Pin for the Motor */
#define MOTOR_R_DIO2_CHANNEL		DIO_IN2_CHANNEL_ID	/* SWPWMM Used for the Motor */

/* Motor Left Configurations */
#define MOTOR_L_OPERATING_FREQ		100U				/* Opearting Frequency */
#define MOTOR_L_DIO1_CHANNEL		DIO_IN3_CHANNEL_ID  /* 1st Direction Pin for the Motor */
#define MOTOR_L_DIO2_CHANNEL		DIO_IN4_CHANNEL_ID	/* 2nd Direction Pin for the Motor */
#define MOTOR_L_SWPWM_CHANNEL		SWPWM_CHANNEL_0_ID	/* SWPWMM Used for the Motor */

/* ID for the Motors Used */
#define MOTOR_RIGHT_ID				0U
#define MOTOR_LEFT_ID				1U

#endif /* MOTOR_LCFG_H_ */
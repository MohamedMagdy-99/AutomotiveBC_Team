/*
 * App.h
 *
 * Created: 7/16/2021 1:22:44 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef APP_H_
#define APP_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Obstcl_Avd_Rbt.h"
#include "ServiceL/OS Module/OS.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for App return status
 */
typedef enum
{
	APP_STATUS_ERROR_NOK,
	APP_STATUS_ERROR_OK,
	APP_STATUS_INITIALIZED,
	APP_STATUS_UNINITIALIZED
}enuApp_Status_t;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to Start the application */
Std_ReturnType App_start(void);

/* Function to initialize the Application */
Std_ReturnType App_init(void);

/* Function to update the application */
Std_ReturnType App_update(void);



#endif /* APP_H_ */
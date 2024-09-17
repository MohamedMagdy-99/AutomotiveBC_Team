/*
 * Bcm_LCfg.h
 *
 * Created: 8/25/2021 7:15:26 PM
 *  Author: Mohamed Magdy & Ahmed Nabil
 */ 


#ifndef BCM_LCFG_H_
#define BCM_LCFG_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES (Com. channels used) *-*-*-*-*-*/
#include "MCAL/Uart Module/Uart.h"


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/* user set the number of channels used in the project */

#define BCM_RX_COM_DEVICES_USED					(1U)

/* Comm Channel Id according to cfg struct array order to be used in function calls */
#define COM_CHANNEL_0_ID				    (0U)

/* com. channels id to be filled in cfg struct */
#define C_CHANNEL_1_ID						UART_CHANNEL_0		 // supposed to be UART_CHANNEL_1 if supported by avr


#define BCM_TX_COM_DEVICES_USED				1U

#define BCM_MAX_TX_REQUESTS					40U

#define BCM_MAX_COM_DEVICES					2U

#define BCM_TX_CHANNEL_0_ID					0U

#endif /* BCM_LCFG_H_ */
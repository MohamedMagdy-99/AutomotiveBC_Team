/*
 * Bcm_LCfg.c
 *
 * Created: 8/25/2021 7:14:55 PM
 *  Author: Ahmed Nabil
 */ 


#include "Bcm.h"


/* here you adjust the com. channels transmit configurations */
const BCM_TxConfig_t BCM_TxConfigurations[BCM_TX_COM_DEVICES_USED] = 
{
	 {UART_CHANNEL_0, USART_TXC_IRQ, Uart_writeByte, Uart_EnableNotification_TXC, Uart_DisableNotification_TXC}
};


/* here you adjust the com. channels receive configurations */
strRxComChannels_Config_t strRxComChannels_Config[BCM_RX_COM_DEVICES_USED] =
{
	/* com channel id */  /* BCM channel read fun */
	{C_CHANNEL_1_ID,  USART_RXC_IRQ, Uart_readByte, Uart_EnableNotification_RXC, Uart_DisableNotification_RXC}
};
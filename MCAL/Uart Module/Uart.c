/*
 * Uart.c
 *
 * Created: 7/18/2021 2:53:22 PM
 *  Author: Ahmed Nabil
 */ 

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Uart.h"
#include "Microcontroller/Atmega32 Registers/Uart_Regs.h"
#include "Uart_Cfg.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- GLOBAL STATIC VARIABLES *-*-*-*-*-*/
static uint8_t u8_Uart_Status = UART_NOT_INITIALIZED;
static strUart_Config_t strUart_Config =
{
	UART_ENABLE,
	UART_SIZE,
	UART_DBL_SPEED,
	UART_PARITY,
	UART_STOP_BITS,
};

/*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- FUNCTIONS IMPLEMENTATION -*-*-*-*-*-*/
enuUart_Status_t Uart_setBaudRate(uint32_t newBaudRate)
{
	/*- Set Baudrate Value in Registers -*/
	if(strUart_Config.u8_DoubleSpeedEnable == UART_U2X_ENABLE)
	{/*- If double speed enabled -*/
		UBRRH_R = (uint8_t)(BAUD_RATE_U2X(newBaudRate)>>8);
		UBRRL_R = (uint8_t)BAUD_RATE_U2X(newBaudRate);
		UCSRA_R = 1<<UART_UCSRA_U2X;
	}else
	{/*- If double speed disabled -*/
		UBRRH_R = (uint8_t)(BAUD_RATE(newBaudRate)>>8);
		UBRRL_R = (uint8_t)BAUD_RATE(newBaudRate);
		UCSRA_R &= ~(1<<UART_UCSRA_U2X);
	}
	return UART_STATUS_ERROR_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Initialize the Uart module.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_init(void)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is already initialized */
	if (UART_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_ALREADY_INIT;
	}else{/*Nothing to here*/}
	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Set Baudrate Value in Registers -*/
	if(strUart_Config.u8_DoubleSpeedEnable == UART_U2X_ENABLE)
	{/*- If double speed enabled -*/
		UBRRH_R = (uint8_t)(BAUD_RATE_U2X(USART_BAUDRATE)>>8);
		UBRRL_R = (uint8_t)BAUD_RATE_U2X(USART_BAUDRATE);
		UCSRA_R = 1<<UART_UCSRA_U2X;
	}else
	{/*- If double speed disabled -*/
		UBRRH_R = (uint8_t)(BAUD_RATE(USART_BAUDRATE)>>8);
		UBRRL_R = (uint8_t)BAUD_RATE(USART_BAUDRATE);
		UCSRA_R &= ~(1<<UART_UCSRA_U2X);	
	}
	/* Enable receiver and/or transmitter */
	UCSRB_R = strUart_Config.u8_Enable;
	/* Enable bit UCSZ2 if DataFrameSize is 9 bits */
	if(strUart_Config.u8_DataFrameSize == UART_SIZE_9_BITS)
	{
		UCSRB_R |= 1 << UART_UCSRB_UCSZ2;
	}
// 	/* Set the Interrupts if Enabled */
// 	if(strUart_Config.u8_Interrupt != UART_INTERRUPT_DISABLE)
// 	{
// 		UART_UCSRB_REG |= strUart_Config.u8_Interrupt;
// 	}
	/* Set the stop bits */
	UCSRC_R = (1<<UART_UCSRC_URSEL)|(strUart_Config.u8_StopBits<<UART_UCSRC_USBS);
	
	/* Set the DataFrameSize in UCSZ0 and UCSZ1 */
	UCSRC_R |= (1<<UART_UCSRC_URSEL)|(((strUart_Config.u8_DataFrameSize) & 0x03)<<UART_UCSRC_UCSZ0);
	
	/* Set the Parity Mode Disabled or Enabled Even/Odd */
	if(strUart_Config.u8_ParityMode != UART_PARITY_DISABLE)
	{
		UCSRC_R |= (1<<UART_UCSRC_URSEL)|((strUart_Config.u8_ParityMode) << UART_UCSRC_UPM0);
	}
	
	/*- Set the Uart module state to initialized -*/
	u8_Uart_Status = UART_INITIALIZED;
	return UART_STATUS_ERROR_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_sendByte
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8_Data - Data to be sent (Size: 5~8 Bits)
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to send Single Data Frame of size from 5 to 8 bits according to data 
*				size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_sendByte(uint8_t u8_Data)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
		
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Wait till the data register is empty */
	while (!(UCSRA_R & (1<<UART_UCSRA_UDRE)));
	/* Fill the data register with the data to be sent */
	UDR_R = u8_Data ;
	
	return UART_STATUS_ERROR_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_sendByte
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u8_Data - Data to be sent (Size: 5~8 Bits)
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType - return the status of the function ERROR_OK or NOT_OK
* Description: Function to send Single Data Frame of size from 5 to 8 bits according to data
*				size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Uart_writeByte(uint8_t Uart_ChannelID, uint8_t u8_data)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
		
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Wait till the data register is empty */
	/*while (!(UART_UCSRA_REG & (1<<UART_UCSRA_UDRE)));*/
	/* Fill the data register with the data to be sent */
	UDR_R = u8_data ;
		
	return E_OK;
}
	
	
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_sendPacket
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): pu8_Data - Pointer to array Data to be sent (Each frame Size: 5~8 Bits).
*				   u16_packetSize - Number of data elements (Frames) to be sent.
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to send Multiple Data Frame (Each frame Size: 5~8 Bits) according to data
*			   size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_sendPacket(uint8_t *pu8_Data, uint16_t u16_packetSize)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if(UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	uint16_t u16_loopIndex=0;
	for(u16_loopIndex=0; u16_loopIndex<u16_packetSize; u16_loopIndex++)
	{
		/* Send the data element by element and check for the return if error */
		if(Uart_sendByte(pu8_Data[u16_loopIndex]) != UART_STATUS_ERROR_OK)
			return UART_STATUS_ERROR_NOK;
	}
	return UART_STATUS_ERROR_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_receiveByte
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): pu8_Data - Data to be received (Size: 5~8 Bits)
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to receive Single Data Frames of size from 5 to 8 bits according to data
*				size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_receiveByte(uint8_t *pu8_Data)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Wait till the data register has data */
	while (!(UCSRA_R & (1<<UART_UCSRA_RXC)));
	
	/* Read the received Data from data register */
	*pu8_Data = UDR_R;
	return UART_STATUS_ERROR_OK;	
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_readByte
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): pu8_Data - Data to be received (Size: 5~8 Bits)
* Return value: Std_ReturnType - return the status of the function ERROR_OK or NOT_OK
* Description: Function to receive Single Data Frames of size from 5 to 8 bits according to data
*				size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Uart_readByte(uint8_t Uart_ChannelID, uint8_t *pu8_data)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
		
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/* Wait till the data register has data */
// 	while (!(UART_UCSRA_REG & (1<<UART_UCSRA_RXC)));
		
	/* Read the received Data from data register */
	*pu8_data = UDR_R;
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_receivePacket
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): u16_packetSize - Number of data elements (Frames) to be received.
* Parameters (inout): None
* Parameters (out): pu8_Data - Pointer to array Data to be received (Each frame Size: 5~8 Bits).
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to receive Multiple Data Frames (Each frame Size: 5~9 Bits) according to data
*			   size in Configurations.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_receivePacket(uint8_t *pu8_Data, uint16_t u16_packetSize)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if(UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
	
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	uint16_t u16_loopIndex=0;
	for(u16_loopIndex=0; u16_loopIndex<u16_packetSize; u16_loopIndex++)
	{
		/* Receive the data element by element and check for the return if error */
		if(Uart_receiveByte(&pu8_Data[u16_loopIndex]) != UART_STATUS_ERROR_OK)
		return UART_STATUS_ERROR_NOK;
	}
	return UART_STATUS_ERROR_OK;
}



/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_EnableNotification_TXC
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Uart_Callback - Pointer to function to be called after sending 1 byte.
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Enable the Interrupt TXC Flag and assign Uart_Callback as a 
*              callback function to it.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Uart_EnableNotification_TXC(uint8_t Uart_ChannelID)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
// 	/* Check if the Callback pointer is NULL */
// 	if(Uart_Callback == NULL_PTR)
// 	{
// 		return UART_STATUS_NULL_ARGUMENT;
// 	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Enable the Uart TXC Interrupt -*/
	UCSRB_R |= UART_INTERRUPT_TXCIE;
	/* Assign the Callback function to the UART's ISR Handler Caller */
	/*Interrupt_install(USART_TXC_IRQ, Uart_Callback);*/
		
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_EnableNotification_RXC
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Uart_Callback - Pointer to function to be called after sending 1 byte.
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Enable the Interrupt RXC Flag and assign Uart_Callback as a 
*              callback function to it.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_EnableNotification_RXC(uint8_t Uart_ChannelID)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Enable the Uart RXC Interrupt -*/
	UCSRB_R |= UART_INTERRUPT_RXCIE;
	/* Assign the Callback function to the UART's ISR Handler Caller */
	/*Interrupt_install(USART_RXC_IRQ, Uart_Callback);*/
		
	return UART_STATUS_ERROR_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_EnableNotification_UDRE
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Uart_Callback - Pointer to function to be called after sending 1 byte.
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Enable the Interrupt UDRE Flag and assign Uart_Callback as a
*              callback function to it.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
enuUart_Status_t Uart_EnableNotification_UDRE(uint8_t Uart_ChannelID)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return UART_STATUS_NOT_INIT;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Enable the Uart UDRE Interrupt -*/
	UCSRB_R |= UART_INTERRUPT_UDRIE;
	/* Assign the Callback function to the UART's ISR Handler Caller */
	//Interrupt_install(USART_UDRE_IRQ, Uart_Callback);
	return UART_STATUS_ERROR_OK;
}


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_DisableNotification
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): u8_InterruptFlags - Interrupt Flags to be stopped.
*					@options: UART_INTERRUPT_RXCIE | UART_INTERRUPT_TXCIE | UART_INTERRUPT_UDRIE
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Disable the given interrupt flag/s.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Uart_DisableNotification_TXC(uint8_t Uart_ChannelID)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Disable the Uart TXC Interrupt -*/
	UCSRB_R &= ~UART_INTERRUPT_TXCIE;
			
	return E_OK;
}

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
* Service Name: Uart_DisableNotification
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): u8_InterruptFlags - Interrupt Flags to be stopped.
*					@options: UART_INTERRUPT_RXCIE | UART_INTERRUPT_TXCIE | UART_INTERRUPT_UDRIE
* Parameters (inout): None
* Parameters (out): None
* Return value: enuUart_Status_t - return the status of the function ERROR_OK or NOT_OK
* Description: Function to Disable the given interrupt flag/s.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
Std_ReturnType Uart_DisableNotification_RXC(uint8_t Uart_ChannelID)
{
/**************************************************************************************/
/*								Start of Error Checking								  */
/**************************************************************************************/
	/* Check if the Uart module is not initialized */
	if (UART_NOT_INITIALIZED == u8_Uart_Status)
	{
		return E_NOT_OK;
	}else{/*Nothing to here*/}
/**************************************************************************************/
/*								End of Error Checking								  */
/**************************************************************************************/

/**************************************************************************************/
/*								Function Implementation								  */
/**************************************************************************************/
	/*- Disable the Uart TXC Interrupt -*/
	UCSRB_R &= ~UART_INTERRUPT_RXCIE;
	
	return E_OK;
}

/*********************************************************
* Uart_DataRegister : Function used directly to return
*				the content of the data registers
* Mainly used by the ISR Callback funtions
*********************************************************/
uint8_t Uart_DataRegister(void)
{
	return UDR_R;
}


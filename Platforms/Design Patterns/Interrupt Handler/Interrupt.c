/*****************************************************************************
* Module: Interrupt Handler Module
* File Name: Interrupt.c
* Description: Source file for Interrupt Handler
* Author: Ahnmed Nabil
* Date: 19-August-2021
******************************************************************************/
#include "Interrupt.h"
#include "Interrupt_Interface.h"
#include "../../Microcontroller/Std_Types.h"
#include "../../Libraries/Common_Macros.h"
#include "../Atmega32 Registers/ISR_Regs.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
pf_Vector old_Vectors[VECTORS_NUM] = 
{
    IntDefaultHandler,          /** External Interrupt Request 0 **/
    IntDefaultHandler,          /** External Interrupt Request 1 **/
    IntDefaultHandler,          /** External Interrupt Request 2 **/
    IntDefaultHandler,          /** Timer/Counter2 Compare Match **/
    IntDefaultHandler,          /** Timer/Counter2 Overflow **/
    IntDefaultHandler,          /** Timer/Counter1 Capture Event **/
    IntDefaultHandler,          /** Timer/Counter1 Compare Match A **/
    IntDefaultHandler,          /** Timer/Counter1 Compare Match B **/
    IntDefaultHandler,          /** Timer/Counter1 Overflow **/
    IntDefaultHandler,          /** Timer/Counter0 Compare Match **/
    IntDefaultHandler,          /** Timer/Counter0 Overflow **/
    IntDefaultHandler,          /** SPI Serial Transfer Complete **/
    IntDefaultHandler,          /** USART, Rx Complete **/
    IntDefaultHandler,          /** USART Data Register Empty **/
    IntDefaultHandler,          /** USART, Tx Complete **/
    IntDefaultHandler,          /** ADC Conversion Complete **/
    IntDefaultHandler,          /** EEPROM Ready **/
    IntDefaultHandler,          /** Analog Comparator **/
    IntDefaultHandler,          /** Two-wire Serial Interface **/
    IntDefaultHandler           /** Store Program Memory Ready **/
};

void EnableGlobalInterrupts(void)
{
	SET_BIT(SREG_R, GLOBAL_INT);
}

void DisableGlobalInterrupts(void)
{
	CLEAR_BIT(SREG_R, GLOBAL_INT);
}

/*- Function Definitions
-------------------------------*/
void IntDefaultHandler(void)
{
    while (1)
    {
    }
    
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: interrupt service routine for external interrupt 2 ISR
******************************************************************************************/
ISR(INT0)
{
    old_Vectors[INT0_IRQ]();
}

ISR(INT1)
{
    old_Vectors[INT1_IRQ]();
}

ISR(INT2)
{
    old_Vectors[INT2_IRQ]();
}

ISR(TIMER2_COMP)
{
    old_Vectors[TIMER2_COMP_IRQ]();
}

ISR(TIMER2_OVF)
{
    old_Vectors[TIMER2_OVF_IRQ]();
}

ISR(TIMER1_CAPT)
{
    old_Vectors[TIMER1_CAPT_IRQ]();
}

ISR(TIMER1_COMPA)
{
    old_Vectors[TIMER1_COMPA_IRQ]();
}

ISR(TIMER1_COMPB)
{
    old_Vectors[TIMER1_COMPB_IRQ]();
}

ISR(TIMER1_OVF)
{
    old_Vectors[TIMER1_OVF_IRQ]();
}

ISR(TIMER0_COMP)
{
    old_Vectors[TIMER0_COMP_IRQ]();
}

ISR(TIMER0_OVF)
{
    old_Vectors[TIMER0_OVF_IRQ]();
}

ISR(SPI_STC)
{
    old_Vectors[SPI_STC_IRQ]();
}

ISR(USART_RXC)
{
    old_Vectors[USART_RXC_IRQ]();
}

ISR(USART_UDRE)
{
    old_Vectors[USART_UDRE_IRQ]();
}

ISR(USART_TXC)
{
    old_Vectors[USART_TXC_IRQ]();
}

ISR(ADC)
{
    old_Vectors[ADC_IRQ]();
}

ISR(EE_RDY)
{
    old_Vectors[EE_RDY_IRQ]();
}

ISR(ANA_COMP)
{
    old_Vectors[ANA_COMP_IRQ]();
}

ISR(TWI)
{
    old_Vectors[TWI_IRQ]();
}

ISR(SPM_RDY)
{
    old_Vectors[SPM_RDY_IRQ]();
}

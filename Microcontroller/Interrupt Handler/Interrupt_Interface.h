/*****************************************************************************
* Module: Interrupt Handler Module
* File Name: Interrupt_Interface.h
* Description: Source file for Interrupt Handler's interface
* Author: Ahnmed Nabil
* Date: 19-August-2021
******************************************************************************/


#ifndef _INTERRUPT_INTERFACE_H_
#define _INTERRUPT_INTERFACE_H_

#include "Interrupt.h"

#define INT0_IRQ                        0U
#define INT1_IRQ                        1U
#define INT2_IRQ                        2U
#define TIMER2_COMP_IRQ                 3U
#define TIMER2_OVF_IRQ                  4U
#define TIMER1_CAPT_IRQ                 5U
#define TIMER1_COMPA_IRQ                6U
#define TIMER1_COMPB_IRQ                7U
#define TIMER1_OVF_IRQ                  8U
#define TIMER0_COMP_IRQ                 9U
#define TIMER0_OVF_IRQ                  10U
#define SPI_STC_IRQ                     11U
#define USART_RXC_IRQ                   12U
#define USART_UDRE_IRQ                  13U
#define USART_TXC_IRQ                   14U
#define ADC_IRQ                         15U
#define EE_RDY_IRQ                      16U
#define ANA_COMP_IRQ                    17U
#define TWI_IRQ                         18U
#define SPM_RDY_IRQ                     19U
#define INVALID_ID                      20U


/** Global Interrupt Functions **/
void EnableGlobalInterrupts(void);
void DisableGlobalInterrupts(void);

/** Installing and Deinstalling Functions **/
void Interrupt_install(uint8_t vectorId_u8, pf_CallBack ISR_Callback);
void Interrupt_deinstall(uint8_t vectorId_u8);

#endif
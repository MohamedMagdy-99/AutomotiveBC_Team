/*****************************************************************************
* Module: Interrupt Handler Module
* File Name: Interrupt_Interface.h
* Description: Source file for Interrupt Handler's interface
* Author: Ahnmed Nabil
* Date: 19-August-2021
******************************************************************************/
#include "Interrupt_Interface.h"

void Interrupt_install(uint8_t vectorId_u8, pf_CallBack ISR_Callback)
{
    if((ISR_Callback != NULL_PTR) && (vectorId_u8 < INVALID_ID))
    {
        old_Vectors[vectorId_u8] = ISR_Callback;
    }
    else
    {

    }
}

void Interrupt_deinstall(uint8_t vectorId_u8)
{
    if(vectorId_u8 < INVALID_ID)
    {
        old_Vectors[vectorId_u8] = IntDefaultHandler;
    }
    else
    {
        
    }
}


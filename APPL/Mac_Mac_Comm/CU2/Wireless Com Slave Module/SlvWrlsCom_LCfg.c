/*
 * SlvWrlsCom_LCfg.c
 *
 * Created: 9/8/2021 1:58:23 PM
 *  Author: Ahmed Nabil
 */ 
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "SlvWrlsCom.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANT CONFIGURATIONS -*-*-*-*-*-*/
const WrlsCom_Config WrlsCom_BlthDevice_constConfig = 
{	/* Baud Rate*/		  /* Role */		/* Name */		/* Password*/
	     38400,			BLTH_ROLE_SLAVE,	 "CU2 - 4",		  "228989"
};

const uint8_t WrlsCom_BlthDevice_Handshake_Packet[7] = {0xAA, 0x01, 0x03, 0x41, 0x45, 0x48, '\0'};
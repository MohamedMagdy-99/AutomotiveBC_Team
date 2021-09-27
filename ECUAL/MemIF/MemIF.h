/*
 * MemIF.h
 *
 * Created: 16-Sep-21 3:01:32 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef MEMIF_H_
#define MEMIF_H_

#include "ECUAL/Eeprom_I2C Module/Eeprom_24.h"




typedef uint8_t MemIF_MemoryID_t;


#define MemIF_init()										Eeprom_24_init()
#define MemIF_writeByte(ID, loc, data)						Eeprom_24_writeByte(loc, data)
#define MemIF_readByte(ID, loc, data)						Eeprom_24_readByte(loc, data)
#define MemIF_writePacket(ID, loc, data, length)			Eeprom_24_writePacket(loc, data, length)
#define MemIF_readPacket(ID, loc, data, length)				Eeprom_24_readPacket(loc, data, length)


#define MEMIF_EEPROM_256K_ID								0U


#endif /* MEMIF_H_ */
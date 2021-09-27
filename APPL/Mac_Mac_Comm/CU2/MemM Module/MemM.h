/*
 * MemM.h
 *
 * Created: 6/9/2021
 *  Author:Ahmed Nabil
 */ 


#ifndef MEMM_H_
#define MEMM_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "MemM_LCfg.h"
#include "ECUAL/MemIF/MemIF.h"
#include "Microcontroller/Std_types.h"
#include "Microcontroller/Platform_Types.h"
#include "Libraries/Utility Module/Utility.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS *-*-*-*-*-*/


/*- Primitive Types
-------------------------------*/
typedef uint8_t MemM_BlockID_t;
typedef uint16_t MemM_BlockAddress_t;
typedef uint16_t MemM_BlockSize_t;
typedef uint8_t MemM_BlockData_t;


/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct  
{
	MemIF_MemoryID_t	MemoryID;
	MemM_BlockAddress_t Block_Address;
	MemM_BlockSize_t Data_Size;
}MemM_BlockConfig_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Used to initialize the Memory Manager Module */
Std_ReturnType MemM_init(void);
/* Function to write the data of the Block in the memory */
Std_ReturnType MemM_writeBlock(MemM_BlockID_t BlockID, uint8_t *Data_Ptr, uint16_t dataLength);
/* Function to read data of a block from its location from the memory */
Std_ReturnType MemM_readBlock(MemM_BlockID_t BlockID, uint8_t *Data_Ptr);

//Std_ReturnType MemM_createBlock(MemM_BlockInfo_t *block_ptr, uint8_t maxBlock_Size, MemM_BlockAddress_t Block_StartAddress);

Std_ReturnType MemM_eraseBlock(MemM_BlockID_t blockID);
Std_ReturnType MemM_deleteBlock(MemM_BlockID_t blockID);
Std_ReturnType MemM_setBlock(MemM_BlockID_t blockID, MemM_BlockAddress_t MemoryAddress,
							 MemM_BlockData_t *dataPtr, MemM_BlockSize_t dataSize);

/* Configuration Extern Variable */
extern MemM_BlockConfig_t MemM_BlocksConfig[MEMM_USED_BLOCKS_NUM];
#endif /* MEMM_H_ */
/*
 * MemM.c
 *
 * Created: 6/9/2021
 *  Authors: Ahmed Nabil 
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "MemM.h"

/*- CONSTANTS
----------------------------------------------*/


/*- GLOBAL EXTERN VARIABLES -------------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initialized BCM module.
************************************************************************************/
Std_ReturnType MemM_init(void)
{
	MemIF_init();
	
	return E_OK;
}

/************************************************************************************
* Parameters (in): comChannelId
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: ask BCM to get any received data from a certain com. channel
************************************************************************************/

Std_ReturnType MemM_writeBlock(MemM_BlockID_t BlockID, uint8_t *Data_Ptr, uint16_t dataLength)
{
	MemIF_writePacket(MemM_BlocksConfig[BlockID].Block_Address , Data_Ptr, dataLength);
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state BCM Rx.
************************************************************************************/
Std_ReturnType MemM_readBlock(MemM_BlockID_t BlockID, uint8_t *Data_Ptr)
{
	MemIF_readPacket(MemM_BlocksConfig[BlockID].Block_Address , Data_Ptr, MemM_BlocksConfig[BlockID].Data_Size);
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType MemM_eraseBlock(MemM_BlockID_t blockID)
{
	return E_OK;
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
#if 0
Std_ReturnType MemM_createBlock(MemM_BlockInfo_t *block_ptr, uint8_t maxBlock_Size, MemM_BlockAddress_t Block_StartAddress)
{
	if((block_ptr == NULL_PTR) || (BlocksCounter == MEMM_MAX_BLOCKS_NUM-1) || (maxBlock_Size > MEMM_MAX_DATA_SIZE))
	{
		return E_NOT_OK;
	}
	
	block_ptr->Block_ID = BlocksCounter;
	block_ptr->Data_Size = maxBlock_Size;
	BlocksCounter++;
	MemM_BlocksAddresses[BlocksCounter].Block_Address = Block_StartAddress;
	MemM_BlocksAddresses[BlocksCounter].Block_ID = BlocksCounter;
	return E_OK;
}
#endif 
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given device.
************************************************************************************/
Std_ReturnType MemM_deleteBlock(MemM_BlockID_t blockID)
{
	return E_OK;
}

/************************************************************************************
* Parameters (in): blockID - Index of the Block in the Array
*				   MemoryAddress - Address in the Memory.
*				   dataPtr - Pointer to the data to be saved.
*                  dataSize - Size of the data.
* Parameters (out): None
* Return value: Std_ReturnType
* Description: update the data of the block.
************************************************************************************/
#if 0
Std_ReturnType MemM_setBlock(MemM_BlockID_t blockID, MemM_BlockAddress_t MemoryAddress,
							 MemM_BlockData_t *dataPtr, MemM_BlockSize_t dataSize)
{
	if((blockID > MemM_BlocksCounter) || (dataPtr == NULL_PTR) || (dataSize > MEMM_MAX_DATA_SIZE))
	{
		return E_NOT_OK;
	}
	
	MemM_UserBlocks[blockID].Address_Offset = MemoryAddress;
	arrayCopy(dataPtr, MemM_UserBlocks[blockID].Data, dataSize);
	MemM_UserBlocks[blockID].Data_Size = dataSize;
	
	return E_OK;
}
#endif
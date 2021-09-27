/*
 * MemM_LCfg.h
 *
 * Created: 6/9/2021 
 *  Author: Ahmed Nabil
 */ 


#ifndef MEMM_LCFG_H_
#define MEMM_LCFG_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES (Com. channels used) *-*-*-*-*-*/


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
	
#define MEMM_MAX_RUN_TIME_CREATED_BLOCKS_NUM					3U
	
#define MEMM_MAX_DATA_SIZE										25U



#define MEMM_USED_BLOCKS_NUM				4U

#define MEMM_VALID_DEVICE_FLAG_ID			0U
#define MEMM_VALID_DEVICE_FLAG_LOC			0x00U
#define MEMM_VALID_DEVICE_FLAG_SIZE			1U

#define MEMM_CONNECTED_DEVICE_NAME_ID		1U
#define MEMM_CONNECTED_DEVICE_NAME_LOC		0x05U
#define MEMM_CONNECTED_DEVICE_NAME_SIZE		7U

#define MEMM_CONNECTED_DEVICE_MAC_ID		2U
#define MEMM_CONNECTED_DEVICE_MAC_LOC		0x0CU
#define MEMM_CONNECTED_DEVICE_MAC_SIZE		12U

#define MEMM_CONNECTED_DEVICE_DATA_PACK_ID			3U
#define MEMM_CONNECTED_DEVICE_DATA_PACK_LOC			0x02U
#define MEMM_CONNECTED_DEVICE_DATA_PACK_SIZE		23U

#endif /* MEMM_LCFG_H_ */
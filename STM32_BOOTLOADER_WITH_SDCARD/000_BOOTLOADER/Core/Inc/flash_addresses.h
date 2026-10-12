/*
 * flash_address.h
 *
 *  Created on: Sep 28, 2026
 *      Author: DELL
 */

#ifndef INC_FLASH_ADDRESSES_H_
#define INC_FLASH_ADDRESSES_H_

/*
 * @brief Flash address */
#define BL_START_ADDR					0x08000000U  	// Flash start address (64KB - (0-3) Sectors)
#define BL_METADATA_ADDR				0x0800C000		// Sector 3 for the slot informatin
#define BL_APP_HEADER_ADDR				0x08010000U		// 64KB - Sector 4

#define APP1_START_ADDR					0x08020000U		// From sector 5 to 7
#define APP2_START_ADDR					0x08080000U		// From sector 8 to 11

#define APP1_START_SECTOR               5               // App1 starting sector
#define APP1_NO_OF_SECTORS				3       		// Occupied sector by app1

#define APP2_START_SECTOR               8               // App2 starting sector
#define APP2_NO_OF_SECTORS				4       		// Occupied sector by app2

#define APP1_SLOT                       1
#define APP2_SLOT                       2


#endif /* INC_FLASH_ADDRESSES_H_ */

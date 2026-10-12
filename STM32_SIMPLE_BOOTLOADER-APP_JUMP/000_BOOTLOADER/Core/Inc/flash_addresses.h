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
#define BL_APP_HEADER_ADDR				0x08010000U		// 64KB - Sector 4
#define APP_START_ADDR					0x08020000U		// From sector 5 to onward

#endif /* INC_FLASH_ADDRESSES_H_ */

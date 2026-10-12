/*
 * flash_operation.h
 *
 *  Created on: Sep 30, 2026
 *      Author: DELL
 */

#ifndef INC_FLASH_OPERATIONS_H_
#define INC_FLASH_OPERATIONS_H_

#include <stdio.h>
#include <stdint.h>

/**
 * @brief To erase a sector
 * 
 * @param[in] sector sector to erase
 * 
 * @return 0 on success
 */
uint8_t flash_operations_erase_sector(uint32_t sector, uint32_t no_of_sector_to_erase);

/**
 * @brief To program a byte
 * 
 * @param[in] flash_address Flash address to program
 * @param[in] data data to write on flash
 * 
 * @return 0 on success
 */
uint8_t flash_operations_program_byte(uint32_t flash_address, uint32_t data);

/**
 * @brief Locks the internal Flash interface.
 *
 * Prevents further Flash programming and erase operations until Flash
 * is unlocked again.
 *
 * @return 0 if Flash is locked successfully; 1 otherwise.
 */
uint8_t flash_operation_lock_flash(void);

/**
 * @brief Unlocks the internal Flash interface.
 *
 * Enables Flash programming and erase operations.
 *
 * @return 0 if Flash is unlocked successfully; 1 otherwise.
 */
uint8_t flash_operation_unlock_flash(void);


//uint8_t flash_operation_write_word(uint32_t flash_address, uint32_t data);
uint8_t flash_operation_write_byte(uint32_t flash_address, uint8_t data);


#endif /* INC_FLASH_OPERATIONS_H_ */

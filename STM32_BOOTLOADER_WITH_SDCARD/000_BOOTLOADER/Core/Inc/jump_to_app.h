/*
 * jump_to_app.h
 *
 *  Created on: Sep 28, 2026
 *      Author: DELL
 */

#ifndef INC_JUMP_TO_APP_H_
#define INC_JUMP_TO_APP_H_

#include <stdint.h>

/**
 * @brief Transfers execution to the application firmware.
 *
 * Reads the initial stack pointer and reset handler from the
 * application's vector table, disables interrupts, stops SysTick,
 * sets the main stack pointer, and calls the application reset handler.
 *
 * @note The application is responsible for configuring its vector
 *       table and initializing its system and peripherals.
 */
void jump_to_application(uint32_t flash_address);
uint32_t is_app_valid(void);

uint32_t bootloader_get_active_slot(void);

/**
 * @brief Reads the stored active application slot from Flash metadata.
 *
 * Interprets the data at BL_METADATA_ADDR as a bootloader_header_t structure
 * and returns its active_slot field.
 *
 * @return Stored active slot value, such as APP1_SLOT or APP2_SLOT.
 *
 * @note This function does not verify whether the stored value is valid
 *       or whether the corresponding application image is usable.
 */
uint8_t bootloader_set_active_slot(uint32_t slot);

#endif /* INC_JUMP_TO_APP_H_ */

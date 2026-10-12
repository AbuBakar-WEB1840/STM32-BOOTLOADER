/*
 * download_firmware.h
 *
 *  Created on: Oct 8, 2026
 *      Author: DELL
 */

#ifndef INC_DOWNLOAD_FIRMWARE_H_
#define INC_DOWNLOAD_FIRMWARE_H_

/**
 * @brief Reads firmware from the SD card and programs it into internal Flash.
 *
 * Mounts the SD card, opens the firmware binary file, erases the target
 * Flash sectors, and writes the firmware data in chunks.
 *
 * @param[in] app_address Starting Flash address where the firmware is to be
 *                        programmed.
 *
 * @note The firmware filename is currently fixed to
 *       "001_APP_LED_BLINK.bin".
 * @note The current implementation erases APP1 sectors regardless of the
 *       supplied app_address.
 * @note Mounting, file opening, Flash unlock, and programming failures cause
 *       the function to enter an infinite loop. A read error terminates the
 *       programming loop without reporting failure to the caller.
 * @note Firmware size and CRC are not validated before or after programming.
 *
 * @warning Verify the target address and erase-sector configuration before
 *          using this function to update firmware.
 *
 * @return None.
 */
void download_and_flash_firmware(uint32_t flash_address);

#endif /* INC_DOWNLOAD_FIRMWARE_H_ */

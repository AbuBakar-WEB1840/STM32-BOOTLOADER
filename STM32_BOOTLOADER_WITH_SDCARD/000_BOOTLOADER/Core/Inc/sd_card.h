/*
 * sd_card.h
 *
 *  Created on: Oct 8, 2026
 *      Author: DELL
 */

#ifndef INC_SD_CARD_H_
#define INC_SD_CARD_H_

#include <stdint.h>
#include <stdio.h>
#include "integer.h"

/**
 * @brief Mounts the SD card file system.
 *
 * @return 0 on success, non-zero on failure.
 */
uint8_t sd_card_mount(void);

/**
 * @brief Opens a file on the SD card.
 *
 * @param file_path     Path of the file to open.
 * @param file_operation File operation mode (e.g. FA_READ).
 *
 * @return 0 on success, non-zero on failure.
 */
uint8_t sd_card_open_file(const char *file_path, uint8_t file_operation);

/**
 * @brief Reads data from the currently opened file.
 *
 * @param buff                 Buffer to store the read data.
 * @param buff_len             Number of bytes to read.
 * @param pNo_of_read_bytes    Number of bytes actually read.
 *
 * @return 0 on success, non-zero on failure.
 */
uint8_t sd_card_read_file(void *buff, uint32_t buff_len, UINT *pNo_of_read_bytes);

/**
 * @brief Closes the currently opened file.
 *
 * @return 0 on success, non-zero on failure.
 */
uint8_t sd_card_close_file(void);

#endif /* INC_SD_CARD_H_ */

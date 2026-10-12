/*
 * sd_card.c
 *
 *  Created on: Oct 8, 2026
 *      Author: DELL
 */

#include "sd_card.h"

#include "fatfs.h"

FATFS FatFs;  // Fatfs handle
FIL fil;      // File handle
FRESULT fres; // Result after operations


uint8_t sd_card_mount(void)
{
	fres = f_mount(&FatFs, "", 1); // 1=mount now
	if (fres != FR_OK) {
		return 1;
	}

	return 0;
}


uint8_t sd_card_open_file(const TCHAR *file_path, uint8_t file_operation)
{
	fres = f_open(&fil, file_path, file_operation);
	if (fres != FR_OK) {
		return 1;
	}
	return 0;
}

uint8_t sd_card_read_file(	void* buff,	uint32_t buff_len, UINT* pNo_of_read_bytes)
{
	fres = f_read(&fil, buff, buff_len, pNo_of_read_bytes);
	if (fres != FR_OK) {
		return 1;
	}
	return 0;
}

uint8_t sd_card_close_file(void)
{
	   f_close(&fil);
}

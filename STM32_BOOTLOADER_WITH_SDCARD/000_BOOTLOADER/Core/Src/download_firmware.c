/*
 * download_firmware.c
 *
 *  Created on: Oct 8, 2026
 *      Author: DELL
 */
#include "fatfs.h"
#include "download_firmware.h"
#include "sd_card.h"
#include "flash_operations.h"
#include "flash_addresses.h"

void download_and_flash_firmware(uint32_t app_address)
{
	FRESULT fres; // Result after operations

	// Open the file system
	uint8_t ret = sd_card_mount();
	if (ret)
	{
		while (1)
			;
	}

	// Now let's try to open file 001_APP_LED_BLINK.bin
	ret = sd_card_open_file("001_APP_LED_BLINK.bin", FA_READ);
	if (ret)
	{
		while (1)
			;
	}

	uint8_t fw_buffer[512]; /* Max we can read 512, it can be change in the Sd card configuration */
	UINT bytes_read;
	UINT total_bytes_read = 0;
	uint32_t flash_address = app_address;

	flash_operations_erase_sector(APP1_START_SECTOR, APP1_NO_OF_SECTORS);

	//    Unlock to flash to perform the write on it
	fres = flash_operation_unlock_flash();
	if (fres != 0)
	{
		while (1)
			;
	}

	do
	{
		fres = sd_card_read_file(fw_buffer, sizeof(fw_buffer), &bytes_read);

		if (fres != FR_OK)
		{
			break;
		}

		if (bytes_read > 0)
		{
			total_bytes_read += bytes_read;

			// fw_buffer now contains firmware bytes.
			// Next step: calculate CRC or program Flash.
		}

		for (uint32_t i = 0; i < bytes_read; i++)
		{
			if (flash_operation_write_byte(flash_address,
										   fw_buffer[i]) != 0)
			{
				while (1)
					;
			}

			flash_address++;
		}

	} while (bytes_read > 0);

	fres = flash_operation_lock_flash();

	if (fres != 0)
	{
		while (1)
			;
	}

	sd_card_close_file();
}

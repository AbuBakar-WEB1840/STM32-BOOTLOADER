/*
 * flash_operations.c
 *
 *  Created on: Sep 30, 2026
 *      Author: DELL
 */


#include "flash_operations.h"

#include "stm32f4xx_hal.h"

uint8_t flash_operations_erase_sector(uint32_t sector, uint32_t no_of_sector_to_erase)
{
    // 1. Unlock the flash to perform operation on it
    HAL_StatusTypeDef ret = HAL_FLASH_Unlock();
    if (ret != HAL_OK)
    {
        return 1;
    }

    // Erase the sector
    FLASH_EraseInitTypeDef erase_sector = {0};
    erase_sector.Banks = 0;
    erase_sector.Sector = sector;
    erase_sector.NbSectors = no_of_sector_to_erase;
    erase_sector.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase_sector.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    uint32_t sectError = 0;
    ret = HAL_FLASHEx_Erase(&erase_sector, &sectError);

    // Lock the flash
    ret = HAL_FLASH_Lock();
    if (ret != HAL_OK)
    {
        return 1;
    }

    return 0;
}

uint8_t flash_operations_program_byte(uint32_t flash_address, uint32_t data)
{
    // 1. Unlock the flash to perform operation on it
    uint8_t ret = HAL_FLASH_Unlock();
    if (ret != HAL_OK)
    {
        return 1;
    }

    // 2. Pointer to flash_address
    ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_address, data);
    if (ret != HAL_OK)
	{
    	HAL_FLASH_Lock();
		return 1;
	}

    // Lock the flash
    ret = HAL_FLASH_Lock();
    if (ret != HAL_OK)
    {
        return 1;
    }

    return 0;
}

uint8_t flash_operation_lock_flash(void)
{
	return (HAL_FLASH_Lock() == HAL_OK) ? 0 : 1;
}

uint8_t flash_operation_unlock_flash(void)
{
	return (HAL_FLASH_Unlock() == HAL_OK) ? 0 : 1;
}

//uint8_t flash_operation_write_word(uint32_t flash_address, uint32_t data)
//{
//	//  Pointer to flash_address
//	uint8_t ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, flash_address, data);
//	if (ret != HAL_OK)
//	{
//		HAL_FLASH_Lock();
//		return 1;
//	}
//	return 0;
//}

uint8_t flash_operation_write_byte(uint32_t flash_address, uint8_t data)
{
    HAL_StatusTypeDef ret;

    ret = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,
                            flash_address,
                            data);

    if (ret != HAL_OK)
    {
        return 1;
    }

    return 0;
}

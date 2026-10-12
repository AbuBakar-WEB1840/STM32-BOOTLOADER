/*
 * jump_to_app.c
 *
 *  Created on: Sep 28, 2026
 *      Author: DELL
 *
 *
 */

#include "jump_to_app.h"

#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "flash_addresses.h"
#include "app_header.h"
#include "crc32.h"
#include "flash_operations.h"

#define APP_NUMBER          0xFFFFFFFF
#define APP_MAX_SIZE        40*1024
#define APP_CRC             0xCECCF9E6

/*
 * @brief This function will be called by the bootloader to
 * jump to main application
 * */
typedef void (*pFunction)(void);
void jump_to_application(uint32_t flash_address)
{
    uint32_t stack_addr         = 0;
    uint32_t reset_handler_addr = 0;
    pFunction app_entry          = 0;

    /* Stack address */
    stack_addr = *((uint32_t*)flash_address);

    /* Reset handler address */
    reset_handler_addr = *((uint32_t*)(flash_address + 4));

    app_entry = (pFunction)(reset_handler_addr);

    /* Disable every interrupt, before jumping to application */
    __disable_irq();

    /* Disable systick */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;

    /* Set the stack pointer */
    __set_MSP(stack_addr);

    /* Jump to application */
    app_entry();
}

/**
 * @brief To verify either the application is valid or not
 */
uint32_t is_app_valid(void)
{
    uint32_t app_hddr_addr = BL_APP_HEADER_ADDR;

    app_header_t *app_header = ((app_header_t*)app_hddr_addr);

    /* 1. Check the firmware number for verification (simple way to verify) */
    // if (app_header->app_number != APP_NUMBER)
    // {
    //     return 1;       /* Firmware is not valid */
    // }

    /* 2. Check the application size */
    if ((app_header->size == 0) || (app_header->size > APP_MAX_SIZE))
    {
        return 2;       /* Firmware is not valid */
    }

    /* 3. Calcualte the CRC */
    // uint32_t cal_crc = crc32((uint8_t*)APP1_START_ADDR, app_header->size);
    // if (cal_crc != app_header->crc)
    // {
    //     return 3;       /* Firmware is not valid */
    // }
    return 0;       /* Firmware is valid */
}




uint32_t bootloader_get_active_slot(void)
{
	bootloader_header_t *data = (bootloader_header_t *)BL_METADATA_ADDR;

    return data->active_slot;
}


uint8_t bootloader_set_active_slot(uint32_t slot)
{
    if ((slot != APP1_SLOT) && (slot != APP2_SLOT))
    {
        return 1;
    }

    if (flash_operations_erase_sector(3U, 1U) != 0)
   {
	   return 1;
   }

    if (flash_operation_unlock_flash() != 0)
    {
        return 1;
    }

    if (flash_operation_write_byte(BL_METADATA_ADDR, slot) != 0)
    {
        flash_operation_lock_flash();
        return 1;
    }

    flash_operation_lock_flash();

    return 0;
}


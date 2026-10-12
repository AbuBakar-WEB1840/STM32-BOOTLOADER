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


typedef void (*pFunction)(void);
void jump_to_application(void)
{
    uint32_t stack_addr         = 0;
    uint32_t reset_handler_addr = 0;
    pFunction app_entry          = 0;

    /* Stack address */
    stack_addr = *((uint32_t*)APP_START_ADDR);

    /* Reset handler address */
    reset_handler_addr = *((uint32_t*)(APP_START_ADDR + 4));

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



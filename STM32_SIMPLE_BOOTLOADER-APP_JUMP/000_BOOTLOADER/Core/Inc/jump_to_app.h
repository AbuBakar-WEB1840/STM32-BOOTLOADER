/*
 * jump_to_app.h
 *
 *  Created on: Sep 28, 2026
 *      Author: DELL
 */

#ifndef INC_JUMP_TO_APP_H_
#define INC_JUMP_TO_APP_H_

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
void jump_to_application(void);

#endif /* INC_JUMP_TO_APP_H_ */

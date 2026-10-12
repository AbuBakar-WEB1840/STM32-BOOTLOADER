/*
 * app_header.h
 *
 *  Created on: Sep 29, 2026
 *      Author: DELL
 */

#ifndef INC_APP_HEADER_H_
#define INC_APP_HEADER_H_

#include <stdio.h>
#include <stdio.h>

typedef struct
{
	uint32_t app_number;		/* Associated number with app */
	uint32_t crc;               /* CRC of firmware */
	uint32_t size;              /* Application size */
	uint32_t version;           /* Application version */
	uint32_t ota_flag;          /* OTA flag to verify */
}app_header_t;

#endif /* INC_APP_HEADER_H_ */

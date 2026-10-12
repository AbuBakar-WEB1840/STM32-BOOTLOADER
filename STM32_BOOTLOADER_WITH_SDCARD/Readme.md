# STM32F407 SD Card Bootloader

A simple STM32 bootloader that loads firmware from an SD card, programs the binary image into internal Flash memory, and transfers execution to the application.

This project uses the STM32F407VG microcontroller and STM32CubeIDE. It builds on the basic bootloader-to-application jump by adding SD card access, FatFs, Flash erase/program operations, and initial A/B application slot management.

## Project structure

```text
.
├── 000_BOOTLOADER/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── app_header.h
│   │   │   ├── crc32.h
│   │   │   ├── download_firmware.h
│   │   │   ├── flash_addresses.h
│   │   │   ├── flash_operations.h
│   │   │   ├── jump_to_app.h
│   │   │   └── sd_card.h
│   │   └── Src/
│   │       ├── crc32.c
│   │       ├── download_firmware.c
│   │       ├── flash_operations.c
│   │       ├── jump_to_app.c
│   │       ├── main.c
│   │       └── sd_card.c
│   ├── FATFS/
│   ├── Middlewares/
│   ├── Drivers/
│   └── STM32F407VGTX_FLASH.ld
│
├── 001_APP_LED_BLINK/
│   ├── Core/
│   ├── Drivers/
│   └── STM32F407VGTX_FLASH.ld
│
└── README.md
```

- **000_BOOTLOADER:** Handles SD card access, firmware loading, internal Flash programming, slot metadata, and application handover.
- **001_APP_LED_BLINK:** Provides a simple LED-blink application to test the firmware loading and handover process.

## Hardware and software

- **Microcontroller:** STM32F407VG
- **Board:** STM32F407 Discovery
- **IDE:** STM32CubeIDE
- **Drivers:** STM32 HAL and CMSIS
- **Filesystem:** FatFs
- **Storage:** SD card using SPI
- **Firmware format:** Raw binary (`.bin`)

## Flash memory layout

The STM32F407VG has 1 MB of internal Flash. The intended memory layout for this project is:

| Region | Start address | Flash sectors | Purpose |
|---|---|---|---|
| Bootloader | `0x08000000` | 0–3 | Bootloader firmware |
| Bootloader metadata | Reserved location to be finalized | Must not overlap the bootloader | Stores the active application slot |
| APP1 | `0x08020000` | 5–7 | Application slot 1 |
| APP2 | `0x08080000` | 8–11 | Application slot 2 |

The corresponding application addresses are:

```c
#define APP1_START_ADDR    0x08020000U
#define APP2_START_ADDR    0x08080000U
```

Each application must be linked to the address at which it will execute. Its vector table must be located at the beginning of its slot.

## How the bootloader works

### 1. Peripheral initialization

The bootloader initializes GPIO, SPI, and FatFs so it can communicate with the SD card.

### 2. Firmware loading

The bootloader mounts the SD card and opens the firmware file:

```text
001_APP_LED_BLINK.bin
```

FatFs reads the file in chunks using a buffer. The bootloader then programs the received bytes into internal Flash.

### 3. Flash erase and programming

Before writing the firmware, the required application sectors must be erased. The bootloader unlocks Flash, programs the binary, and locks Flash again after programming.

The target address determines where the application image is written. The erase operation must therefore use the sector range corresponding to that target slot.

### 4. Application slot selection

The project includes functions to read and update the active slot metadata:

- `bootloader_get_active_slot()`
- `bootloader_set_active_slot()`

The intended design uses APP1 and APP2 alternately. When one slot contains the active application, the other slot is the target for the next update.

The active slot should only change after the new image has been successfully written and validated. The current implementation still needs the complete slot-specific erase and validation logic.

### 5. Jump to application

The bootloader reads the application's initial stack pointer and reset handler from its vector table, disables interrupts, stops SysTick, sets the main stack pointer, and calls the reset handler.

The application is responsible for configuring its vector table and initializing its system and peripherals.

## Preparing the firmware

Build `001_APP_LED_BLINK` in STM32CubeIDE and generate a raw `.bin` file from the application ELF.

Make sure that:

- The application linker script uses the correct slot start address.
- The binary contains the application image, not the bootloader.
- The binary is copied to the SD card using the filename expected by the bootloader.
- The target slot has enough Flash capacity for the image.

A raw `.bin` file does not contain its own load address. The bootloader must know the correct destination address.

## Building the project

### Bootloader

1. Open `000_BOOTLOADER` in STM32CubeIDE.
2. Check the linker configuration and Flash memory definitions.
3. Build the project.

### Application

1. Open `001_APP_LED_BLINK` in STM32CubeIDE.
2. Set the application Flash origin to the desired slot address.
3. Build the project and generate the `.bin` file.
4. Copy the binary to the SD card.

## Flashing and testing

1. Connect the board through ST-LINK.
2. Program the bootloader using STM32CubeIDE or STM32CubeProgrammer.
3. Insert the SD card containing `001_APP_LED_BLINK.bin`.
4. Reset the board and observe the firmware loading process.
5. Verify that the application starts and the LED blinks.

Test the bootloader and application with the intended memory map. Do not test metadata updates until the sector erase configuration has been corrected.


## Future improvements

- Add CRC verification before activating a new image.
- Correct the Flash erase logic for each slot.
- Make active-slot metadata updates safe against power loss.
- Validate the application's stack pointer and reset handler.
- Add recovery behavior when an update fails.
- Test the A/B update sequence and fallback behavior systematically.


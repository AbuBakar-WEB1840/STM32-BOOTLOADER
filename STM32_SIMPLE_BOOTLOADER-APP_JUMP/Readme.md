# STM32F407 Simple Bootloader (Application Jump)

A simple STM32 bootloader that transfers execution from a bootloader to a separately built application stored in internal Flash memory.

This project uses an STM32F407VG based board, such as the **STM32F407G-DISC1 Discovery board**. The bootloader and application are developed as separate STM32CubeIDE projects and programmed into their respective Flash regions.

## Project structure

```text
.
├── 000_BOOTLOADER/
│   ├── Core/
│   │   ├── Inc/
│   │   └── Src/
│   ├── Drivers/
│   └── STM32F407VGTX_FLASH.ld
│
├── 001_APP_LED_BLINK/
│   ├── Core/
│   │   ├── Inc/
│   │   └── Src/
│   ├── Drivers/
│   └── STM32F407VGTX_FLASH.ld
│
└── README.md
```

- **000_BOOTLOADER:** Initializes the MCU and transfers execution to the application.
- **001_APP_LED_BLINK:** A simple LED blink application used to verify that the bootloader can successfully start another firmware image.

## Memory layout

The project uses the STM32F407VG's 1 MB internal Flash memory.

| Region | Start address | Size | Purpose |
|---|---|---|---|
| Sectors 0–3 | `0x08000000` | 64 KB | Bootloader |
| Sector 4 | `0x08010000` | 64 KB | Reserved for application metadata |
| Sector 5 onward | `0x08020000` | Remaining Flash | Application |

The main addresses are defined as follows in flash_addresses.h:

```c
#define BL_START_ADDR       0x08000000U
#define BL_APP_HEADER_ADDR  0x08010000U
#define APP_START_ADDR      0x08020000U
```

The application is linked to start at `0x08020000`. Its vector table is therefore located at this address rather than at the default Flash base address.

The bootloader and application must use their respective linker configurations to prevent their Flash regions from overlapping.

## How it works

1. The MCU starts executing the bootloader from `0x08000000`.
2. The bootloader initializes the system clock and GPIO.
3. The bootloader reads the application's initial stack pointer and reset handler from the application's vector table.
4. Interrupts are disabled and the SysTick timer is stopped.
5. The bootloader sets the application's stack pointer and transfers execution to its reset handler.
6. The application initializes HAL, sets `SCB->VTOR` to `APP_START_ADDR`, configures the system clock and initializes its peripherals.
7. The LED-blink application starts running.

If execution returns to the bootloader's main loop, the bootloader blinks the blue LED as a basic diagnostic indication.

## Building the project

Both projects can be built separately in STM32CubeIDE.

### 1. Build the bootloader

1. Open `000_BOOTLOADER` in STM32CubeIDE.
2. Verify that its linker script places the bootloader in the Flash region starting at `0x08000000`.
3. Build the project.

### 2. Build the application

1. Open `001_APP_LED_BLINK` in STM32CubeIDE.
2. Verify that its linker script sets the Flash origin to `0x08020000`.
3. Build the project.

The application's vector table and reset handler must be located at the application start address.

## Flashing and testing

1. Connect the STM32F407 Discovery board using ST-LINK.
2. Program the bootloader ELF using STM32CubeIDE or STM32CubeProgrammer.
3. Program the application ELF using the same tools. Because the application is linked to `0x08020000`, its load addresses must remain intact.
4. Reset the board and verify that the bootloader transfers execution to the LED-blink application.

**Important:** Do not program the application at `0x08000000`, because that would overwrite the bootloader region.

## Current scope

This project demonstrates the basic bootloader-to-application handover. It does not yet implement firmware updates, A/B slots, CRC validation, or recovery from an interrupted update.

## Tools 

- MCU: STM32F407VG
- Board: STM32F407 Discovery
- IDE: STM32CubeIDE
- Drivers: STM32 HAL and CMSIS
- Language: C
- Debugging/programming: ST-LINK


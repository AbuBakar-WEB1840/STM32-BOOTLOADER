# STM32 Bootloader Projects

STM32F407VG bootloader projects developed using STM32CubeIDE and the STM32 HAL.

## Projects

- **Simple Bootloader:** Transfers execution from the bootloader to an application stored at a separate Flash address.
- **SD Card Bootloader:** Loads firmware from an SD card and programs the STM32 internal Flash, with initial A/B application-slot support.

## Hardware & Tools

- **MCU:** STM32F407VG
- **IDE:** STM32CubeIDE
- **Framework:** STM32 HAL
- **Storage:** SD card with FatFs (second project)

Each project contains its own bootloader and application projects.

**Note:** These projects are for learning and experimentation. The SD-card bootloader still requires additional safeguards for reliable firmware updates.
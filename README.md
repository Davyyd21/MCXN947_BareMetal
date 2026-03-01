# MCXN947 Bare-Metal Development

This repository contains the foundational hardware abstraction files for the NXP MCX N947 microcontroller, specifically for the FRDM-MCXN947 development board. 

The goal of this project is to provide a clean, bare-metal starting point without the overhead of heavy SDKs, focusing on direct register access and hardware optimization.

## Key Features
- **Custom Startup**: A streamlined initialization process that handles the vector table, data relocation from Flash to RAM, and BSS clearing.
- **Optimized Performance**: Enables the LPCAC (Cache Controller) to ensure the processor runs at its full 150 MHz potential without being throttled by Flash latency.
- **Hardware Acceleration**: Unlocks the FPU and PowerQuad math co-processors immediately at boot.
- **Manual Memory Management**: Includes a custom linker script tailored to the 512KB SRAM and 2MB Flash layout of the MCXN947.

## Project Structure
- `startup.c`: Contains the interrupt vector table and the Reset_Handler logic.
- `linker_script.ld`: Defines the memory map and ensures proper section alignment.
- `main.c`: The entry point for your application code.
- `.vscode/c_cpp_properties.json`: Configuration for VS Code IntelliSense using the ARM GCC toolchain.

## Requirements
- **Toolchain**: `arm-none-eabi-gcc`
- **Hardware**: FRDM-MCXN947 Board
- **Debugger**: LinkServer

## How to use
1. Ensure your ARM GCC compiler path is correctly set in your environment variables or IDE settings.
2. The `Reset_Handler` will automatically initialize the system hardware before calling `main()`.
3. Use a Makefile or your preferred build system to link the files using the provided `linker_script.ld`.

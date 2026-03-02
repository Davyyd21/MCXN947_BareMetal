CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CPU = -DCPU_MCXN947VDF_cm33_core0
INCLUDES = -I"C:/Users/david21/OneDrive/Desktop/NXP_SDK/SDK_25_12_00_FRDM-MCXN947/devices/MCXN947" \
           -I"C:/Users/david21/OneDrive/Desktop/NXP_SDK/SDK_25_12_00_FRDM-MCXN947/CMSIS/Core/Include" \
           -I"C:/Users/david21/OneDrive/Desktop/NXP_SDK/SDK_25_12_00_FRDM-MCXN947/devices/MCXN947/periph" \
		   -I"C:/Users/david21/OneDrive/Desktop/NXP_SDK/SDK_25_12_00_FRDM-MCXN947/CMSIS" \
		   -I"C:/Users/david21/OneDrive/Desktop/NXP_SDK/SDK_25_12_00_FRDM-MCXN947/CMSIS/m-profile"

CFLAGS = -mcpu=cortex-m33 -mthumb -O0 -g3 -Wall $(CPU) $(INCLUDES)

LDFLAGS = -T linker_script.ld -nostdlib

all: final.bin

final.elf: main.c startup_mcxn947.c
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

final.bin: final.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.elf *.bin *.o
flash:
	LinkServer flash auto load final.elf
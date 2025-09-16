# Makefile for Raspberry Pi 3
# Updated by Wagner Morais Aug 22
# Modified for WSL compatibility

MAINFILE = a1p1

# Object files for Raspberry Pi (cross-compilation)
OBJS	=  lib/iregister.o 
OBJS	+= lib/uart.o lib/rpi-armtimer.o lib/rpi-gpio.o lib/rpi-interrupts.o lib/rpi-systimer.o 
OBJS	+= lib/startup.o lib/syscalls.o 
OBJS	+= $(MAINFILE).o

# Object files for local testing (WSL/Linux)
TEST_OBJS = lib/iregister.o $(MAINFILE).o

ELF		= $(MAINFILE).elf
MAIN	= $(MAINFILE).img
TEST_EXE = $(MAINFILE)_test

# Cross-compilation tools for Raspberry Pi
CROSS	= arm-none-eabi-
CC		= $(CROSS)gcc
AS		= $(CROSS)as
SIZE	= $(CROSS)size
OCOPY	= $(CROSS)objcopy

# Local compilation tools for testing
LOCAL_CC = gcc

# Cross-compilation flags for Raspberry Pi
# CFLAGS	= -march=armv8-a -mcpu=cortex-a53 -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib -DRPI3=1 -DIOBPLUS=1
CFLAGS	= -march=armv8-a+crc -mtune=cortex-a53 -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib -DRPI3=1 -DIOBPLUS=1

# Local compilation flags for testing
TEST_CFLAGS = -g -std=gnu99 -Wall -Wextra -O0 -Ilib

LFLAGS	= -static -nostartfiles -lc -lgcc -specs=nano.specs -Wl,--gc-sections -lm
LSCRIPT	= lib/rpi3.ld

LDFLAGS	+= -u _printf_float

.PHONY: all clean run test clean-test install-deps

# Default target - builds for Raspberry Pi
all: $(MAIN)

# Raspberry Pi cross-compilation rules
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(ELF): $(OBJS)
	$(CC) -T $(LSCRIPT) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@
	
$(MAIN): $(ELF)
	$(OCOPY) $< -O binary $@

# Local testing rules for WSL/Linux
lib/iregister_test.o: lib/iregister.c
	$(LOCAL_CC) $(TEST_CFLAGS) -c -o $@ $^

$(MAINFILE)_test.o: $(MAINFILE).c
	$(LOCAL_CC) $(TEST_CFLAGS) -c -o $@ $^

$(TEST_EXE): lib/iregister_test.o $(MAINFILE)_test.o
	$(LOCAL_CC) $(TEST_CFLAGS) -o $@ $^

# Test target - builds and runs locally
test: $(TEST_EXE)
	@echo "Running test program..."
	./$(TEST_EXE)

# Install dependencies for cross-compilation (if needed)
install-deps:
	@echo "Installing ARM cross-compilation tools..."
	sudo apt update
	sudo apt install -y gcc-arm-none-eabi

clean:
	@echo "Cleaning up..."
	rm -f $(MAIN) $(ELF) $(OBJS)

clean-test:
	@echo "Cleaning test files..."
	rm -f $(TEST_EXE) lib/iregister_test.o $(MAINFILE)_test.o

clean-all: clean clean-test

run: $(MAIN)
	@echo "Raspberry Pi image $(MAIN) built successfully!"
	@echo "Copy $(MAIN) to your Raspberry Pi to run it."

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build Raspberry Pi image (default)"
	@echo "  test         - Build and run test program locally in WSL"
	@echo "  clean        - Clean Raspberry Pi build files"
	@echo "  clean-test   - Clean test build files"
	@echo "  clean-all    - Clean all build files"
	@echo "  install-deps - Install ARM cross-compilation tools"
	@echo "  help         - Show this help message"

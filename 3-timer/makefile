TARGET = debug
CPU = cortex-m4

CFLAGS = -mcpu=$(CPU) -mthumb -Og -Wall -fdata-sections -ffunction-sections -g -gdwarf-2
LDFLAGS = -mcpu=$(CPU) -mthumb -specs=nano.specs -T./linker.ld -Wl,-Map=build/$(TARGET).map,--cref -Wl,--gc-sections
LIBS = -lc -lm -lnosys

CFILES = $(shell find . -name '*.c')
COBJECTS = $(patsubst %.c, %.o, $(CFILES))
AFILES = $(shell find . -name '*.s')
AOBJECTS = $(patsubst %.s, %.o, $(AFILES))


all: $(AOBJECTS) $(COBJECTS)
	mkdir -p build/
	arm-none-eabi-gcc $(AOBJECTS) $(COBJECTS) $(LIBS) $(LDFLAGS) -o build/$(TARGET).elf
	arm-none-eabi-objcopy -O binary -S build/$(TARGET).elf build/$(TARGET).bin
	arm-none-eabi-objcopy -O ihex build/$(TARGET).elf build/$(TARGET).hex

$(AOBJECTS): src/%.o : src/%.s
	arm-none-eabi-gcc -c $(CFLAGS) $< -o $@

$(COBJECTS): src/%.o : src/%.c
	arm-none-eabi-gcc -c $(CFLAGS) $< -o $@


flash: all
	st-flash write build/$(TARGET).bin 0x08000000


clean:
	rm -f $(COBJECTS)
	rm -f $(AOBJECTS)
	rm -rf build/

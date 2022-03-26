# Getting the onboard led to work

Copyright 2022  Jannik Kreucher

## Table Of Contents
  - [Talking to hardware registers](#talking-to-hardware-registers)
  - [The RCC Registers](#the-rcc-registers)
  - [The GPIO Registers](#the-gpio-registers)


## Talking to hardware registers

When working with microcontrollers we need to be able to read and write from and to hardware registers to configure the device. ST provides a [Reference Manual](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) where every register function is explained. When attempting to write your own hardware drivers this should be the first place to get your information. It is very important to read the manual thoroughly because small little details could make or break your code.

### Register Maps
The microcontrollers registers are gouped into functional blocks. The RCC registers in which we will look into in a little bit, control as the name might imply reset and clock functions. Every register in a STM32 is in RAM on a specific address. These address locations are 32 bit wide each. Creating a register map should be pretty straight forward.
```c
typedef struct {
	uint32_t register1;
	uint32_t register2;
} REGISTER_t;
```
### Assigning an address
But how do we assign this struct to a specific RAM address you might ask? To do that we generate a pointer to the hardware address with the struct a data type.
```c
volatile REGISTER_t* reg = (REGISTER_t*)0x12345678;
```
The keyword `volatile` is very important here. Leaving it out can cause your perfectly fine code not to work. It tells the compiler that the address locations the pointer `reg` is pointing at can be changed externally, in our case the hardware. This gets really important when reading flags that are set/reset by hardware.


## The RCC registers

The RCC (Reset and Clock Control) register is one if not the most important register. It controls the clock souce, clock dividers, clock enable signals for each peripheral and the pll clock muliplier. Forgetting to enable the peripheral you want to work with leads it to be inactive. The register map can be found in the ST provided reference manual on page 136. With this map the rcc register structure can be implemented. See [rcc.h](src/drivers/rcc.h) for detailed information. The microcontroller runs on its internal 16MHz clock by default. To drive the LED the GPIO port C needs to be anabled. The other configurations are kept as default.


## The GPIO registers

The GPIO (General Purpose Input Output) registers control the behaviour of the I/O ports. See [gpio.h](src/drivers/gpio.h) for the GPIO register map. Use the function `gpio_mode(port, pin, mode)` to configure a GPIO pin. The argument `port` can be any of GPIOA, GPIOB or GPIOC. Any GPIO pin can be configured as Input or Output with different functions like open drain output, pull up or pull down resistor. Most pins can be used with an alternate function like SPI bus signals. To configure the alternate function use `void gpio_alt(port, pin, alt_func)` where alt_func is the number of the alternate function described in STs [datasheet](https://www.st.com/resource/en/datasheet/stm32f411ce.pdf).
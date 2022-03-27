# Building a delay function

Copyright 2022  Jannik Kreucher

## Table Of Contents
  - [The Systick Timer](#the-systick-timer)


## The Systick Timer

The systick timer is a simple counter that counts down from a preset value. When reaching 0 the timer issues a system interrupt and the reload value gets loaded into the counter again. The interrupt vector is defined in [startup.s](src/startup.s) as `SysTick_Handler`. This function gets called when the counter reaches zero. The clock source is the AHB clock divides by 8. With the internal HSI clock the systick counts down with 2MHz. When using a reaload value of 2000 the timer generates an interrupt every millisecond. This behaviour makes it pretty straight forward to implement a fairly accurate delay function. For more information look into the [Programming Manual](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf) starting at page 246.

### This might me interesting
The global variable `systick_ticks` in [systick.c](src/drivers/systick.c) has to be defined as volatile as it can be changed by an interrupt. Letting the compiler know the variable can change at any moment by an interupt is crucial for compiler optimization. Then not using `volatile` the compiler would optimize the `start` variable in `delay(time)`. This would break the delay function since the compiler would not expect `systick_ticks` to change at this point.
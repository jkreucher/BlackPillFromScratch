#include "rcc.h"

void rcc_init() {
	// puts rcc struct to the right place
	// "volatile" tells the compiler that rcc can be changed by hardware
	volatile RCC_t* rcc = (RCC_t*)ADDR_BASE_RCC;
	// enable all gpio ports
	rcc->ahb1enr |= RCC_EN_GPIOA | RCC_EN_GPIOB | RCC_EN_GPIOC;
	// enable power control
	rcc->ahb1enr |= RCC_EN_POWER;
	// enable timer
	rcc->apb1enr |= RCC_EN_TIM2;
	rcc->apb2enr |= RCC_EN_TIM1;
}
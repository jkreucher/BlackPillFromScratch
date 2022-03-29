#include "rcc.h"

void rcc_init() {
	// puts rcc struct to the right place
	// "volatile" tells the compiler that rcc can be changed by hardware
	volatile RCC_t* rcc = (RCC_t*)ADDR_BASE_RCC;
	
	// enable external 25MHz clock
	rcc->cr |= (1 << 16);
	// wait for HSE ready
	while(!(rcc->cr & (1 << 17)));
	// PLL input devision: input needs to be between 1 and 2 MHz
	rcc->pllcfgr |= (25 << 0);
	// PLL multiplication: output needs to be between 100 and 432MHz
	rcc->pllcfgr |= (200 << 6);
	// PLL divider for main clock: pll/2
	rcc->pllcfgr |= (0 << 16);
	// PLL clock source: HSE
	rcc->pllcfgr |= (1 << 22);
	// PLL USB/SDIO divider
	rcc->pllcfgr |= (3 << 24);
	// enable pll
	rcc->cr |= (1 << 24);
	// wait for pll
	while(!(rcc->cr & (1 << 25)));

	// AHB prescaler - divide by 1
	rcc->cfgr |= (0b0000 << 4);
	// APB1 (low speed, max 50MHz) - divide AHB by 4
	rcc->cfgr |= (0b101 << 10);
	// APB2 (high speed, max 100MHz) - divide AHB by 2
	rcc->cfgr |= (0b100 << 13);
	// RTC clock: HSE/25 = 1MHz
	rcc->cfgr |= (25 << 16);

	// change flash latency
	flash_init();

	// switch system clock to pll
	rcc->cfgr |= (0b10 << 0);
	// wait for clock source to be pll
	while(!(rcc->cfgr & (0b10 << 2)));
	
	// enable all gpio ports
	rcc->ahb1enr |= RCC_EN_GPIOA | RCC_EN_GPIOB | RCC_EN_GPIOC;
	// enable power control
	rcc->ahb1enr |= RCC_EN_POWER;
	// enable timer
	rcc->apb1enr |= RCC_EN_TIM2;
	rcc->apb2enr |= RCC_EN_TIM1;
}

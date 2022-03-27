#include "systick.h"

// volatile is important here because systick_ticks can be changed by an isr
volatile uint32_t systick_ticks;


void systick_init(uint32_t load_val) {
	volatile SYSTICK_t* systick = (SYSTICK_t*)ADDR_BASE_TICK;
	// set top value
	systick->load = load_val - 1;
	// reset value
	systick->val = 0;
	// enable systick: enable, enable int, ahb/8
	systick->ctrl = (1 << 0) | (1 << 1) | (0 << 2);
	// reset systick ticks
	systick_ticks = 0;
}


uint32_t systick_get() {
	// just return the current ticks
	return systick_ticks;
}


void SysTick_Handler() {
	// increment ticks when interrupt occoured
	systick_ticks++;
}


void delay(uint32_t time) {
	uint32_t start = systick_ticks;
	while(systick_ticks-start < time);
}
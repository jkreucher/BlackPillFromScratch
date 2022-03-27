#include "timer.h"

// timers
volatile TIMER_t* TIMER1 = (TIMER_t*)ADDR_BASE_TIM1;
volatile TIMER_t* TIMER2 = (TIMER_t*)ADDR_BASE_TIM2;
volatile TIMER_t* TIMER3 = (TIMER_t*)ADDR_BASE_TIM3;
volatile TIMER_t* TIMER4 = (TIMER_t*)ADDR_BASE_TIM4;
volatile TIMER_t* TIMER5 = (TIMER_t*)ADDR_BASE_TIM5;


void timer_init(volatile TIMER_t* timer, uint16_t prescaler, uint16_t period, uint8_t interrupt) {
	// set prescaler
	timer->psc = prescaler - 1;
	// set period: update when counter reaches this number
	timer->arr = period - 1;
	// check if interrupt needs to be enabled
	if(interrupt > 0) {
		// enable overflow interrupt
		timer->dier = 0x01;
		// register interrupt in nvic controller
		nvic_enable(interrupt);
	}
	// enable timer
	timer->cr1 = 0x01;
}


uint16_t timer_get_count(volatile TIMER_t* timer) {
	// return current timer value
	return timer->cnt;
}


void timer_init_channel(volatile TIMER_t* timer, uint8_t channel, uint8_t mode, uint8_t dead_time) {
	// turn channel off
	timer->ccer = timer->ccer & ~(0xF << (channel-1)*4);
	// set channel mode (only writeable when channel is off)
	// configure as output, perload enable
	uint8_t config = ((mode & 0x0F) << 4) | 0b1000;
	if(channel <= 2) {
		timer->ccmr1 = (config << ((channel-1)*8)) | (timer->ccmr1 & ~(0xFF << ((channel-1)*8)));
	} else {
		timer->ccmr2 = (config << ((channel-3)*8)) | (timer->ccmr1 & ~(0xFF << ((channel-3)*8)));
	}
	// configure optional dead time (availabe on timer 1 only)
	timer->bdtr = dead_time | (0b1 << 15);
	// turn channel on (CCxE active high, CCxNE active high)
	timer->ccer |= ((mode >> 4) << (channel-1)*4);
}


void timer_set_channel(volatile TIMER_t* timer, uint8_t channel, uint16_t value) {
	// load value in preload register
	timer->ccr[channel-1] = value;
}
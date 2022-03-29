#include "timer.h"

// timers
volatile TIMER_t* TIMERS[] = {
	(TIMER_t*)ADDR_BASE_TIM1,
	(TIMER_t*)ADDR_BASE_TIM2,
	(TIMER_t*)ADDR_BASE_TIM3,
	(TIMER_t*)ADDR_BASE_TIM4,
	(TIMER_t*)ADDR_BASE_TIM5
};

// ISR jump table
void (*TIMER_HANDLERS[4])(volatile TIMER_t*);


void timer_init(uint8_t timer, uint16_t prescaler, uint16_t period) {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[timer];
	// all channels off
	tim->ccer = 0;
	// set prescaler
	tim->psc = prescaler - 1;
	// set period: update when counter reaches this number
	tim->arr = period - 1;
	// enable timer
	tim->cr1 = 0x01;
}


void timer_init_int(uint8_t timer, void (*handler)) {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[timer];
	// enable overflow interrupt
	tim->dier |= 0b1;
	// register in nvic
	switch (timer) {
		case TIMER1:
			nvic_enable(INT_POS_TIM1_UP);
			break;
		case TIMER2:
			nvic_enable(INT_POS_TIM2);
			break;
		case TIMER3:
			nvic_enable(INT_POS_TIM3);
			break;
		case TIMER4:
			nvic_enable(INT_POS_TIM4);
			break;
		default:
			break;
	}
	// save isr pointer in jump table
	TIMER_HANDLERS[timer] = handler;
}


uint16_t timer_get_count(uint8_t timer) {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[timer];
	// return current timer value
	return tim->cnt;
}


void timer_channel_init(uint8_t timer, uint8_t channel, uint8_t mode, uint8_t dead_time) {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[timer];
	// turn channel off
	tim->ccer = tim->ccer & ~(0xF << (channel-1)*4);
	// set channel mode (only writeable when channel is off)
	// configure as output, perload enable
	uint8_t config = ((mode & 0x0F) << 4) | 0b1000;
	if(channel <= 2) {
		tim->ccmr1 = (config << ((channel-1)*8)) | (tim->ccmr1 & ~(0xFF << ((channel-1)*8)));
	} else {
		tim->ccmr2 = (config << ((channel-3)*8)) | (tim->ccmr1 & ~(0xFF << ((channel-3)*8)));
	}
	// configure optional dead time (availabe on tim 1 only)
	tim->bdtr = dead_time | (0b1 << 15);
	// turn channel on (CCxE active high, CCxNE active high)
	tim->ccer |= ((mode >> 4) << (channel-1)*4);
}


void timer_channel_set(uint8_t timer, uint8_t channel, uint16_t value) {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[timer];
	// load value in preload register
	tim->ccr[channel-1] = value;
}




// Timer 1 ISR
void TIM1_UP_TIM10_IRQHandler() {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[TIMER1];
	// check if update interrupt
	if(tim->sr & 0b1) {
		// check if isr is in jump table
		if(TIMER_HANDLERS[TIMER1]) {
			(*TIMER_HANDLERS[TIMER1])(tim);
		}
	}
	// clear status
	tim->sr = 0;
}

// Timer 2 ISR
void TIM2_IRQHandler() {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[TIMER2];
	// check if update interrupt
	if(tim->sr & 0b1) {
		// check if isr is in jump table
		if(TIMER_HANDLERS[TIMER2]) {
			(*TIMER_HANDLERS[TIMER2])(tim);
		}
	}
	// clear status
	tim->sr = 0;
}

// Timer 3 ISR
void TIM3_IRQHandler() {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[TIMER3];
	// check if update interrupt
	if(tim->sr & 0b1) {
		// check if isr is in jump table
		if(TIMER_HANDLERS[TIMER3]) {
			(*TIMER_HANDLERS[TIMER3])(tim);
		}
	}
	// clear status
	tim->sr = 0;
}

// Timer 4 ISR
void TIM4_IRQHandler() {
	// timer pointer
	volatile TIMER_t* tim = TIMERS[TIMER4];
	// check if update interrupt
	if(tim->sr & 0b1) {
		// check if isr is in jump table
		if(TIMER_HANDLERS[TIMER4]) {
			(*TIMER_HANDLERS[TIMER4])(tim);
		}
	}
	// clear status
	tim->sr = 0;
}
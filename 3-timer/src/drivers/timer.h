#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#include "stm32f4.h"
#include "nvic.h"
#include "gpio.h"


// Timers
#define TIMER1	0
#define TIMER2	1
#define TIMER3	2
#define TIMER4	3
#define TIMER5	4
// Timer modes
#define TIMER_MODE_TOGGLE		0b00010011
#define TIMER_MODE_PWM			0b00010110
#define TIMER_MODE_TOGGLE_NEG	0b01010011
#define TIMER_MODE_PWM_NEG		0b01010110


// TIMER REGISTER MAP
typedef struct {
	uint32_t cr1;		// 0x00 - control register 1
	uint32_t cr2;		// 0x04 - control register 2
	uint32_t smcr;		// 0x08 - slave mode control register
	uint32_t dier;		// 0x0C - dma/interrupt enable register
	uint32_t sr;		// 0x10 - status register
	uint32_t egr;		// 0x14 - event generation register
	uint32_t ccmr1;		// 0x18 - capture/compare mode register 1
	uint32_t ccmr2;		// 0x1C - capture/compare mode register 2
	uint32_t ccer;		// 0x20 - cpature/compare enable register
	uint32_t cnt;		// 0x24 - counter
	uint32_t psc;		// 0x28 - prescaler
	uint32_t arr;		// 0x2C - auto-reload register
	uint32_t rcr;		// 0x30 - repetition counter register
	uint32_t ccr[4];	// 0x34-0x40 - cpature/compare registers
	uint32_t bdtr;		// 0x44 - break and dead-time register
	uint32_t dcr;		// 0x48 - dma control register
	uint32_t dmar;		// 0x4C - dma address for full transfer
} TIMER_t;


// public functions
void timer_init(uint8_t timer, uint16_t prescaler, uint16_t period);
void timer_init_int(uint8_t timer, void (*handler));
uint16_t timer_get_count(uint8_t timer);
void timer_channel_init(uint8_t timer, uint8_t channel, uint8_t mode, uint8_t dead_time);
void timer_channel_set(uint8_t timer, uint8_t channel, uint16_t value);


#endif
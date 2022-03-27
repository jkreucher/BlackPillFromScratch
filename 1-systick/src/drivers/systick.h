#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

#include "stm32f4.h"


// SYSTICK REGISTER MAP
typedef struct {
	uint32_t ctrl;	// 0x00 - control and status register
	uint32_t load;	// 0x04 - reload value register
	uint32_t val;	// 0x08 - current value register
	uint32_t calib;	// 0x0C - calibration value register
} SYSTICK_t;


// global functions
void systick_init(uint32_t divider);
uint32_t systick_get();
void delay(uint32_t time);

// ISR
void SysTick_Handler();


#endif
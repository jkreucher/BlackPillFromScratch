#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>

#include "stm32f4.h"


// NVIC REGISTER MAP
typedef struct {
	uint32_t iser[8];		// 0x00-0x1C - set-enable registers
	uint32_t rsvd1[24];		// 0x20-0x7C - reserved
	uint32_t icer[8];		// 0x80-0x9C - clear-enable registers
} NVIC_t;


// global functions
void nvic_enable(uint8_t int_pos);
void nvic_disable(uint8_t int_pos);


#endif
#include "nvic.h"

void nvic_enable(uint8_t int_pos) {
	volatile NVIC_t* nvic = (NVIC_t*)ADDR_BASE_NVIC;
	// calculare index and bit shift
	uint8_t index = int_pos / 32;
	uint8_t shift = int_pos % 32;
	// write a 1 to enable the interrupt
	nvic->iser[index] = (1 << shift);
}


void nvic_disable(uint8_t int_pos) {
	volatile NVIC_t* nvic = (NVIC_t*)ADDR_BASE_NVIC;
	// calculare index and bit shift
	uint8_t index = int_pos / 32;
	uint8_t shift = int_pos % 32;
	// write a 1 to disable the interrupt
	nvic->icer[index] = (1 << shift);
}
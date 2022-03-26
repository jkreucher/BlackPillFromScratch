#include "rcc.h"

void rcc_init() {
	// puts rcc struct to the right place
	// "volatile" tells the compiler that rcc can be changed by hardware
	volatile RCC_t* rcc = (RCC_t*)ADDR_BASE_RCC;

}
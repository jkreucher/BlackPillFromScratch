#include "flash.h"


void flash_init() {
	volatile FLASH_t* flash = (FLASH_t*)ADDR_BASE_FLASH;
	// enable prefetch, instruction cache, data cache
	flash->acr |= (1 << 8) | (1 << 9) | (1 << 10);
	// change latency
	#if CLOCK_SYS > 90000000
		// 3 wait states
		flash->acr |= (3 << 0);
	#elif CLOCK_SYS > 64000000
		// 2 wait states
		flash->acr |= (2 << 0);
	#elif CLOCK_SYS > 30000000
		// 1 wait state
		flash->acr |= (1 << 0);
	#else
		// 0 wait states
		flash->acr |= (0 << 0);
	#endif
}
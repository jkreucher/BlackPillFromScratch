#include "flash.h"

void flash_init() {
	volatile FLASH_t* flash = (FLASH_t*)ADDR_BASE_FLASH;
	// enable prefetch, instruction cache, data cache
	flash->acr |= (1 << 8) | (1 << 9) | (1 << 10);
	// change latency to work at 100MHz: 3WS
	flash->acr |= (3 << 0);
}
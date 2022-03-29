#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>

#include "stm32f4.h"


// FLASH REGISTER MAP
// see reference manual at page 66
typedef struct {
	uint32_t acr;		// 0x00 - access control register
	uint32_t keyr;		// 0x04 - key register
	uint32_t optkey;	// 0x08 - option key register
	uint32_t sr;		// 0x0C - status register
	uint32_t cr;		// 0x10 - control register
	uint32_t optcr;		// 0x14 - option control register
} FLASH_t;


// public functions
void flash_init();

#endif
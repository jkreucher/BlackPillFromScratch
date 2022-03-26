#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>

#include "stm32f4.h"


// Enable Defines
#define RCC_EN_GPIOA	(1 << 0)	// ahb1
#define RCC_EN_GPIOB	(1 << 1)	// ahb1
#define RCC_EN_GPIOC	(1 << 2)	// ahb1
#define RCC_EN_POWER	(1 << 28)	// ahb1


// RCC REGISTER MAP
// see Reference Manual on page 136
typedef struct {
	uint32_t cr;		// 0x00 - control register
	uint32_t pllcfgr;	// 0x04 - pll configuration register
	uint32_t cfgr;		// 0x08 - clock configuration register
	uint32_t cir;		// 0x0C - clock interrupt register
	uint32_t ahb1rstr;	// 0x10 - ahb1 peripheral reset register
	uint32_t ahb2rstr;	// 0x14 - ahb2 peripheral reset register
	uint32_t reserved1;	// 0x18 - reserved
	uint32_t reserved2;	// 0x1C - reserved
	uint32_t apb1rstr;	// 0x20 - apb1 peripheral reset register
	uint32_t apb2rstr;	// 0x24 - apb2 peripheral reset register
	uint32_t reserved3;	// 0x28 - reserved
	uint32_t reserved4;	// 0x2C - reserved
	uint32_t ahb1enr;	// 0x30 - ahb1 peripheral clock enable register
	uint32_t ahb2enr;	// 0x34 - ahb2 peripheral clock enable register
	uint32_t reserved5;	// 0x38 - reserved
	uint32_t reserved6;	// 0x3C - reserved
	uint32_t apb1enr;	// 0x40 - apb1 peripheral clock enable register
	uint32_t apb2enr;	// 0x44 - apb2 peripheral clock enable register
	uint32_t reserved7;	// 0x48 - reserved
	uint32_t reserved8;	// 0x4C	- reserved
	uint32_t ahb1lpenr;	// 0x50 - ahb1 peripheral clock enable in LP mode
	uint32_t ahb2lpenr;	// 0x54 - ahb2 peripheral clock enable in LP mode
	uint32_t reserved9;	// 0x58 - reserved
	uint32_t reserved10;// 0x5C	- reserved
	uint32_t apb1lpenr;	// 0x60 - apb1 peripheral clock enable in LP mode
	uint32_t apb2lpent;	// 0x64 - apb2 peripheral clock enable in LP mode
	uint32_t reserved11;// 0x68	- reserved
	uint32_t reserved12;// 0x6C	- reserved
	uint32_t bdcr;		// 0x70 - backup domain control register
	uint32_t csr;		// 0x74 - clock control & status register
	uint32_t reserved13;// 0x78	- reserved
	uint32_t reserved14;// 0x7C	- reserved
	uint32_t sscgr;		// 0x80 - spread spectrum clock generation register
	uint32_t plli2scfgr;// 0x84 - PLL I2S configuration register
	uint32_t reserved15;// 0x88	- reserved
	uint32_t dckcfgr;	// 0x8C - dedicated clocks configuration register
} RCC_t;


// public functions
void rcc_init();


#endif
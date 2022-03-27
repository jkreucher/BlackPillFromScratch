#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#include "stm32f4.h"


// GPIO FUNCTION DEFINES
// 0b 00 00 00  (pull type mode)
#define GPIO_INPUT		0b000000
#define GPIO_IN_UP		0b010000
#define GPIO_IN_DWN		0b100000
#define GPIO_OUT		0b000001
#define GPIO_OUT_OD		0b000101
#define GPIO_ANALOG		0b000011
#define GPIO_ALT		0b000010
#define GPIO_ALT_OD		0b000110


// GPIO REGISTER MAP
// see Reference Manual on page 163
typedef struct {
	uint32_t moder;	// 0x00 - port mode register
	uint32_t type;	// 0x04 - port output type register
	uint32_t speed;	// 0x08 - port output speed register
	uint32_t pull;	// 0x0C - port pull-up/pull-down register
	uint32_t idr;	// 0x10 - port input data register
	uint32_t odr;	// 0x14 - port output data register
	uint32_t srr;	// 0x18 - port bit set/reset register
	uint32_t lckr;	// 0x1C - port configuration lock register
	uint32_t afrl;	// 0x20 - alternate function low register
	uint32_t afrh;	// 0x24 - alternate function high register
} GPIO_t;


// gpio ports for global use
extern volatile GPIO_t* GPIOA;
extern volatile GPIO_t* GPIOB;
extern volatile GPIO_t* GPIOC;

// public functions
void gpio_mode(volatile GPIO_t* port, uint8_t pin, uint8_t mode);
void gpio_alt(volatile GPIO_t* port, uint8_t pin, uint8_t alt_func);
void gpio_write(volatile GPIO_t* port, uint8_t pin, uint8_t state);
uint8_t gpio_read(volatile GPIO_t* port, uint8_t pin);

#endif
#include "gpio.h"

volatile GPIO_t* GPIOA = (GPIO_t*)ADDR_BASE_GPIOA;
volatile GPIO_t* GPIOB = (GPIO_t*)ADDR_BASE_GPIOB;
volatile GPIO_t* GPIOC = (GPIO_t*)ADDR_BASE_GPIOC;


void gpio_mode(volatile GPIO_t* port, uint8_t pin, uint8_t mode) {
	// write port mode
	port->moder = (port->moder & ~(0b11 << pin*2)) | ((mode & 0b11) << pin*2);
	// write output type
	port->type = (port->type & ~(1 << pin)) | (((mode & 0b100) >> 2) << pin);
	// write gpio speed (high speed)
	port->speed = (0b11 << pin*2);
	// write pull-up / pull-down
	port->pull = (port->pull & ~(0b11 << pin*2)) | (mode >> 4) << pin*2;
}


void gpio_alt(volatile GPIO_t* port, uint8_t pin, uint8_t alt_func) {
	if(pin < 8) {
		port->afrl = (port->afrl & ~(0b1111 << pin*4)) | (alt_func << pin*4);
	} else {
		port->afrh = (port->afrh & ~(0b1111 << (pin-8)*4)) | (alt_func << (pin-8)*4);
	}
}


void gpio_write(volatile GPIO_t* port, uint8_t pin, uint8_t state) {
	port->odr = (port->odr & ~(1 << pin)) | (state & 0b1) << pin;
}


uint8_t gpio_read(volatile GPIO_t* port, uint8_t pin) {
	return (port->idr & (0b1 << pin)) >> pin;
}
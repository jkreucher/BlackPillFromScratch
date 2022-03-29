#include "gpio.h"


volatile GPIO_t* GPIOS[] = {
	(GPIO_t*)ADDR_BASE_GPIOA,
	(GPIO_t*)ADDR_BASE_GPIOB,
	(GPIO_t*)ADDR_BASE_GPIOC
};


void gpio_mode(uint8_t port, uint8_t pin, uint8_t mode) {
	// get port pointer from port number
	volatile GPIO_t* gpio = GPIOS[port];
	// write port mode
	gpio->moder = (gpio->moder & ~(0b11 << pin*2)) | ((mode & 0b11) << pin*2);
	// write output type
	gpio->type = (gpio->type & ~(1 << pin)) | (((mode & 0b100) >> 2) << pin);
	// write gpio speed (high speed)
	gpio->speed = (0b11 << pin*2);
	// write pull-up / pull-down
	gpio->pull = (gpio->pull & ~(0b11 << pin*2)) | (mode >> 4) << pin*2;
}


void gpio_alt(uint8_t port, uint8_t pin, uint8_t alt_func) {
	// get port pointer from port number
	volatile GPIO_t* gpio = GPIOS[port];
	// write alternate function
	if(pin < 8) {
		gpio->afrl = (gpio->afrl & ~(0b1111 << pin*4)) | (alt_func << pin*4);
	} else {
		gpio->afrh = (gpio->afrh & ~(0b1111 << (pin-8)*4)) | (alt_func << (pin-8)*4);
	}
}


void gpio_write(uint8_t port, uint8_t pin, uint8_t state) {
	// get port pointer from port number
	volatile GPIO_t* gpio = GPIOS[port];
	// 
	gpio->odr = (gpio->odr & ~(1 << pin)) | (state & 0b1) << pin;
}


uint8_t gpio_read(uint8_t port, uint8_t pin) {
	// get port pointer from port number
	volatile GPIO_t* gpio = GPIOS[port];
	// return bit
	return (gpio->idr & (0b1 << pin)) >> pin;
}
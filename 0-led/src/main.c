#include "drivers/rcc.h"
#include "drivers/gpio.h"

int main() {
	// initialize everything we need
	rcc_init();
	// set built-in led to output push-pull
	gpio_mode(GPIOC, 13, GPIO_OUT_PP);
	// set built-in key to input pull-up
	gpio_mode(GPIOA, 0, GPIO_IN_UP);

	// main loop
	while(1) {
		if(gpio_read(GPIOA, 0)) {
			gpio_write(GPIOC, 13, 0);
		} else {
			gpio_write(GPIOC, 13, 1);
		}
	}
	
	// lets hope we dont get here...
	return 0;
}

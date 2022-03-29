#include "drivers/rcc.h"
#include "drivers/gpio.h"
#include "drivers/systick.h"

int main() {
	// initialize everything we need
	rcc_init();
	systick_init();
	// set built-in led to output push-pull
	gpio_mode(GPIOC, 13, GPIO_OUT);
	
	// main loop
	while(1) {
		gpio_write(GPIOC, 13, 1);
		delay(500);
		gpio_write(GPIOC, 13, 0);
		delay(500);
	}
	
	// lets hope we dont get here...
	return 0;
}
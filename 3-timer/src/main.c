#include "drivers/rcc.h"
#include "drivers/gpio.h"
#include "drivers/systick.h"
#include "drivers/timer.h"


// prototypes
void toggleLed();


int main() {
	// initialize everything we need
	// make sure timer are enabled in rcc_init()
	rcc_init();
	systick_init();

	// set built-in led to output push-pull
	gpio_mode(GPIOC, 13, GPIO_OUT);
	
	// set PA8 to alternate functon 1 (Timer 1 CC1)
	// see datasheet on page 47 for alternate function mapping
	gpio_mode(GPIOA, 8, GPIO_ALT);
	gpio_alt(GPIOA, 8, 1);
	// set PB13 to alternate function 1 (Timer 1 CC1NE)
	gpio_mode(GPIOB, 13, GPIO_ALT);
	gpio_alt(GPIOB, 13, 1);

	// init timer 1 as pwm output (output at PA8)
	// set up pwm mode with positive and negative output with dead-time
	timer_init(TIMER1, 1, 1024);
	timer_channel_init(TIMER1, 1, TIMER_MODE_PWM_NEG, 20);

	// init timer 2 with interrupt (executes toggleLed at update event)
	// divide system clock by 50000 -> 2kHz, update event when reaching 1000
	timer_init(TIMER2, 50000, 1000);
	timer_init_int(TIMER2, toggleLed);
	
	// main loop - modulate pwm signal
	while(1) {
		// count up and set pwm duty
		for(int i=0; i<256; i++) {
			timer_channel_set(TIMER1, 1, i<<2);
			delay(10);
		}
		// count down and set pwm duty
		for(int i=255; i>0; i--) {
			timer_channel_set(TIMER1, 1, i<<2);
			delay(10);
		}
	}
	
	// lets hope we dont get here...
	return 0;
}


void toggleLed() {
	// toggle led
	uint8_t status = gpio_read(GPIOC, 13);
	gpio_write(GPIOC, 13, !status);
}
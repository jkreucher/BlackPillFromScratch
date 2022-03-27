#include "drivers/rcc.h"
#include "drivers/gpio.h"
#include "drivers/systick.h"
#include "drivers/timer.h"

int main() {
	// initialize everything we need
	// make sure timer are enabled in rcc_init()
	rcc_init();
	systick_init(2000);

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
	timer_init(TIMER1, 1, 256, 0);
	timer_init_channel(TIMER1, 1, TIMER_MODE_PWM_NEG, 10);

	// init timer 2 as timer interrupt
	// divide system clock by 16000, update event when reaching 500
	timer_init(TIMER2, 16000, 500, INT_POS_TIM2);
	
	// main loop - modulate pwm signal
	while(1) {
		// count up and set pwm duty
		for(int i=0; i<256; i++) {
			timer_set_channel(TIMER1, 1, i);
			delay(10);
		}
		// count down and set pwm duty
		for(int i=255; i>0; i--) {
			timer_set_channel(TIMER1, 1, i);
			delay(10);
		}
	}
	
	// lets hope we dont get here...
	return 0;
}


// Timer 2 ISR (vector specified in startup.s)
void TIM2_IRQHandler() {
	// toggle led
	uint8_t status = gpio_read(GPIOC, 13);
	gpio_write(GPIOC, 13, !status);
	// clear status
	TIMER2->sr = 0;
}
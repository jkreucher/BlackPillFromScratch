#ifndef STM32F4_H_
#define STM32F4_H_

// Clock Frequencies
#define CLOCK_SYS	100000000U
#define CLOCK_AHB	100000000U
#define CLOCK_APB1	25000000U
#define CLOCK_APB2	50000000U


// Register Addresses
#define ADDR_BASE_NVIC	0xE000E100U
#define ADDR_BASE_TICK	0xE000E010U
#define ADDR_BASE_FLASH	0x40023C00U
#define ADDR_BASE_RCC	0x40023800U
#define ADDR_BASE_GPIOC	0x40020800U
#define ADDR_BASE_GPIOB	0x40020400U
#define ADDR_BASE_GPIOA	0x40020000U
#define ADDR_BASE_TIM1	0x40010000U
#define ADDR_BASE_TIM5	0x40000C00U
#define ADDR_BASE_TIM4	0x40000800U
#define ADDR_BASE_TIM3	0x40000400U
#define ADDR_BASE_TIM2	0x40000000U


// Interrupt Positions
#define INT_POS_TIM1_UP		25	// TIM1 update
#define INT_POS_TIM1_TG		26	// TIM1 trigger
#define INT_POS_TIM1_CC		27	// TIM1 capture compare
#define INT_POS_TIM2		28	// TIM2 global interrupt
#define INT_POS_TIM3		29	// TIM3 global interrupt
#define INT_POS_TIM4		30	// TIM4 global interrupt


#endif
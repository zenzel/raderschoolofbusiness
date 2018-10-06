/*
 * File: GPIO_driver.c
 * Written by: Eli Zenz <zenze@msoe.edu>
 * Updated on: 17 December 2016
 * Source file to initialize and drive most of the
 * GPIO functions on the development board.
 * Updated as need.
 */

#include <stdio.h>
#include <timers.h>
#include "GPIO_driver.h"

/*
 * Enables the clock for a given source GPIOx.
 */
void clock_init(uint8_t source) {
	switch(source) {
	case GPIOA:
		*(RCC_AHB1ENR) |= (1<<GPIOA);
		break;
	case GPIOB:
		*(RCC_AHB1ENR) |= (1<<GPIOB);
		break;
	case GPIOC:
		*(RCC_AHB1ENR) |= (1<<GPIOC);
		break;
	case TIMER2:
		*(RCC_APB1ENR) |= (1<<0);
		break;
	case TIMER3:
		*(RCC_APB1ENR) |= (1<<1);
		break;
	case TIMER4:
		*(RCC_APB1ENR) |= (1<<2);
		break;
	}
}

/*
 * Selects the specified mode for the specified pin at the given
 * MODER address. Accepts a mode and a pin number (shift amount).
 */
void mode_select(volatile uint32_t* adr, uint8_t mode, uint16_t pin) {
	//Clears the two bits at the shift amount, then sets those bits
	//to their give mode
	*(adr) |= (((*(adr) &= (~(0b00<<(pin*2))))) | (mode<<(pin*2)));
}

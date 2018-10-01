/*
 * timer_12.c
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#include "timer_12.h"
#include "GPIO_driver.h"

void timer_12_init()
{
	//GPIO INITS
	//enable clock for GPIOB
	clock_init(GPIOB);
	//enable timer 12
	*(RCC_APB1ENR) |= 1 << TIM12_APB1ENR;
	//enable alternate function mode for TIM12 pin PB14
	mode_select(GPIOB_MODER, AF, PB14);
	//set IC1 on TI1
		//pg 608
		//clear IC1
	*(TIM12_CCMR1) &= 0xFFFC;
		//set IC1 to TI1
	*(TIM12_CCMR1) |= 0b01;
	//set input capture on both edges (rising and falling)
	//enable input capture
		//pg 611
	*(TIM12_CCER) |= 0b1011;
	//enable interrupt requests
		//pg 604
	*(TIM12_DIER) |= 0b10;

}

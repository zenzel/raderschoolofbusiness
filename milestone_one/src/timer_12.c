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
	//enable interrupt requests for input capture
	//enable interrupt requests for reloads (time out)
		//pg 604
	*(TIM12_DIER) |= 0b11;
	//enable the ISR in the NVIC
	*(NVIC_ISER1) |= 0x800;
	//set pre-scaler to 160. With a 16MHz clock, this gives a count period
	//of 10 uS. Documentation for Channel Monitor specifies timeout at
	//1.11 ms, or 1110 uS. A timer period of 10 uS gives us the necessary precision
	//to meet the timing requirement.
	//note that the pre-scale value is PSC+1, so we load 159 instead of 160.
	*(TIM12_PSC) = 0x009F;
	//set timer to auto-reload at 111. we configured a reload to trigger
	//an interrupt letting us know the timer has expired when the timer reloads
	*(TIM12_ARR) = 0x006F;
}

/*
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#include "timers.h"
#include "GPIO_driver.h"



void timer_6_init() {
	//enable timer clock
	*(RCC_APB1ENR) |= (1 << TIM6_APB1ENR);

	//set the update event source to overflow only
	*(TIM6_CR1) |= (1 << TIM6_URS);

	//enable interrupt
	*(TIM6_DIER) |= (1 << TIM6_UIE);

	//16,000,000 clocks per second
	//want 2000 events per second
	//so we prescale by 4000 (3999)
	//results in 4000 counts per second
	//reload register is 2

	//set the prescale register to give a clock of 4000Hz
	*(TIM6_PSC) = BITRATE_PSC;

	//set the reload register to count of 2
	*(TIM6_ARR) = BITRATE_RELOAD;
}


//initializes timer 12 to the required needs of the channel monitor.
//That it, TIM12 is configured for input capture on dual edges.
//Because the capture is on dual edges and wee need to know the
//logic level of the data pulses. See pg 181 for why we are lucky!
//Even though PB14 is in alternate function mode, it's input is still
//stored in the GPIO_IDR. This means we can capture on both edges
//and still be able to find out what voltage we are at.
//This voltage checking will be taken care of in the TIM12 IRQHandler
void timer_12_init()
{
	//GPIO INITS
	//enable clock for GPIOB
	clock_init(GPIOB);
	//enable timer 12
	*(RCC_APB1ENR) |= 1 << TIM12_APB1ENR;
	//enable alternate function mode for TIM12 pin PB14
	mode_select(GPIOB_MODER, AF, PB14);
	//slect alternate function
	*(GPIOB_AFRH) |= (0b1001 << 24);
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
	//*(TIM12_PSC) = 0x009F;
	//set timer to auto-reload at 111. we configured a reload to trigger
	//an interrupt letting us know the timer has expired when the timer reloads
	//*(TIM12_ARR) = 0x006F;
	*(TIM12_ARR) = 0x4560;
	//enable the timer.
	//set the timer to generate update IRQ's only when
	//the the timer auto-updates, and not when it is
	//reset by the program.
	*(TIM12_CR1) |= 0b101;
}

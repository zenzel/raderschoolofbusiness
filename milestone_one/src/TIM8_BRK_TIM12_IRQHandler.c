/*
 * TIM8_BRK_TIM12_IRQHandler.c
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#include <inttypes.h>
#include "channel_monitor.h"

extern void TIM8_BRK_TIM12_IRQHandler()
{
	//we either got here from a detected edge or a counter reset.
	//we need to determine which one happened.
	//the status register clears when it is read, so we can't check bit by bit. we have to
	//read in the whole thing
		//see pg 605
	volatile uint16_t status = *(TIM12_SR);
	//check if the timer expired
	if((status & 0b1) == 0b1)
	{
		//clear interrupt flag
		*(TIM12_SR) &= 0xFFFE;

		//get Tx value
		//if Tx is high, Tx_line will not equal 0.
		//if Tx is low, Tx_line will equal 0.
		Tx_line = *(GPIOB_IDR) & (1<<14);

		//timer expired, so check if line is high or low to determine if idle or collision
		//then take appropriate action
		if(Tx_line == 0)
		{
			channel_status = 2; //collision
			//we could call out set_collision() function,
			//but that would create function overhead in the ISR
			*(GPIOA_BSRR) = 1 << PA12; // set red LED
			*(GPIOA_BSRR) = 1 << (PA11 + 16); //clear yellow LED
			*(GPIOA_BSRR) = 1 << (PA10 + 16); //clear green LED
		}
		else
		{
			channel_status = 0; //idle
			*(GPIOA_BSRR) = 1 << PA10; //set green LED
			*(GPIOA_BSRR) = 1 << (PA11 + 16); //clear yellow LED
			*(GPIOA_BSRR) = 1 << (PA12 + 16); //clear red LED

		}

		//reset timer
		*(TIM12_EGR) |= 1;
	}
	else if((status & 0b10) == 0b10)
	{
		//clear interrupt flag
		*(TIM12_SR) &= 0xFFFD;

		channel_status = 1; //busy
		*(GPIOA_BSRR) = 1 << PA11; // set yellow LED
		*(GPIOA_BSRR) = 1 << (PA10 + 16); //clear green LED
		*(GPIOA_BSRR) = 1 << (PA12 + 16); //clear red LED
		//we are going to reset the timer, but this would cause an update event
		//which would cause this IRQHandler to be called again. We don't want that
		//so we will tell the timer not to create an update event, then reset, then
		//enable update events when we are done.
		//There is a bit in TIM12_CR1 which disables update IRQ's from software resets.
		//Setting this bit is a much better solution.
			//see pg 601
		//disable update events
		//*(TIM12_CR1) |= 0b10;
		//reset timer
		*(TIM12_EGR) |= 1;
		//enable update events
		//*(TIM12_CR1) &= 0xFFFD;
	}
}

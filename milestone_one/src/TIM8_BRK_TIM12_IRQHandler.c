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
	//we will check for an edge first since that is more likely during transmission.
	//doing this first might save us some cycles in the long run.
	if((status & 0b10) == 0b10)
	{
		//clear interrupt flag
		*(TIM12_SR) &= 0xFFFD;

		//we are going to reset the timer, but this would cause an update event
		//which would cause this IRQHandler to be called again. We don't want that
		//so we will tell the timer not to create an update event, then reset, then
		//enable update events when we are done.
			//see pg 601
		//disable update events
		*(TIM12_CR1) |= 0b10;
		//reset timer
		*(TIM12_EGR) |= 1;
		//enable update events
		*(TIM12_CR1) &= 0xFFFD;

		set_collision(); //for testing

	}
	//check if the timer expired
	else if((status & 0b1) == 0b1)
	{
		//clear interrupt flag
		*(TIM12_SR) &= 0xFFFE;

		//timer expired, so check if line is high or low to determine if idle or collision
		//then take appropriate action

		set_collision(); //for testing

		//we are going to reset the timer, but this would cause an update event
		//which would cause this IRQHandler to be called again. We don't want that
		//so we will tell the timer not to create an update event, then reset, then
		//enable update events when we are done.
		//disable update events
		*(TIM12_CR1) |= 0b10;
		//reset timer
		*(TIM12_EGR) |= 1;
		//enable update events
		*(TIM12_CR1) &= 0xFFFD;
	}
}

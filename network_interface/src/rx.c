/**
 * @file rx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 22 October 2018
 * @brief Source file for CE4951 receiver milestone.
 */

#include "rx.h"
#include "timers.h"

void TIM7_IRQHandler(void) {
	//set it to be 1/4 of bit period
	*(STK_LOAD) = bitrate_fourth;

	//enable the timer
	*(STK_CTRL) |= (1<<STK_ENABLE);
}

void SysTick_Handler(void) {
	//disable the timer
	*(STK_CTRL) &= ~(1<<STK_ENABLE);
}

/*
 * TIM8_BRK_TIM12_IRQHandler.c
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#include <inttypes.h>
#include <timers.h>
#include <stdlib.h>
#include "channel_monitor.h"
#include "tx.h"
#include "rx.h"

extern void TIM8_BRK_TIM12_IRQHandler() {
	//reset timer.
	//we do this before anything to avoid a race condition.
	//there are two cases:
	//The timer could expire immediately before an edge, in which
	//case we would be resetting the timer within microseconds,
	//or the timer could expire immediately after an edge, in which case
	//we want the timer reset ASAP to narrow the window for a interrupt
	//race condition.
	*(TIM12_EGR ) |= 1;
	//we either got here from a detected edge or a counter reset.
	//we need to determine which one happened.
	//we also need to avoid a race condition between the
	//interrupts, which can happen at a specific frequency
	//, so we check immediately and hope to see only one of the
	//interrupts pending in the TIM12_SR.
	volatile uint16_t status = *(TIM12_SR );
	//check to see if interrupt was caused by an edge
	if ((status & 0b10)) {
		//read the Tx line and record the value for the time-out interrupt
		Tx_line1 = *(GPIOB_IDR ) & (1 << PB14);
		//clear interrupt flag.
		*(TIM12_SR ) &= 0xFFFD;
		//set state to BUSY
		channel_status = BUSY;
		//set yellow LED and clear all others. the compiler/optimizer will make this look nice.
		*(GPIOA_BSRR ) = (1 << PA11) | (1 << (PA10 + 16)) | (1 << (PA12 + 16));
		//clear interrupt flag.
		*(TIM12_SR ) &= 0xFFFC; //CRITICAL ADDITION
		*(NVIC_ICPR1 ) &= ~0x0800; //CRITICAL ADDITION

		//calibrates the receiver clock
		if (counted_edges < 8) {
			if (counted_edges) {
				edge_delta_sum += *(TIM12_CCR1 );
			}
			counted_edges++;
		}

		//synch has been fully received
		if (counted_edges == 8) {
			bitrate = (edge_delta_sum / 7);
			bitrate_fourth = bitrate / 4;
			//*(TIM7_ARR) = bitrate;
			//enable
			//*(TIM7_CR1) |= (1 << TIM7_CEN);
			//populate first edge register
			//edges[0] = *(TIM12_CCR1);
			*(STK_LOAD ) = bitrate_fourth;
			counted_edges++;
		} else if (counted_edges == 9) {
			if (*(TIM12_CCR1 ) > (0.75 * bitrate)) {
				*(STK_CTRL ) |= (1 << STK_ENABLE);
			} else {
				counted_edges++;
			}
		} else if (counted_edges == 10) {
			*(STK_CTRL ) |= (1 << STK_ENABLE);
		}

		if (state == 2) {
			if (*(TIM12_CCR1 ) > ((0.75) * bitrate)) {
				bitrate = *(TIM12_CCR1 );
			} else {
				bitrate = 2 * (*(TIM12_CCR1 ));
			}

			//50 is an offset to account for instruction overhead on CPU
			bitrate_fourth = (bitrate / 4) + 50;
			*(STK_LOAD ) = bitrate_fourth;
			//enable the systick
			*(STK_CTRL ) |= (1 << STK_ENABLE);
			state = 0;
		}
	}

	//check if timer expired, then check if line is high or low to determine if idle or collision
	else if ((status & 0b1)) {
		//clear interrupt flag
		*(TIM12_SR ) &= 0xFFFE;
		//if data is high
		if (!Tx_line1) {
			//set state to COLLISION
			channel_status = COLLISION;
			//set red LED and clear others
			*(GPIOA_BSRR ) = (1 << PA12) | (1 << (PA11 + 16))
					| (1 << (PA10 + 16));

			//set the line idle
			*(GPIOB_BSRR) = 1 << PB15;

			//disable transmit timer
			*(TIM6_CR1 ) &= ~(1 << TIM6_CEN);

			//clear transmit count
			tx_count = 0;

			//calculate random backoff time in 16MHz ARR values, configured for 0.000s - 1.000s
			wait_time_reload = 50*((rand() % 200) + 1);

			//set TIM7 ARR to count the wait time
			*(TIM7_ARR) = wait_time_reload;
			*(TIM7_CR1) |= (1 << TIM7_CEN);
		} else {
			//set state to IDLE
			channel_status = IDLE;

			//set the edge calibrate high for next rx event
			counted_edges = 0;

			//set green LED and clear others
			*(GPIOA_BSRR ) = (1 << PA10) | (1 << (PA11 + 16))
					| (1 << (PA12 + 16));
		}
	}

}

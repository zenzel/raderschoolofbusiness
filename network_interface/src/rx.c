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

	//sample the line
	rx_buffer[bit_count] = *(GPIOB_IDR) & (1 << PB14);
	bit_count++;

	if(bit_count == 240) {
		//disable timer 7
		*(TIM7_CR1) &= ~(1 << TIM7_CEN);
		parse_flag = 1;
	}
}

void rx_parse() {
	uint8_t char_count = 0;
	while(bit_count) {
		for(int i = 0; i < 8; i++) {
			rx_chars[char_count] |= rx_buffer[bit_count--] << i;
		}
		char_count++;
	}

	parse_flag = 0;
}

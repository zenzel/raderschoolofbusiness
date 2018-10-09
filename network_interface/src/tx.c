/**
 * @file tx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 3 October 2018
 * @brief Source file for CE4951 Milestone 2: network transmitter.
 */

#include "timers.h"
#include "tx.h"
#include "uart_driver.h"
#include "channel_monitor.h"

uint8_t tx_get_input() {
	//how many characters to be sent
	bytes = 0;

	//for now let;s limit the transmission to 5 bytes
	char c;
	while (bytes < 5) {
		c = usart2_getch();
		if ((c == ENTER_PRESS)) {
			break;
		}

		char_buffer[bytes++] = c;
	}
	encode();
	tx();
	return bytes;
}

//an algorithm to turn the transmit character into manchester levels
void encode() {
	//first loop iterates through all bytes stored in the character buffer
	//second loop iterates through individual bits in each byte
	//adds to transmit buffer accordingly
	int idx = 0;
	for (int i = 0; i < bytes; i++) {
		for (int j = 7; j >= 0; j--) {
			//invert for first half of bit period
			tx_buffer[idx] = (~((char_buffer[i] & (1 << j)) >> j)) & 0b1;
			//transition during second half of bit period
			tx_buffer[idx+1] = ((char_buffer[i] & (1 << j)) >> j);
			idx+=2;
		}
	}
}

void tx() {
	//make sure count is at 0
	tx_count = 0;

	//enable the transmit timer
	*(TIM6_CR1 ) |= (1 << TIM6_CEN);
}

//repeatedly send data so we can test collision stopping
void collision_test()
{
	tx_count = 0;
	//enable the transmit timer
	*(TIM6_CR1 ) |= (1 << TIM6_CEN);
	while(1)
	{
		if(tx_count == (bytes * CHAR_SIZE * 2))
		{
			tx_count = 0;
			//enable the transmit timer
			*(TIM6_CR1 ) |= (1 << TIM6_CEN);
		}
	}
}

extern void TIM6_DAC_IRQHandler() {
	//if collision is detected, halt the timer

	if (channel_status == COLLISION) {
		*(TIM6_CR1 ) &= ~(1 << TIM6_CEN);
		*(GPIOB_BSRR) = 1 << PB15;
	} else if (tx_count < (bytes * CHAR_SIZE * 2)) {
		//here we set the BSRR to whatever is in the tx register
		//*(GPIOB_BSRR) = (1 << (PB15 + 16)) | (tx_buffer[tx_count++] << PB15);
		if (tx_buffer[tx_count]) {
			*(GPIOB_BSRR) = 1 << PB15;
		}
		else {
			*(GPIOB_BSRR) = 1 << (PB15 + 16);
		}
		tx_count++;
	} else if (tx_count == (bytes * CHAR_SIZE * 2)) {
		//turn off TIM6 because we are done transmitting
		*(TIM6_CR1 ) &= ~(1 << TIM6_CEN);
		*(GPIOB_BSRR) = 1 << PB15;
	}
	*(TIM6_SR ) &= 0xFFFE;
}

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
	return bytes;
}

//an algorithm to turn the transmit character into manchester levels
void encode() {
	//first loop iterates through all bytes stored in the character buffer
	//second loop iterates through individual bits in each byte
	//adds to transmit buffer accordingly
	int idx = 0;
	for (int i = 0; i <= bytes; i++) {
		for (int j = 0; j < 8; j++) {
			tx_buffer[idx] = ((char_buffer[i] & (1 << j)) >> j);
			idx++;
		}
	}
}

void tx() {
	//enable GPIOB PB15 for transmit
	clock_init(GPIOB);
	mode_select(GPIOB_MODER, OUT, PB15);

	//make sure count is at 0
	tx_count = 0;

	//enable the transmit timer
	*(TIM6_CR1 ) |= (1 << TIM6_CEN);
}

extern void TIM6_DAC_IRQHandler() {
	//if collision is detected, halt the timer
	if (channel_status == COLLISION) {
		*(TIM6_CR1 ) &= ~(1 << TIM6_CEN);
	} else if (tx_count <= (bytes * sizeof(char))) {
		//here we set the BSRR to whatever is in the tx register
		*(GPIOB_BSRR) = (1 << (PB15 + 16)) | (tx_buffer[tx_count++] << PB15);
		//this works, right?
	}

}

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

void encode(uint8_t bytes);

uint8_t tx_get_input() {
	//how many characters to be sent
	uint8_t bytes = 0;

	//for now let;s limit the transmission to 5 bytes
	char c;
	while(bytes < 5) {
		c = usart2_getch();
		if((c == ENTER_PRESS)) {
			break;
		}
		char_buffer[bytes++] = c;
	}
	encode(bytes);
	return bytes;
}


void tx() {
	//enable the transmit timer
	*(TIM6_CR1) |= (1 << TIM6_CEN);

}


//an algorithm to turn the transmit character into manchester levels
void encode(uint8_t bytes) {
	//first loop iterates through all bytes stored in the character buffer
	//second loop iterates through individual bits in each byte
	//adds to transmit buffer accordingly
	int idx = 0;
	for(int i = 0; i <= bytes; i++) {
		for(int j = 0; j < 8; j++) {
			tx_buffer[idx] = ((char_buffer[i] & (1 << j)) >> j);
			idx++;
		}
	}
}

extern void TIM6_DAC_IRQHandler() {
	//if collision is detected, halt the timer
	if(channel_status == COLLISION) {
		*(TIM6_CR1) &= ~(1 << TIM6_CEN);
	}

	//here we set the BSRR to whatever is in the tx register
	//GPIO_BSRR &= (1 << (P + 16)) | (tx_buffer[tx_count++] << P);
	//this works, right?


}

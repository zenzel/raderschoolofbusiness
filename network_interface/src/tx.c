/**
 * @file tx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 3 October 2018
 * @brief Source file for CE4951 Milestone 2: network transmitter.
 */

#include "tx.h"
#include "uart_driver.h"

void encode(uint8_t bytes);

void tx_get_input() {
	//how many characters to be sent
	uint8_t bytes = 0;

	//transmit flag
	uint8_t enter = 0;

	//for now let's limit the transmission to 5 bytes
	while (1) {
		char c = usart2_getch();
		if ((c == ENTER_PRESS) || (bytes > 4)) {
			encode(bytes);
			break;
		} else {
			char_buffer[bytes++] = c;
		}
	}
}

void encode(uint8_t bytes) {
	for (int i = 0; i < bytes; i++) {
		if () {
		}
	}
}

void tx() {

}

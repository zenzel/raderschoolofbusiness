/**
 * @file tx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 3 October 2018
 * @brief Source file for CE4951 Milestone 2: network transmitter.
 */

#include <stdbool.h>
#include "tx.h"
#include "uart_driver.h"


void tx_get_input() {
	//how many characters to be sent
	uint8_t bytes = 0;

	//for now let;s limit the transmission to 5 bytes
	char c;
	for(; bytes < 5; bytes++) {
		c = usart2_getch();
		if((c == ENTER_PRESS)) {
			break;
		}
		char_buffer[bytes] = c;
	}


	tx();
}


void tx() {

}

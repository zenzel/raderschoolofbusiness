/**
 * @file main.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 27 September 2018
 * @brief Main driver for CE4951 Network Interface Card.
 */

#include <inttypes.h>
#include <timers.h>
#include <timers.h>
#include <stdio.h>
#include "channel_monitor.h"
#include "uart_driver.h"
#include "tx.h"
#include "rx.h"

int main() {
	channel_monitor_init();
	timer_12_init();
	timer_7_init();
	timer_6_init();
	systick_init();
	usart2_init(DEFAULT_BAUD, F_CPU);

	parse_flag = 0;
	char choice;
	while (1) {
		//tx or rx
		printf("\n\rPress (t) for transmit or (r) for receive.\n\r");
		choice = usart2_getch();
		if (choice == 't') {
			tx_get_input();
			tx();
		} else if (choice == 'r') {
			//wait for full message to come in
			while(!parse_flag);
			rx_parse();
			//reset receive variables
			counted_edges = 0;
			bit_count = 0;
			length = 0;
			parse_flag = 0;
			state = 0;
			edge_delta_sum = 0;
			printf("\r\n");
		}
	}
}

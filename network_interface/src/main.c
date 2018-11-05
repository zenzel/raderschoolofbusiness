/**
 * @file main.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 27 September 2018
 * @brief Main driver for CE4951 Network Interface Card.
 */

#include <inttypes.h>
#include <timers.h>
#include <timers.h>
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

	//tx or rx
	usart2_putch('t');
	usart2_putch('/');
	usart2_putch('r');
	usart2_putch('?');
	usart2_putch('\n');
	usart2_putch('\r');
	char choice = usart2_getch();

	if(choice == 't') {
		usart2_putch('t');
		usart2_putch(':');
		usart2_putch(' ');
		tx_get_input();
		tx();
	}

	//collision_test();
	parse_flag = 0;
	while(1) {
		if(parse_flag) {
			rx_parse();
			//reset receive variables
			counted_edges = 0;
			bit_count = 0;
			length = 0;
			parse_flag = 0;
			state = 0;
			edge_delta_sum = 0;
		}
	}
}

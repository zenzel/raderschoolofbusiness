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
	//collision_test();
	tx_get_input();
	tx();
	parse_flag = 0;
	while(1) {
		if(parse_flag) {
			rx_parse();
		}
	}
}

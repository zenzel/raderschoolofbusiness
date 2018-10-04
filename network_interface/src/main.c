/**
 * @file main.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 27 September 2018
 * @brief Main driver for CE4951 Network Interface Card.
 */

#include <inttypes.h>
#include "channel_monitor.h"
#include "timer_12.h"
#include "uart_driver.h"

int main() {

	channel_monitor_init();
	timer_12_init();
	usart2_init(DEFAULT_BAUD, F_CPU);

	while(1);
}

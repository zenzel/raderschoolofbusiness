/**
 * @file main.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 27 September 2018
 * @brief Main driver for CE4951 Milestone 1.
 */

#include "channel_monitor.h"

int main() {
	//enable clocks for gpio a
	//PA13, 14, 15
	//interrupt NVIC pg 234

	channel_monitor_init();


	while(1);
}

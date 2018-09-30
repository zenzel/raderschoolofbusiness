
#include <stdio.h>
#include "GPIO_driver.h"
/*
 * Initializers.
 */
void channel_monitor_init() {
	//****************************************
	//GPIO INITS
	//enable clock for GPIOA
	clock_init(GPIOA);
}

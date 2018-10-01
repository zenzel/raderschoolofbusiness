
#include <stdio.h>
#include "GPIO_driver.h"
#include "channel_monitor.h"
/*
 * Initializers.
 */
void channel_monitor_init()
{
	//****************************************
	//GPIO INITS
	//enable clock for GPIOA
	clock_init(GPIOA);
	//set PA10 (green LED) to output
	mode_select(GPIOA_MODER, OUT, PA10);
	//set PA11 (yellow LED) to output
	mode_select(GPIOA_MODER, OUT, PA11);
	//set PA12 (red LED) to output
	mode_select(GPIOA_MODER, OUT, PA12);
	//clear all LED's
	clear_idle();
	clear_busy();
	clear_collision();
	set_idle();
	clear_idle();
	set_busy();
	clear_busy();
	set_collision();
	clear_collision();
}

void set_idle()
{
	*(GPIOA_BSRR) = 1 << PA10;
}

void clear_idle()
{
	*(GPIOA_BSRR) = 1 << (PA10 + 16);
}

void set_busy()
{
	*(GPIOA_BSRR) = 1 << PA11;
}

void clear_busy()
{
	*(GPIOA_BSRR) = 1 << (PA11 + 16);
}

void set_collision()
{
	*(GPIOA_BSRR) = 1 << PA12;
}

void clear_collision()
{
	*(GPIOA_BSRR) = 1 << (PA12 + 16);
}

/*
 * Selects the specified mode for the specified pin at the given
 * MODER address. Accepts a mode and a pin number (shift amount).
 */
//void mode_select(volatile uint32_t* adr, uint8_t mode, uint16_t pin)

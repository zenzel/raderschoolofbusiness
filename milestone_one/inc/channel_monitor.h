/*
 * channel_monitor.h
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#ifndef CHANNEL_MONITOR_H_
#define CHANNEL_MONITOR_H_

#include <inttypes.h>

//initialize the channel monitor
//-enable clocks for GPIOA
void channel_monitor_init();

//set the green LED
void set_idle();

//clear the green LED
void clear_idle();

//set the yellow LED
void set_busy();

//clear the yellow LED
void clear_busy();

//set the red LED
void set_collision();

//clear the red LED
void clear_collision();

#define PA10 10
#define PA11 11
#define PA12 12


#endif /* CHANNEL_MONITOR_H_ */
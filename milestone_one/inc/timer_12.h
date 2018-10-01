/*
 * timer_12.h
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#ifndef TIMER_12_H_
#define TIMER_12_H_

#include <inttypes.h>

#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define TIM12_BASE (volatile uint32_t*) 0x40001800
#define TIM12_CCMR1 (volatile uint32_t*) 0x40001818
#define TIM12_CCER (volatile uint32_t*) 0x40001820
#define TIM12_DIER (volatile uint32_t*) 0x40001820C
#define TIM12_APB1ENR 6
#define PB14 14

//initialize timer 12
void timer_12_init();

#endif /* TIMER_12_H_ */

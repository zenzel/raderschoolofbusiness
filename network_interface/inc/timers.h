/*
#include <timers.h>
 * timer_12.h
 *
 *  Created on: Sep 30, 2018
 *      Author: micha
 */

#ifndef TIMER_12_H_
#define TIMER_12_H_

#include <inttypes.h>

//clock enable register
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840

//NVIC registers
#define NVIC_BASE (volatile uint32_t*) 0xE000E100
#define NVIC_ISER1 (volatile uint32_t*) 0xE000E104
#define NVIC_ICSR (volatile uint32_t*) 0xE000ED04

//systick
#define STK_CTRL (volatile uint32_t*) 0xE000E010
#define STK_LOAD (volatile uint32_t*) 0xE000E014
#define STK_VAL (volatile uint32_t*) 0xE000E014
#define STK_ENABLE 0
#define STK_INT_EN 1
#define STK_CLKSRC 2
#define STK_COUNT 16
//clear in what i call NVIC_ICSR
#define STK_CLR_PEND 25
uint32_t systick_period;

//TIM6
#define TIM6_BASE (volatile uint32_t*) 0x40001000
#define TIM6_CR1 (volatile uint32_t*) 0x40001000
#define TIM6_CR2 (volatile uint32_t*) 0x40001004
#define TIM6_DIER (volatile uint32_t*) 0x4000100C
#define TIM6_SR (volatile uint32_t*) 0x40001010
#define TIM6_EGR (volatile uint32_t*) 0x40001014
#define TIM6_CNT (volatile uint32_t*) 0x40001024
#define TIM6_PSC (volatile uint32_t*) 0x40001028
#define TIM6_ARR (volatile uint32_t*) 0x4000102C
#define TIM6_APB1ENR 4

#define TIM6_URS 2
#define TIM6_CEN 0
#define TIM6_UIE 0
#define TIM6_ISER_EN 22

#define BITRATE_PSC 2673
#define BITRATE_RELOAD 2

//TIM7
#define TIM7_BASE (volatile uint32_t*) 0x40001400
#define TIM7_CR1 (volatile uint32_t*) 0x40001400
#define TIM7_CR2 (volatile uint32_t*) 0x40001404
#define TIM7_DIER (volatile uint32_t*) 0x4000140C
#define TIM7_SR (volatile uint32_t*) 0x40001410
#define TIM7_EGR (volatile uint32_t*) 0x40001414
#define TIM7_CNT (volatile uint32_t*) 0x40001424
#define TIM7_PSC (volatile uint32_t*) 0x40001428
#define TIM7_ARR (volatile uint32_t*) 0x4000142C
#define TIM7_APB1ENR 5

#define TIM7_URS 2
#define TIM7_CEN 0
#define TIM7_UIE 0
#define TIM7_UIF 0
#define TIM7_ISER_EN 23

uint32_t tim7_bitrate_psc;

//TIM12
#define TIM12_BASE (volatile uint32_t*) 0x40001800
#define TIM12_CR1 (volatile uint32_t*) 0x40001800
#define TIM12_CCMR1 (volatile uint32_t*) 0x40001818
#define TIM12_CCR1 (volatile uint32_t*) 0x40001834
#define TIM12_CCER (volatile uint32_t*) 0x40001820
#define TIM12_DIER (volatile uint32_t*) 0x4000180C
#define TIM12_PSC (volatile uint32_t*) 0x40001828
#define TIM12_ARR (volatile uint32_t*) 0x4000182C
#define TIM12_SR (volatile uint32_t*) 0x40001810
#define TIM12_EGR (volatile uint32_t*) 0x40001814
#define TIM12_APB1ENR 6

//pins
#define PB14 14
#define PB13 13

//initialize timer 12
void timer_12_init();

//initialize timer 6
void timer_6_init();

//initialize timer 7
void timer_7_init();

//initialize systick
void systick_init();

#endif /* TIMERS_H_ */

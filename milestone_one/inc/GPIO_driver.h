/*
 * File: GPIO_driver.h
 * Written by: Eli Zenz <zenze@msoe.edu>
 * Updated on: 12 Febrauary 2017
 * Header file for GPIO_driver.c
 */

/*
typedef struct {
	uint32_t MODER;
	uint32_t BSRR;
} GPIO;

static volatile GPIO* GPIOA = 0x4002000;
GPIOA->MODER = ...
*/

#include <inttypes.h>

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define GPIOA 0
#define GPIOB 1
#define GPIOC 2
#define TIMER2 3
#define TIMER3 4
#define TIMER4 5

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844

#define GPIOA_MODER (volatile uint32_t*) 0x40020000
#define GPIOB_MODER (volatile uint32_t*) 0x40020400
#define GPIOC_MODER (volatile uint32_t*) 0x40020800

#define OUT 0b01
#define IN 0b00
#define AF 0b10
#define ANALOG 0b11

#define GPIOA_IDR (volatile uint32_t*) 0x40020010
#define GPIOB_IDR (volatile uint32_t*) 0x40020410
#define GPIOC_IDR (volatile uint32_t*) 0x40020810

#define GPIOA_ODR (volatile uint32_t*) 0x40020014
#define GPIOB_ODR (volatile uint32_t*) 0x40020414
#define GPIOC_ODR (volatile uint32_t*) 0x40020814

#define GPIOA_BSRR (volatile uint32_t*) 0x40020018
#define GPIOB_BSRR (volatile uint32_t*) 0x40020418
#define GPIOC_BSRR (volatile uint32_t*) 0x40020818

#define GPIOC_PUPDR (volatile uint32_t*) 0x4002080C
#define GPIOB_AFRL (volatile uint32_t*) 0x40020420

#define LED_A_OUTPUT 0x00554000
#define LED_B_OUTPUT 0x05150000

#define LEDS_A 0b111110000000
#define LEDS_B 0b11011100000000

#define A7 1<<7
#define A8 1<<8
#define A9 1<<9
#define A10 1<<10
#define A11 1<<11

#define B8 1<<8
#define B9 1<<9
#define B10 1<<10
#define B12 1<<12
#define B13 1<<13

extern void clock_init(uint8_t);
extern void mode_select(volatile uint32_t*, uint8_t, uint16_t);

#endif

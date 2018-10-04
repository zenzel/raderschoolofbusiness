/**
 * @file uart_driver.h
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 4 October 2018
 * @brief Header file for onboard U(S)ART driver.
 * Some code source from W. Barnekow.
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <inttypes.h>

// RCC registers
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830

#define GPIOAEN 0		// GPIOA Enable is bit 0 in RCC_APB1LPENR
#define USART2EN 17  // USART2 enable is bit 17 in RCC_AHB1LPENR

// USART registers
#define USART_SR    (volatile uint32_t*) 0x40004400
#define USART_DR    (volatile uint32_t*) 0x40004404
#define USART_BRR   (volatile uint32_t*) 0x40004408
#define USART_CR1   (volatile uint32_t*) 0x4000440c
#define USART_CR2   (volatile uint32_t*) 0x40004410
#define USART_CR3   (volatile uint32_t*) 0x40004414

// CR1 bits
#define UE 13 //UART enable
#define TE 3  // Transmitter enable
#define RE 2  // Receiver enable

// Status register bits
#define TXE 7  // Transmit register empty
#define RXNE 5  // Receive register is not empty..char received

#define DEFAULT_BAUD 19200
#define F_CPU 16000000UL

// Function prototypes
extern void usart2_init(uint32_t baud, uint32_t sysclk);
extern char usart2_getch();
extern void usart2_putch(char c);



#endif /* UART_DRIVER_H_ */

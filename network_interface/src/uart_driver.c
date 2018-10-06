/**
 * @file uart_driver.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 4 October 2018
 * @brief Driver program for onboard U(S)ART.
 * Some code source from W. Barnekow.
 */

#include <stdio.h>
#include <inttypes.h>
#include "timers.h"
#include "uart_driver.h"
#include "GPIO_driver.h"

void usart2_init(uint32_t baud, uint32_t sysclk) {
	// Enable clocks for GPIOA and USART2
	*(RCC_AHB1ENR ) |= (1 << GPIOAEN);
	*(RCC_APB1ENR ) |= (1 << USART2EN);

	// Function 7 of PORTA pins is USART
	*(GPIOA_AFRL ) &= (0xFFFF00FF); // Clear the bits associated with PA3 and PA2
	*(GPIOA_AFRL ) |= (0b01110111 << 8); // Choose function 7 for both PA3 and PA2
	*(GPIOA_MODER ) &= (0xFFFFFF0F);  // Clear mode bits for PA3 and PA2
	*(GPIOA_MODER ) |= (0b1010 << 4);  // Both PA3 and PA2 in alt function mode

	// Set up USART2
	//USART2_init();  //8n1 no flow control
	// over8 = 0..oversample by 16
	// M = 0..1 start bit, data size is 8, 1 stop bit
	// PCE= 0..Parity check not enabled
	// no interrupts... using polling
	*(USART_CR1 ) = (1 << UE) | (1 << TE) | (1 << RE); // Enable UART, Tx and Rx
	*(USART_CR2 ) = 0;  // This is the default, but do it anyway
	*(USART_CR3 ) = 0;  // This is the default, but do it anyway
	*(USART_BRR ) = sysclk / baud;

	/* I'm not sure if this is needed for standard IO*/
	//setvbuf(stderr, NULL, _IONBF, 0);
	//setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

//fetches a character from the uart
char usart2_getch() {
	char c;
	//wait for the receive bit to be set in the status register
	while ((*(USART_SR ) & (1 << RXNE)) != (1 << RXNE));

	//read character from uart
	c = ((char) *USART_DR );

	//callback for echo
	usart2_putch(c);

	//not needed for now
	// If character is CR
	/*if (c == '\r') {
		usart2_putch('\n');  // send it
		c = '\n';   // Return LF. fgets is terminated by LF
	}*/

	return c;
}

//sends a character to the uart
void usart2_putch(char c) {
	//wait for the transmit bit to be ready
	while ((*(USART_SR ) & (1 << TXE)) != (1 << TXE));
	//write character to data register
	*(USART_DR ) = c;
}


/**
 * @file rx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 22 October 2018
 * @brief Source file for CE4951 receiver milestone.
 */

#include "tx.h"
#include "rx.h"
#include "timers.h"
#include "uart_driver.h"

void SysTick_Handler(void) {
	//clear the pending status
	*(NVIC_ICSR) &= ~(1 << STK_CLR_PEND);

	//disable the timer
	//*(STK_CTRL) &= ~(1<<STK_ENABLE);

	//sample the line if in state 0
	if(state == 0){
		rx_buffer[bit_count] = *(GPIOB_IDR) & (1 << PB14);
		bit_count++;
		state++;
	}
	else if(state == 2){
		sample_flag = 1;
		//disable the timer
		*(STK_CTRL) &= ~(1<<STK_ENABLE);
		//a write to Systick_Val register resets the timer
		//and clears the reload flag
		*(STK_VAL) = 0;
	}
	else{
		state++;
	}
	//if we read in the length field
	if(bit_count == 32)
	{
		length = 0;
		length |= rx_buffer[31] << 0;
		length |= rx_buffer[30] << 1;
		length |= rx_buffer[29] << 2;
		length |= rx_buffer[28] << 3;
		length |= rx_buffer[27] << 4;
		length |= rx_buffer[26] << 5;
		length |= rx_buffer[25] << 6;
		length |= rx_buffer[24] << 7;
		//convert length to bits
		length *= 8;
	}

	if(length && (bit_count == length)) {
		//disable timer 7
		//*(TIM7_CR1) &= ~(1 << TIM7_CEN);
		parse_flag = 1;

		//disable systick
		*(STK_CTRL) &= ~(1 << STK_ENABLE);
	}
}

void rx_parse() {
	uint8_t char_count = 0;
	uint32_t bits = 0;
	while(bits < bit_count) {
		for(int i = 7; i >= 0; i--) {
			rx_chars[char_count] |= rx_buffer[bits++] << i;
		}
		char_count++;
	}

	uint8_t check = crc_rx(rx_chars, (char_count - 1));

	for(int i = 0; i <= char_count; i++) {
		usart2_putch(rx_chars[i]);
	}

	if(!(check ^= rx_chars[char_count - 1])) {
		printf("CRC Check PASS\n\r");
	} else {
		printf("CRC Check FAIL\n\r");
	}

	parse_flag = 0;

	//clear the bit count
	bit_count = 0;
}

//crc algorithm (reference: https://barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code)
CRC crc_rx(char const message[], int nBytes) {
	CRC remainder = 0;

	for (int byte = 5; byte < nBytes; ++byte) {
		remainder ^= (message[byte] << (WIDTH - 8));

		for (uint8_t bit = 8; bit > 0; --bit) {
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			} else {
				remainder = (remainder << 1);
			}
		}
	}
	return (remainder);
}

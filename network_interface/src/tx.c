/**
 * @file tx.c
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 3 October 2018
 * @brief Source file for CE4951 Milestone 2: network transmitter.
 */

#include <stdlib.h>
#include <stdio.h>
#include "timers.h"
#include "tx.h"
#include "uart_driver.h"
#include "channel_monitor.h"
#include "GPIO_driver.h"

uint8_t tx_get_input() {
	//how many bytes will be sent
	bytes = 6;

	printf("Enter the destination address in hex (0x##): 0x");
	char addr0 = usart2_getch();
	char addr1 = usart2_getch();

	printf("\r\nEnable CRC FCS (y)/(n)?\n\r");
	char crc_c = usart2_getch();
	uint8_t crc_en = 0;
	if(crc_c == ENTER_PRESS || crc_c == 'y') {
		crc_en = 1;
	}

	char c;
	while ((c = usart2_getch() != ENTER_PRESS) && (bytes < 254)) {
		char_buffer[bytes++] = c;
	}
	//add synch bits to header
	char_buffer[0] = 0x55;
	//add version to header
	char_buffer[1] = 0x01;
	//add source to header
	char_buffer[2] = 0x06;
	//add destination to header
	char_buffer[3] = (addr0 << 4) | addr1;
	//add CRC flag to header
	char_buffer[5] = (char)crc_en;
	//add length to header
	//usually this would be (bytes - 1), but (-1) taken off for CRC byte addition
	char_buffer[4] = (bytes++) & 0xFF;

	//add CRC trailer before data is encoded
	if(crc_en) {
		uint8_t temp = crc(char_buffer, (bytes - 1));
		char_buffer[bytes - 1] = (char) temp;
	} else {
		char_buffer[bytes - 1] = 0xAA;
	}
	encode();
	tx();
	return bytes;
}

//crc algorithm (reference: https://barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code)
CRC crc(char const message[], int nBytes) {
	CRC remainder = 0;

	for (int byte = 6; byte < nBytes; ++byte) {
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

//an algorithm to turn the transmit character into manchester levels
void encode() {
	//first loop iterates through all bytes stored in the character buffer
	//second loop iterates through individual bits in each byte
	//adds to transmit buffer accordingly
	int idx = 0;
	for (int i = 0; i < bytes; i++) {
		for (int j = 7; j >= 0; j--) {
			//invert for first half of bit period
			tx_buffer[idx] = (~((char_buffer[i] & (1 << j)) >> j)) & 0b1;
			//transition during second half of bit period
			tx_buffer[idx + 1] = ((char_buffer[i] & (1 << j)) >> j);
			idx += 2;
		}
	}
}

void tx() {
	//make sure count is at 0
	tx_count = 0;

	//set the transmit start flag
	tx_start = 1;

	//enable the transmit timer
	*(TIM6_CR1 ) |= (1 << TIM6_CEN);
}

//repeatedly send data so we can test collision stopping
/*void collision_test()
 {
 tx_count = 0;
 //enable the transmit timer
 *(TIM6_CR1 ) |= (1 << TIM6_CEN);
 while(1)
 {
 if(tx_count == (bytes * CHAR_SIZE * 2))
 {
 tx_count = 0;
 //enable the transmit timer
 *(TIM6_CR1 ) |= (1 << TIM6_CEN);
 }
 }
 }*/

extern void TIM6_DAC_IRQHandler() {
	//clear the pending IRQ bit
	*(TIM6_SR ) &= ~(1 << TIM6_UIF);

	//clear the pending IRQ in NVIC
	*(NVIC_ICPR1 ) |= (1 << TIM6_ICPR_CLR);

	//if still transmitting
	if (tx_count < (bytes * CHAR_SIZE * 2)) {
		waiting = false;
		//here we set the BSRR to whatever is in the tx register
		//*(GPIOB_BSRR) = (1 << (PB15 + 16)) | (tx_buffer[tx_count++] << PB15);
		if (tx_buffer[tx_count]) {
			*(GPIOB_BSRR ) = 1 << PB15;
		} else {
			*(GPIOB_BSRR ) = 1 << (PB15 + 16);
		}
		tx_count++;
	} else if (tx_count == (bytes * CHAR_SIZE * 2)) {
		//turn off TIM6 because we are done transmitting
		*(TIM6_CR1 ) &= ~(1 << TIM6_CEN);

		//clear timeout count
		try_count = 0;

		//set full transmit complete flag
		full_tx = true;

		//clear transmit start flag
		tx_start = false;

		//clear bit
		*(GPIOB_BSRR ) = 1 << PB15;
	}
}

void TIM7_IRQHandler(void) {
	//clear the pending status
	*(TIM7_SR ) &= ~(1 << TIM7_UIF);

	//disable TIM7
	*(TIM7_CR1 ) &= ~(1 << TIM7_CEN);

	//enable the transmit timer
	*(TIM6_CR1 ) |= (1 << TIM6_CEN);

	//signal we are done backing off
	backoff = false;
}

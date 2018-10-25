/**
 * @file tx.h
 * @author Michael Doughery <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 4 Ocotber 2018
 * @brief Header file for transmission controller.
 */

#ifndef TX_H_
#define TX_H_

#include <stdbool.h>

//temporary size of character buffer
#define BUFFER_SIZE 500

#define CHAR_SIZE 8

//TODO find what the enter key returns on our hardware
#define ENTER_PRESS '\r'

//holds number of bytes actually selected to be sent
volatile uint8_t bytes;

//holds characters to transmit
char char_buffer[BUFFER_SIZE];

//holds the breakout of bits from transmit characters
bool tx_buffer[CHAR_SIZE * BUFFER_SIZE * 2];

//holds the transmit count
int tx_count;

uint8_t tx_get_input();
void tx();
void encode();
void collision_test();

#endif /* TX_H_ */

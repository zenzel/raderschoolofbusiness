/**
 * @file tx.h
 * @author Michael Doughery <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 4 Ocotber 2018
 * @brief Header file for transmission controller.
 */

#ifndef TX_H_
#define TX_H_

#include <stdbool.h>

typedef uint8_t CRC;
#define WIDTH  (8 * sizeof(CRC))
#define TOPBIT (1 << (WIDTH - 1))

//0b100000111
#define POLYNOMIAL 0x07

//temporary size of character buffer
#define BUFFER_SIZE 500

#define CHAR_SIZE 8

//TODO find what the enter key returns on our hardware
#define ENTER_PRESS '\r'

//holds number of bytes actually selected to be sent
volatile uint16_t bytes;

//holds characters to transmit
char char_buffer[BUFFER_SIZE];

//backoff flag
bool backoff;

//transmit start flag
bool tx_start;

//holds the breakout of bits from transmit characters
bool tx_buffer[CHAR_SIZE * BUFFER_SIZE * 2];

//holds the transmit count
int tx_count;

uint32_t wait_time_reload;
bool waiting;

//timeout counter
uint8_t try_count;

//flag to see if message has been fully transmitted in the past
bool full_tx;


uint8_t tx_get_input();
void tx();
void encode();
CRC crc(char const message[], int nBytes);
void collision_test();

#endif /* TX_H_ */

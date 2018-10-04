/**
 * @file tx.h
 * @author Michael Doughery <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 4 Ocotber 2018
 * @brief Header file for transmission controller.
 */

#ifndef TX_H_
#define TX_H_

//temporary size of character buffer
#define BUFFER_SIZE 5

//TODO find what the enter key returns on our hardware
#define ENTER_PRESS 13

//holds characters to transmit
char char_buffer[BUFFER_SIZE];

//holds encoded bits to transmit
uint32_t tx_buffer[(sizeof(char) * BUFFER_SIZE) * 2]; //doubled size for manchester

void tx_get_input();
void tx();

#endif /* TX_H_ */

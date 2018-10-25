/**
 * @file rx.h
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 22 October 2018
 * @brief Header file for CE4951 receiver.
 */

#ifndef RX_H_
#define RX_H_

#include <stdbool.h>

#define PB1 1

uint8_t parse_flag;
uint8_t counted_edges;
uint32_t edge_delta_sum;
uint32_t bitrate;
uint32_t bitrate_fourth;
volatile uint64_t bit_count;

bool rx_buffer[240];
char rx_chars[30];

void rx_parse();


#endif /* RX_H_ */

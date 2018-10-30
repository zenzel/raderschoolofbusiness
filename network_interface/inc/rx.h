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

uint32_t parse_flag;
uint32_t counted_edges;
uint32_t edge_delta_sum;
uint32_t bitrate;
uint32_t bitrate_fourth;
volatile uint64_t bit_count;
uint32_t length;
uint32_t state;
uint32_t sample_flag;
//int edges[3];

bool rx_buffer[2048];
char rx_chars[256];

void rx_parse();


#endif /* RX_H_ */

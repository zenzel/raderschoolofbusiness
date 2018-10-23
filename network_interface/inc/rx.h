/**
 * @file rx.h
 * @author Michael Dougherty <doughertymj@msoe.edu>, Eli Zenz <zenze@msoe.edu>
 * @date 22 October 2018
 * @brief Header file for CE4951 receiver.
 */

#ifndef RX_H_
#define RX_H_

uint8_t counted_edges;
uint32_t edge_delta_sum;
uint32_t bitrate;
uint32_t bitrate_fourth;

#endif /* RX_H_ */

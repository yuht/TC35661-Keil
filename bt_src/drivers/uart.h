/*
 * uart.h
 *
 *  Created on: 23.7.2014
 *      Author: horinek
 */

#ifndef UART_H_
#define UART_H_

#include "../xlib/core/usart.h"

void uart_init_buffers();
void uart_init();
void uart_low_speed();
void uart_stop();
void uart_send(char * msg);

extern Usart uart;



#endif /* UART_H_ */

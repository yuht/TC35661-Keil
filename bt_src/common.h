/*
 * common.h
 *
 *  Created on: 12.9.2014
 *      Author: horinek
 */

#ifndef COMMON_H_
#define COMMON_H_



#include "string.h"
#include "stdio.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif


//typedef unsigned char 		uint8_t;
//typedef unsigned short int 	uint16_t;
//typedef unsigned int 		uint32_t;
//typedef unsigned long int 	uint64_t;

//typedef char 		int8_t;
//typedef short int 	int16_t;
//typedef int 		int32_t;
//typedef long int 	int64_t;

#define MEDIUM			2
#define BUFFER_SIZE	    64
#define HW_REW_1504		0
#define hw_revision		HW_REW_1504

//#define DEBUG_UART_PWR_ON
//#define DEBUG_UART_PWR_OFF

#define PSTR(A) 	(char *)(A)
#define strcpy_P   	strcpy 

#define GetID_str(destid)  			strcpy(destid,"012345678") //23 b

#define eeprom_busy_wait()
#define eeprom_update_block(A,B,C)
#define pgm_read_byte(A)   			*A
#define _delay_ms(A) 		//		delay_ms(A)

//extern void delay_ms(u16 nms);

extern uint32_t task_get_ms_tick(void );

#define CreateStdOut(file, putc)  

#define fprintf_P( A , B , C ) \
	for (uint8_t i = 0; i < strlen(this->label); i++) \
		this->StreamWrite(this->label[i]) \
 
#define PROGMEM
#define GpioSetDirection(a, c)
#define GpioWrite(a, c)
#define GpioSetPull(A, B)
#define GpioSetInterrupt(A, B, C)
#define gpio_interrupt1 0
#define gpio_rising 0

#define BT_UART     0

#define BT_UART_PWR_OFF
#define BT_UART_PWR_ON
#define gpio_pull_down 0
#define eeprom_read_byte(A) 	BT_PAN1026
#define ISR(A)  				void UNUSEDFUNCTION_##A (void)

#define gui_showmessage_P(A) 	printf(A)
#define DEBUG printf


struct cfg_connectivity
{ 
	uint8_t bt_link_key[16];
};


struct cfg_t
{
	cfg_connectivity connectivity;
};

extern volatile struct cfg_t config;
#define config_ee config
#define config_ro config



#ifdef __cplusplus
}
#endif


#endif /* COMMON_H_ */

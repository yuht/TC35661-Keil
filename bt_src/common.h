/*
 * common.h
 *
 *  Created on: 12.9.2014
 *      Author: horinek
 */

#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG_BT_ENABLED

#ifdef DEBUG_BT_ENABLED
	#define DEBUG_BT(...) DEBUG(__VA_ARGS__)
#else
	#define DEBUG_BT(...)
#endif

#define BT_DISABLE_UART_RTSCTS //½ûÓÃÁ÷¿Ø



#include "string.h"
#include "stdio.h"
#include "delay.h"

#define LOW			0
#define HIGH		1
#define BT_EN		2
#define BT_RESET	3
#define BT_RTS		4


#define PROGMEM
#define BT_UART_PWR_OFF
#define BT_UART_PWR_ON
#define eeprom_busy_wait()
#define eeprom_update_block(A,B,C)
	
	
#define MEDIUM			2
#define BUFFER_SIZE	    64
#define HW_REW_1504		0
#define hw_revision		HW_REW_1504


#define PSTR(A) 		(char *)(A)
#define strcpy_P(A,B)   \
		do{\
			strcpy (A,"Yuht_TC35661-501");	\
			DEBUG_BT("%s\r\n" ,A);	\
		}while(0);


extern uint8_t device_id[11]; //11byte

extern void GetID_str(char * id); //22 byte


#define pgm_read_byte(A)	*A
#define _delay_ms(A)		delay_ms(A)

extern void GpioWrite(uint8_t Port, uint8_t Stat);
extern uint32_t task_get_ms_tick(void );

#define CreateStdOut(file, putc)  

#define fprintf_P( A , B , C ) \
	for (uint8_t i = 0; i < strlen(this->label); i++) \
		this->StreamWrite(this->label[i]) \
 

#define GpioSetDirection(a, c)
#define GpioSetPull(A, B)
#define GpioSetInterrupt(A, B, C)
#define gpio_interrupt1 		0
#define gpio_rising 			0

#define BT_UART     			0


#define gpio_pull_down 			0
#define eeprom_read_byte(A) 	BT_PAN1026
#define ISR(A)  				void UNUSEDFUNCTION_##A (void)

#define DEBUG 					printf
#define gui_showmessage_P		DEBUG_BT



typedef struct tg2
{ 
	uint8_t bt_link_key[16];
	//add
	uint8_t btle_mac[6];
	//end add
}cfg_connectivity;


typedef struct tg1 
{
	cfg_connectivity connectivity;

}cfg_t;

extern volatile  cfg_t config;
#define config_ee config
#define config_ro config






#endif /* COMMON_H_ */

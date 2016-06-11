/*
 * common.h
 *
 *  Created on: 12.9.2014
 *      Author: horinek
 */

#ifndef COMMON_H_
#define COMMON_H_


#define BT_DISABLE_UART_RTSCTS //禁用流控


#include "string.h"
#include "stdio.h"
#include "delay.h"


// 引脚和状态定义
#define LOW			0
#define HIGH		1
#define BT_EN		2
#define BT_RESET	3
#define BT_RTS		4

//空定义，否则编译出错
#define PROGMEM
#define BT_UART_PWR_OFF
#define BT_UART_PWR_ON
#define eeprom_busy_wait()
#define eeprom_update_block(A,B,C)
#define GpioSetDirection(a, c)
#define GpioSetPull(A, B)
#define GpioSetInterrupt(A, B, C)
#define CreateStdOut(file, putc)  


//为了不出错
#define MEDIUM					0
#define BUFFER_SIZE	    		0
#define gpio_interrupt1 		0
#define gpio_rising 			0
#define BT_UART     			0
#define gpio_pull_down 			0

//和实际程序相关内容
#define HW_REW_1504				0
#define hw_revision				HW_REW_1504


#define pgm_read_byte(A)		*A
#define _delay_ms(A)			delay_ms(A)
#define PSTR(A) 				(char *)(A)
#define eeprom_read_byte(A) 	BT_PAN1026
#define ISR(A)  				void UNUSEDFUNCTION_##A (void)
#define DEBUG 					printf
#define gui_showmessage_P		DEBUG_BT
#define config_ee 				config
#define config_ro 				config

#define strcpy_P(A,B)   \
		do{\
			strcpy (A,"Yuht_TC35661-501");	\
			DEBUG_BT("%s\r\n" ,A);	\
		}while(0);


#define fprintf_P( A , B , C ) \
	for (uint8_t i = 0; i < strlen(this->label); i++) \
		this->StreamWrite(this->label[i]) \

		
extern uint8_t 	device_id[11]; //11byte
extern void 	GetID_str(char * id); //22 byte
extern void 	GpioWrite(uint8_t Port, uint8_t Stat);
extern uint32_t task_get_ms_tick(void );
extern void		reset_pin_high(void);
extern void		reset_pin_low(void);

extern void BtRecDataToHost(uint8_t *BtRecdata, uint16_t len);
		
typedef struct
{ 
	uint8_t bt_link_key[16]; 
	uint8_t btle_mac[6]; 
}cfg_connectivity;


typedef struct
{
	cfg_connectivity connectivity;
}cfg_t;

extern volatile  cfg_t config;


#endif /* COMMON_H_ */


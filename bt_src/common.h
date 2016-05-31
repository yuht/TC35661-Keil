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


#ifdef __cplusplus
extern "C" {
#endif



#define MEDIUM	2
#define BUFFER_SIZE	    64
#define HW_REW_1504		0

#define DEBUG_UART_PWR_ON
#define DEBUG_UART_PWR_OFF

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;

typedef uint8_t register8_t;

uint32_t task_get_ms_tick();

/* Universal Synchronous/Asynchronous Receiver/Transmitter */
typedef struct USART_struct
{
    register8_t DATA;  /* Data Register */
    register8_t STATUS;  /* Status Register */
    register8_t reserved_0x02;
    register8_t CTRLA;  /* Control Register A */
    register8_t CTRLB;  /* Control Register B */
    register8_t CTRLC;  /* Control Register C */
    register8_t BAUDCTRLA;  /* Baud Rate Control Register A */
    register8_t BAUDCTRLB;  /* Baud Rate Control Register B */
} USART_t;

#define PORT_t uint8_t



#define PSTR(A) (unsigned char *)(A)
extern char *strcpy_P( char *, unsigned char *);
extern uint8_t hw_revision;
void GetID_str(char * id); //22 b

typedef unsigned char uint8_t;


#define eeprom_busy_wait()
#define eeprom_update_block(A,B,C)
#define pgm_read_byte(A)  *A
#define _delay_ms(A)
#define fprintf_P( A , B , C ) // sprintf( A , B , C )

#define PROGMEM
#define GpioSetDirection(a, c)
#define GpioWrite(a, c)
#define GpioSetPull(A, B)
#define GpioSetInterrupt(A, B, C)
#define gpio_interrupt1 0
#define gpio_rising 0

#define DEBUG_UART  0,0,0,0
#define BT_UART     0,0,0,0

#define BT_UART_PWR_OFF
#define BT_UART_PWR_ON
#define gpio_pull_down 0
#define eeprom_read_byte(A) BT_PAN1026
#define ISR(A)  void UNUSEDFUNCTION_##A (void)

#define gui_showmessage_P(A)
#define DEBUG printf

#ifdef __cplusplus
}
#endif

class DataBuffer
{
public:
	uint8_t * data;

	uint16_t size;
	uint16_t length;
	uint16_t write_index;
	uint16_t read_index;

	DataBuffer(uint16_t size);
	~DataBuffer();

	uint16_t Read(uint16_t len, uint8_t * * data);
	bool Write(uint16_t len, uint8_t * data);

	uint16_t Length();
	void Clear();
};

struct cfg_connectivity
{
	uint8_t usb_mode;

	uint8_t use_gps;
	uint8_t gps_format_flags;

	uint8_t use_bt;
	uint8_t bt_link_key[16];

	uint8_t forward_gps;
	uint8_t protocol;

	uint8_t uart_function;
};


struct cfg_t
{


	cfg_connectivity connectivity;
};

extern volatile cfg_t config;
extern struct cfg_t config_ee,config_ro;



/**
 * Define Out FILE and using putc as output method/function
 *
 * \param file FILE name
 * \param putc method/function with no parameter returning uint8_t byte
 *
 * \note this macro have to be used outside of method/function
 */
#define CreateStdOut(file, putc) //\
	int xlib_stdout_ ## file ## _call(char data, FILE * stream) \
	{ \
		putc(data); \
		return 0;\
	} \
	\
	static FILE file ## _wrap = FDEV_SETUP_STREAM(xlib_stdout_ ## file ## _call, NULL, _FDEV_SETUP_WRITE); \
	FILE * file = &file ## _wrap;



//========================
#endif /* COMMON_H_ */

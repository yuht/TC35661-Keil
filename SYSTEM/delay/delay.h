#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

	
extern void delay_ms(u16 nms);
	
extern void delay_s(u16 ns);


#ifdef __cplusplus
}
#endif

#endif


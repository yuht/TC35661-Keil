
#include "stm32f10x.h"


#ifndef __PLUSC2C_H__
#define __PLUSC2C_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "stm32f10x.h"
//#include "bt.h"
	
void C_bt_init(void);
void C_bt_stop(void);
void C_bt_step(void);

void C_bt_module_reset(void);
void C_bt_module_init(void);
void C_bt_module_deinit(void);

uint8_t C_bt_device_active(void);

void C_bt_send(char * str);

uint8_t C_bt_selftest(void);


#ifdef __cplusplus
}
#endif


#endif
	

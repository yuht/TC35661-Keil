#include "sys.h"
#include "common.h"
#include "drivers/uart.h"
#include <string.h>

uint8_t device_id[11]={0,1,2,3,4,5,6,7,8,9,10};

uint32_t task_get_ms_tick(void)
{
	return ms_timer;
}

volatile cfg_t config;


void GetID_str(char * id) //23 b
{
	uint8_t * b = device_id;

	sprintf(id, PSTR("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"), b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10]);
}

void GpioWrite(uint8_t Port, uint8_t Stat)
{
// LOW			0
// HIGH			1
// BT_EN		2
// BT_RESET		3
// BT_RTS		4
	if(Port == BT_RESET)
	{
		PAout(12) = Stat;
	}
	
}


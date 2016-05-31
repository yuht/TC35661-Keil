#include "common.h"
#include "drivers/uart.h"
#include <string.h>

uint32_t task_get_ms_tick()
{
	return 00000000l;
}

volatile struct cfg_t config;

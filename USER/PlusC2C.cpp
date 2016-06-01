
#include "plusc2c.h"
#include "bt.h"

void C_bt_init(void)
{
	bt_init();
}

void C_bt_stop(void)
{
	bt_stop();
}

void C_bt_step(void)
{
	bt_step();
}

void C_bt_module_reset(void)
{
	bt_module_reset();
}

void C_bt_module_init(void)
{
	bt_module_init();
}

void C_bt_module_deinit(void)
{
	bt_module_deinit();
}

uint8_t C_bt_device_active(void)
{
	return bt_device_active();
}

void C_bt_send(char * str)
{
	bt_send(str);
}

void C_bt_irgh(uint8_t type, uint8_t * buf)
{
	bt_irgh(type, buf);
}

uint8_t C_bt_selftest(void)
{
	return bt_selftest();
}

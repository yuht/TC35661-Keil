#include "sys.h"
#include "common.h"
//#include "drivers/uart.h"
#include <string.h>

#include "plusc2c.h"
#include "bt.h"
#include "sys.h"
#include "usart.h"

uint8_t device_id[11]={0,1,2,3,4,5,6,7,8,9,10};
volatile uint8_t Uart2_pos=0;

// 获取系统时钟函数，作为pan1026.cpp状态机的延时时钟
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

//reset引脚拉高，回复正常
void reset_pin_high(void)
{
	PAout(12) = 1;
}

//reset引脚拉低，引发复位
void reset_pin_low(void)
{
	PAout(12) = 0;
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
		if(Stat){
			reset_pin_high();
		}else{
			reset_pin_low();
		}
	}
	
}



//串口缓冲初始化
void Usart::InitBuffers(uint8_t rx_size, uint8_t tx_size)
{
	Uart2_RcvCnt = 0;
	Uart2_pos = 0; 
}

//串口空检测
bool Usart::isRxBufferEmpty()
{
	return !(Uart2_RcvCnt - Uart2_pos);
}

//清理缓冲
void Usart::ClearRxBuffer()
{
	Uart2_RcvCnt = 0;
	Uart2_pos = 0; 
}

//空函数
void Usart::SetInterruptPriority(uint8_t p)
{ 
}
 
//写数据到tc35661的rx引脚
void Usart::Write(uint8_t c)
{
	Uart2SendHex(c); 
}

//读取串口缓冲区数据
uint8_t Usart::Read()
{
	uint8_t c;
	
	c = Uart2_Buff[Uart2_pos++];
	
	if(Uart2_RcvCnt == Uart2_pos){
		Uart2_RcvCnt = Uart2_pos = 0;
	}

	return c;

}

//数据明文输出，处理tc35661接收到的数据，解析协议后的明文数据。
void BtRecDataToHost(uint8_t *BtRecdata, uint16_t len)
{
	while(len--){
		Uart1SendHex(*(BtRecdata++));
	}
}



//蓝牙初始化
void C_bt_init(void)
{
	bt_init();
}

//蓝牙停止
void C_bt_stop(void)
{
	bt_stop();
}

//蓝牙模块状态机调用接口
void C_bt_step(void)
{
	bt_step();
}
//蓝牙模块复位
void C_bt_module_reset(void)
{
	bt_module_reset();
}
//蓝牙模块初始化
void C_bt_module_init(void)
{
	bt_module_init();
}

//注销蓝牙模块
void C_bt_module_deinit(void)
{
	bt_module_deinit();
}
//初始化状态
uint8_t C_bt_device_active(void)
{
	return bt_device_active();
}
//发送数据给蓝牙rx引脚
void C_bt_send(char * str, uint16_t len)
{
	bt_send(str,len);
}


//自测状态是否正常可用
uint8_t C_bt_selftest(void)
{
	return bt_selftest();
}





Usart::Usart()
{
	
}


Usart::~Usart()
{ 
	
}

///**
// * Initialize usart
// *
// * \param usart Usart structure
// * \param port Port structure
// * \param tx Number of tx pin
// * \param n Object index for ISR handling
// * \param baud Baudrate
// *
// * \note There are predefined usart modules like usart0, usart1 which contains usart and port structure, tx pin number and module index
// */
void Usart::Init(uint8_t usart,uint32_t baud)
{ 
	
}

void Usart::Stop()
{
//	return (this->rx_len == 0);
}

void Usart::TxComplete()
{
	
}



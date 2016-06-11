//***********************************************************

#include "sys.h"
#include "plusc2c.h"

//***********************************************************

#define STR(A) 	(unsigned char*)(A)



int main ( void )
{
	
	uint8_t static ledstat;
	SystemInit();//系统时钟等初始化
	if(SysTick_Config(72000*1))	 //配置错误返回1,max 16777216   默认72Mhz 时钟 ,1ms延时
	{							
		LED4_ON; 	//错误处理 		
		while(1);
	}
	
	LED_Init();	 //LED端口初始化
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart1Init ( 115200 ); //串口初始化为115200
	Uart2Init ( 115200 ); //串口初始化为115200
	Uart3Init ( 115200 );//串口初始化为115200

	Uart1SendStr(STR("uart1 init\r\n"));

	Uart2SendStr(STR("uart2 init\r\n"));

	Uart3SendStr(STR("uart3 init\r\n"));


//	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD , ENABLE );
//	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );
//	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOD, ENABLE );

	
//	GPIO_Configuration_LCD();
//	GPIO_ResetBits ( GPIOC, GPIO_Pin_10 );
//	LED_LINGHT = 1;
//	LCD_Init();
//	LCD_Clear();
//	LCD_WriteString_en ( 0, 0, PSTR("gsm starting") );
//	LCD_WriteString_en ( 1, 1, PSTR("gsm starting") );
//	LCD_WriteString_en ( 2, 2, PSTR("gsm starting") );
//	LCD_WriteString_en ( 3, 3, PSTR("gsm starting") );
//	LCD_WriteString_en ( 4, 4, PSTR("gsm starting") );
//	Timerx_Init ( 1000, 7199 ); //10Khz的计数频率，1000次为10ms
	
	C_bt_init();
	C_bt_module_reset();
	C_bt_module_init();
	
	 
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	delay_ms ( 500 );
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF; 

	while(1)
	{
		//运行灯
		if( ms_delay_counter >500 ){
			ms_delay_counter = 0;
			if( ledstat ){
				LED1_ON;
			}else{
				LED1_OFF;
			}
			ledstat = !ledstat;
		}
		
		//调用速度特别快会导致初始化失败
		if((ms_timer %10) == 0){
			C_bt_step();
		}
		
		//模块初始化成功检测
		if(C_bt_selftest()){
			LED2_ON;
		}else{
			LED2_OFF;
		}
		
		//模块配对后，通信连接ok
		if(C_bt_device_active()){
			LED3_ON;
			if(Uart1_RcvCnt){
				delay_ms(100);
				//发送数据
				C_bt_send((char*)Uart1_Buff,Uart1_RcvCnt);
				Uart1_RcvCnt = 0;				
			}
		}else{
			LED3_OFF;
		}

	}
}

//***********************************************************

#include "sys.h"
#include "plusc2c.h"
	


//***********************************************************
#define GSM_RST PAout(12)
#define STR(A) (unsigned char*)(A)

void RCC_Configuration(void);

int main ( void )
{
	SystemInit();//系统时钟等初始化

	//delay_init ( 72 );	  //延时初始化
	if(SysTick_Config(1*7200000))	 //配置错误返回1,max 16777216   默认72Mhz 时钟 ,100ms延时
	{							
		LED2_ON; 	//错误处理 								
	}
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart1Init ( 115200 ); //串口初始化为115200
	Uart2Init ( 115200 ); //串口初始化为115200
//	Uart3Init(115200);//串口初始化为115200


	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );
	
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
	LED_Init();	 //LED端口初始化

	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	//delay_s ( 1 );
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	
	GSM_RST = 0; //启动GSM模块

	C_bt_init();
	C_bt_module_reset();
	C_bt_module_init();

	CleanGsmRcv();
//	Uart1SendStr(STR("init \r\n"));
//	printf("test printf function: %s\r\n","abc");
	while(1)
	{
		LED1_ON;
		delay_ms(500);
		LED1_OFF;
		delay_ms(500);
		
	}
	
	
//	//
//	while(1);

//	while ( !Hand ( STR("SIM900") ) ) //与GSM模块握手，判断是否收到GSM模块返回的OK
//	{
//		Uart2SendStr ( STR("ATI\r") ); //打开回显命令
//		delay_s ( 1 );
//	}

//	CleanGsmRcv();//清除接收缓存
//	LED1_ON;



//	while ( ! ( Hand ( STR("+CREG: 1,1") ) || Hand ( STR("+CREG: 1,5") ) ) ) //检测是否以注册到服务商
//	{
//		Uart2SendStr ( STR("AT+CREG=1\r") ); //设置服务商状态为数据显示
//		delay_s ( 1 );
//		Uart2SendStr ( STR("AT+CREG?\r") ); //检测服务商状态
//		delay_s ( 1 );
//	}

//	CleanGsmRcv();//清除接收缓存
//	LED2_ON;

//	while ( 1 )
//	{
//		Uart2SendStr ( STR("AT+CIPCLOSE\r") ); //连接前先关闭先前的连接状态
//		delay_s ( 1 );
//		Uart2SendStr ( STR("AT+CIPSHUT\r") ); //连接前先关闭先前的连接状态
//		delay_s ( 1 );
//		Uart2SendStr ( STR("AT+CLPORT=\"TCP\",\"2022\"\r") ); //发送指令指定本地端口
//		delay_s ( 1 );
//		Uart2SendStr ( STR("AT+CIPHEAD=1\r") ); //发送指令指定本地端口
//		delay_s ( 1 );
//		CleanGsmRcv();//清除接收缓存
//		Uart2SendStr ( STR("AT+CIPSTART=\"TCP\",\"123.79.0.241\",\"8080\"\r") ); //连接服务器地址123.79.0.241，服务器端口号8080

//		while ( ! ( Hand ( STR("CONNECT OK") ) ) ); //检测是否收到 CONNECT OK ,如果这连接成功

//		LED3_ON;
//		Uart2SendStr ( STR("AT+CIPSEND\r") );
//		delay_s ( 1 );
//		Uart2SendStr ( STR("发送LED0或者LED1，对应的LED会点亮哦。") ); //向服务器发送数据
//		delay_s ( 1 );
//		Uart2SendHex ( 0x1a ); //以0x1a结束
//		CleanGsmRcv();//清除接收缓存

//		while ( 1 )
//		{
//			if ( ( Hand ( STR("+IPD") ) && ( Hand ( STR("LED1") ) || Hand ( STR("led1") ) ) ) )
//			{
//				LED4_ON;
//				CleanGsmRcv();//清除接收缓存
//			}

//			if ( ( Hand ( STR("+IPD") ) && ( Hand ( STR("LED0") ) || Hand ( STR("led0") ) ) ) )
//			{
//				LED4_OFF;
//				CleanGsmRcv();//清除接收缓存
//			}
//		}

//	}

}




 
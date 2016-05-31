/***********************************************************
酷学之家 http://simcom.taobao.com/
联系方式：15296811438 林工
*************************************************************/

#include "sys.h"

/************************************************************
程序说明：
本程序实现开机自动拨打电话10086
1.我们的程序全部都是通过单片机串口2与SIM900通讯，串口1用于下载程序和观察SIM900返回的数据
（串口2收到的SIM900返回的数据会通过串口1发送到电脑中，用于观察数据），使用过程中，如果没
有特殊要求跳线帽不用变动。
2.在开发板上放入您的手机卡，接好天线，打开电源，接入耳机。
3.把程序编译后下载到单片机中，使用KEIL4下载，具体请参照教程。
4.使用浏览器打开网页http://www.ip138.com/。查询自己的外网ip地址。将ip地址修改到程序87行处。编译程序。
5.在光盘中找到 调试工具\NetAssist\NetAssist.exe 打开，协议类型：tcp服务器、ip地址默认,本地端口8080,最后点击连接。
6.程序自动连接上写入的ip地址，后发送数据到服务器。
7.服务器软件NetAssist.exe看到发送的数据后，可以在输入框内输入LED0或者LED1，此时LED4会被点亮或者熄灭。
*************************************************************/
#define GSM_RST PAout(12)
#define PSTR(A) (unsigned char*)(A)


int main ( void )
{
	SystemInit();//系统时钟等初始化
	delay_init ( 72 );	  //延时初始化
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart1Init ( 115200 ); //串口初始化为115200
	Uart2Init ( 115200 ); //串口初始化为115200
	Uart3Init(115200);//串口初始化为115200


	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );
	GPIO_Configuration_LCD();
	GPIO_ResetBits ( GPIOC, GPIO_Pin_10 );
//	LED_LINGHT = 1;
	LCD_Init();
	LCD_Clear();
//	LCD_WriteString_en ( 0, 0, PSTR("gsm starting") );
//	LCD_WriteString_en ( 1, 1, PSTR("gsm starting") );
//	LCD_WriteString_en ( 2, 2, PSTR("gsm starting") );
//	LCD_WriteString_en ( 3, 3, PSTR("gsm starting") );
//	LCD_WriteString_en ( 4, 4, PSTR("gsm starting") );
	Timerx_Init ( 1000, 7199 ); //10Khz的计数频率，1000次为10ms
	LED_Init();	 //LED端口初始化

	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	delay_s ( 1 );
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;

	GSM_RST = 0; //启动GSM模块

	CleanGsmRcv();

	while ( !Hand ( PSTR("SIM900") ) ) //与GSM模块握手，判断是否收到GSM模块返回的OK
	{
		Uart2SendStr ( PSTR("ATI\r") ); //打开回显命令
		delay_s ( 1 );
	}

	CleanGsmRcv();//清除接收缓存
	LED1_ON;



	while ( ! ( Hand ( PSTR("+CREG: 1,1") ) || Hand ( PSTR("+CREG: 1,5") ) ) ) //检测是否以注册到服务商
	{
		Uart2SendStr ( PSTR("AT+CREG=1\r") ); //设置服务商状态为数据显示
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CREG?\r") ); //检测服务商状态
		delay_s ( 1 );
	}

	CleanGsmRcv();//清除接收缓存
	LED2_ON;

	while ( 1 )
	{
		Uart2SendStr ( PSTR("AT+CIPCLOSE\r") ); //连接前先关闭先前的连接状态
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CIPSHUT\r") ); //连接前先关闭先前的连接状态
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CLPORT=\"TCP\",\"2022\"\r") ); //发送指令指定本地端口
		delay_s ( 1 );
		Uart2SendStr ( PSTR("AT+CIPHEAD=1\r") ); //发送指令指定本地端口
		delay_s ( 1 );
		CleanGsmRcv();//清除接收缓存
		Uart2SendStr ( PSTR("AT+CIPSTART=\"TCP\",\"123.79.0.241\",\"8080\"\r") ); //连接服务器地址123.79.0.241，服务器端口号8080

		while ( ! ( Hand ( PSTR("CONNECT OK") ) ) ); //检测是否收到 CONNECT OK ,如果这连接成功

		LED3_ON;
		Uart2SendStr ( PSTR("AT+CIPSEND\r") );
		delay_s ( 1 );
		Uart2SendStr ( PSTR("发送LED0或者LED1，对应的LED会点亮哦。") ); //向服务器发送数据
		delay_s ( 1 );
		Uart2SendHex ( 0x1a ); //以0x1a结束
		CleanGsmRcv();//清除接收缓存

		while ( 1 )
		{
			if ( ( Hand ( PSTR("+IPD") ) && ( Hand ( PSTR("LED1") ) || Hand ( PSTR("led1") ) ) ) )
			{
				LED4_ON;
				CleanGsmRcv();//清除接收缓存
			}

			if ( ( Hand ( PSTR("+IPD") ) && ( Hand ( PSTR("LED0") ) || Hand ( PSTR("led0") ) ) ) )
			{
				LED4_OFF;
				CleanGsmRcv();//清除接收缓存
			}
		}

	}

}



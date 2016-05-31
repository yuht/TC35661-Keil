

#include "sys.h"
  
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    

void _ttywrch(int ch)
{
    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕    
    USART1->DR = (u8) ch;  
}

int _sys_exit(int x) 
{ 
	return 0;
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕    
    USART1->DR = (u8) ch;      
	return 0;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/

u8 GsmRcv[MAXRCV] = {0};
u16 GsmRcvCnt = 0;
u16 Debug1RcvCnt = 0;
u8 DebugBuf_U1[MAXBUF] = {0};

u8 DebugBuf_U2[MAXBUF] = {0};
u16 Debug2RcvCnt = 0;



void Uart1Init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}

void Uart1SendHex(u8 ch)
{
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch; 
}

void Uart1SendStr(u8* str)
{
	u16 cnt=0;
	while(*(str+cnt))	//判断一串数据是否结束
	{
		while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	    USART1->DR = *(str+cnt);
		cnt++;	//准备发送一个数据
	}
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 tmp;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		tmp =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据

//#ifdef UART1_DEBUG
		//将接收到的数据放入DebugBuf_U1，在定时器内，DebugBuf_U1会被串口2发送给GSM模块。
		//这样通过串口1发送到单片机的数据GSM模块就可以收到了，主要为了调试的方便。
		DebugBuf_U1[Debug1RcvCnt] = tmp;
		Debug1RcvCnt++;
		if(Debug1RcvCnt>=MAXBUF-1)
		{
			Debug1RcvCnt = 0;	
		}
//#endif


		
	}
}


void Uart2Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
     //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART2
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_DeInit(USART2);
    USART_Init(USART2, &USART_InitStructure);
   

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART2, ENABLE);                    //使能串口 
	
}

void USART2_IRQHandler(void)                	//串口3中断服务程序
{
	u8 tmp;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
		tmp = USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据

		GsmRcv[GsmRcvCnt] = tmp;
		GsmRcvCnt++;
		if(GsmRcvCnt > MAXRCV)
		{
			GsmRcvCnt = 0;
		}
				
//#ifdef UART1_DEBUG
		//将接收到的数据放入DebugBuf_U3，在定时器内，DebugBuf_U3会被串口1发送给GSM模块。
		//这样通过串口1发送到单片机的数据GSM模块就可以收到了，主要为了调试的方便。
		DebugBuf_U2[Debug2RcvCnt] = tmp;
		Debug2RcvCnt++;
		if(Debug2RcvCnt>=MAXBUF-1)
		{
			Debug2RcvCnt = 0;	
		}
//#endif
		
	}
}

void Uart2SendHex(u8 ch)
{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//发送完毕
		USART_SendData(USART2, ch);
}

void Uart2SendStr(u8* str)
{
	u16 cnt=0;
	while(*(str+cnt))	//判断一串数据是否结束
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//发送完毕
		USART_SendData(USART2, *(str+cnt));
		cnt++;	//准备发送一个数据
	}
}



void Uart3Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
     //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart3 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART3
  
   //USART 初始化设置

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  //RCC_APB1_USART3使能
	USART_InitStructure.USART_BaudRate = 9600;  //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //数据字长8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //停止位为1
	USART_InitStructure.USART_Parity = USART_Parity_No;  //奇偶失能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //发送使能  接收使能
	USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART3, ENABLE);                    //使能串口
}

void USART3_IRQHandler(void)                	//串口3中断服务程序
{

}

void Uart3SendHex(u8 ch)
{
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch; 
}

void Uart3SendStr(u8* str)
{
	u16 cnt=0;
	while(*(str+cnt))	//判断一串数据是否结束
	{
		while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	    USART3->DR = *(str+cnt);
		cnt++;	//准备发送一个数据
	}
}

void CleanGsmRcv(void)
{
	u16 i = 0;
	for(i=0; i<=MAXRCV; i++)
	{
		GsmRcv[i] = 0;	
	}

	GsmRcvCnt = 0;	
}

u8 Hand(unsigned char *a)
{ 
    if(strstr((const char *)GsmRcv,(const char *)a)!=NULL)
	    return 1;
	else
		return 0;
}

 

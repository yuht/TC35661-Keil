#ifndef __STM32_USART_H
#define __STM32_USART_H
#include "stdio.h"
#include "string.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/5/27
//版本：V1.3
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//////////////////////////////////////////////////////////////////////////////////
#define UART1_DEBUG 
#define MAXRCV 255
#define MAXBUF 255

extern u8 GsmRcv[MAXRCV];
extern u16 GsmRcvCnt;

extern u8 DebugBuf_U1[MAXBUF];
extern u16 Debug1RcvCnt;

extern u8 DebugBuf_U2[MAXBUF];
extern u16 Debug2RcvCnt;

extern u8 DebugBuf_U3[MAXBUF];
extern u16 Debug3RcvCnt;



void Uart1Init(u32 bound);
void Uart1SendHex(u8 ch);
void Uart1SendStr(u8* str);
void Uart2Init(u32 bound);
void Uart2SendHex(u8 ch);
void Uart2SendStr(u8* str);
void Uart3Init(u32 bound);
void Uart3SendHex(u8 ch);
void Uart3SendStr(u8* str);
void CleanGsmRcv(void);


u8 Hand(unsigned char *a);

#endif

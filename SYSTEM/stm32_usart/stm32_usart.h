#ifndef __STM32_USART_H
#define __STM32_USART_H

#define MAXBUF 255


extern u8 Uart1_Buff[MAXBUF];
extern u16 Uart1_RcvCnt;

extern u8 Uart2_Buff[MAXBUF];
extern u16 Uart2_RcvCnt;

extern u8 Uart3_Buff[MAXBUF];
extern u16 Uart3_RcvCnt;



void Uart1Init(u32 bound);
void Uart1SendHex(u8 ch);
void Uart1SendStr(u8* str);
void Uart2Init(u32 bound);
void Uart2SendHex(u8 ch);
void Uart2SendStr(u8* str);
void Uart3Init(u32 bound);
void Uart3SendHex(u8 ch);
void Uart3SendStr(u8* str);

#endif

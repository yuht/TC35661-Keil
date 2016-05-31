 #ifndef __5110LCD_H
 #define __5110LCD_H

 #include "stm32f10x.h"	
///////////////////////////////////////////////////////
//------------------------------------/				 //
// SCE    ------------PA5  //片选					 //
// RST    ------------PA4  //位选					 //
//  D/C    ------------PA3  // 1写数据，0写指令		 //
// SD     ------------PA2	   //数据				 //
// SCLK   ------------PA1	   //时钟				 //
// LCD    ------------PA0      //背光				 //
///////////////////////////////////////////////////////
    /*
  PB6-RST
  PB5-CE
  PD2-DC
  PC12-DIN
  PC11-CLK
  PC10-LED
  */
 #define sce0   GPIO_ResetBits(GPIOB, GPIO_Pin_5)  //片选CE
 #define res0   GPIO_ResetBits(GPIOB, GPIO_Pin_6)  //复位RST,0复位
 #define dc0    GPIO_ResetBits(GPIOD, GPIO_Pin_2)   //DC 1写数据，0写指令
 #define sdin0  GPIO_ResetBits(GPIOC, GPIO_Pin_12)   //数据DIN
 #define sclk0  GPIO_ResetBits(GPIOC, GPIO_Pin_11)   //时钟CLK


 #define sce1   GPIO_SetBits(GPIOB, GPIO_Pin_5)  //片选CE
 #define res1   GPIO_SetBits(GPIOB, GPIO_Pin_6)  //复位RST,0复位
 #define dc1    GPIO_SetBits(GPIOD, GPIO_Pin_2)   //DC 1写数据，0写指令
 #define sdin1  GPIO_SetBits(GPIOC, GPIO_Pin_12)   //数据DIN
 #define sclk1  GPIO_SetBits(GPIOC, GPIO_Pin_11)   //时钟CLK

 #define LED_LINGHT PCout(10)
	    
void GPIO_Configuration_LCD(void);
void LCD_WriteByte(unsigned char dt, unsigned char command);
void LCD_Init(void);
void LCD_Set_XY(unsigned char X, unsigned char Y);
void LCD_Clear(void);
void LCD_WriteChar(unsigned char X,unsigned char Y,unsigned char c);
void LCD_WriteString_en(unsigned char X,unsigned char Y,unsigned char *s);
void LCD_WriteNumber(unsigned char x,unsigned char y, unsigned long number);
void LCD_write_chinese_string(unsigned char X, unsigned char Y,
                              unsigned char ch_with,unsigned char num,
							  unsigned char line,unsigned char row);
void LCD_Write_cn(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符

//void delay_ms(int t);
#endif

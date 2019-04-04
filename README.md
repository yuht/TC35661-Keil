<a href="https://996.icu"><img src="https://img.shields.io/badge/link-996.icu-red.svg" alt="996.icu" /></a>
[![LICENSE](https://img.shields.io/badge/license-Anti%20996-blue.svg)](https://github.com/996icu/996.ICU/blob/master/LICENSE)


# TC35661-Keil
use stm32f103r8tb driver tc35661
Finished. 
If has some ERR , please PULL ISSUES

# wire conn
stm32 uart1 => PC

stm32 uart2 => TC35661

stm32 pin PA12  => tc35661 reset pin


#Rewrite NOTICE
0、硬件上蓝牙需要连接的是串口rx、tx、复位引脚。串口是115200波特率。复位需要拉低引脚，延时，拉高引脚，完成复位

1、原始代码有一处错，蓝牙复位引脚初始化。led.c文件下31行GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;应该改为 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 在stm32上没问题，但是在GD32上就用不了，引脚下拉不了。

2、修改蓝牙复位引脚需要改这么几处:led.c相应引脚初始化；main.c里面第9行#define GSM_RST PAout(12)需要改；common.cpp里面第32行#define GSM_RST PAout(12)需要改.
例如原代码使用的是PA12脚，与usb引脚冲突；而即付宝bz1的pos机里面的对应引脚是PC11

3、usart.cpp文件是一个硬件串口和bt数据的接口链接文件，负责转发数据
在demo中三个串口都已经初始化为115200，默认使用串口一向外发送数据（如ttl小板），串口二向蓝牙模块发送数据。
a、修改与蓝牙模块连接的串口：在usart.cpp文件中，使用查找替换替换该文件中所有Uart2为Uart1或者Uart3即可。
b、修改与向外输出连接的串口：在usart.cpp文件中，216行Uart1SendHex(c)改为Uart2SendHex(c)或Uart3SendHex(c)。
在main.c中，105-108行中if(Uart1_RcvCnt){
delay_ms(100);
C_bt_sendBinary((char*)Uart1_Buff,Uart1_RcvCnt);
Uart1_RcvCnt = 0;这些代码中的Uart1全部改为Uart2或者Uart3即可。	
c、（Uart1为单片机PA9和10，Uart2为PA1和2，Uart3为PB10和11）
d、两个串口不能选相同的
e、即付宝bz1的pos上蓝牙接串口3

4、个人认为106行的delay_ms(100);可以直接删除，提高速度。

5、修改led灯在led.c\led.h中修改。led1和led3为连接成功后闪烁.led2在模块初始化后亮。led4为错误处理

6、C_bt_step();为蓝牙状态机调用。在原程序中，使用SysTick（在stm32f10x_it.h里面配置）调用。移植需保持在循环里面经常调用此状态机（10-50ms？）

7、C_bt_selftest()函数为检测模块初始化是否成功。返回值为1则是初始化成功（手机可搜到）

8、C_bt_device_active()函数为检测模块是否连接成功的。返回值为1则为与主机连接成功
此时可传数据

9、78-90行的if( ms_delay_counter >500 ){}内代码可直接删除，这是测试代码

10、主要数据处理是在bt.cpp文件里面，移植不用理会

11、在复位引脚拉高之前，需要先执行这三个初始化函数C_bt_init();C_bt_module_reset();
C_bt_module_init();
（demo中在55行）

12、向蓝牙模块发送透传数据调用这些函数C_bt_send()C_bt_sendBinary()
eg:C_bt_send("test str");C_bt_sendBinary((char*)Uart1_Buff,Uart1_RcvCnt);
sendBinary函数中，第一个变量是缓存区指针（char*），第二个变量为数据长度

13、调试中可开启debug模式，在common.h文件中，第11行，解除//#define DEBUG_BT_ENABLED屏蔽，则会向用户发送debug信息。

14、修改到12mhz晶振下运行需要修改两个地方
a、system_stm32f10x.c文件下，1080行和1085行修改RCC_CFGR_PLLMULL9为RCC_CFGR_PLLMULL6
b、stm32f10x_it.h文件下，119行#define HSE_VALUE((uint32_t)8000000) 改为#define HSE_VALUE((uint32_t)12000000) 


15、一般移植不成功的（即上电后搜索不到蓝牙），问题都在复位不成功，开启debug后，可以看到串口返回的数据为
BT RESET STEP：0
BT RESET STEP：1
BT RESET STEP：2
这里有几种可能，可能性最大的是复位不成功，重新检查复位引脚是否接对，是否初始化；
接线不对，串口号和程序里面的不一样；
反正就是检测复位，实在不行在蓝牙模块串口输出引脚接一根线连到ttl小板上来看是否有04开头的数据过来。如果没有，检查复位问题、电源问题，如果有，检测串口问题


16、demo中串口处理方式的效率不高，可能会丢包什么的，要想提高速率，可尝试fifo，环形缓存区、dma等等方法，自行研究。连续大量数据可能会出问题

17、数据包可能会有最长长度限制

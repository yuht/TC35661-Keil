

#include "sys.h"

void delay_ms(u16 nms)
{	 		  	  
	ms_delay_counter = 0;
	while(ms_delay_counter < nms);
}
void delay_s(u16 ns)
{
	u16 i;
	for(i=0; i<ns; i++)
	{
		delay_ms(1000); 	
	}
}



































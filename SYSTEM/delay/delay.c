

#include "sys.h"

void delay_ms(u16 nms)
{	 		  	  
	ms_delay = 0;
	while(ms_delay < nms);
}
void delay_s(u16 ns)
{
	u16 i;
	for(i=0; i<ns; i++)
	{
		delay_ms(1000); 	
	}
}



































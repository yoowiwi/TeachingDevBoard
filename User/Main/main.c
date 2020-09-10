
#include "include.h"

uint32_t cnt = 0;

int main(int argc,char* argv[])
{
	
	LED_InitConfig();
	KEY_InitConfig();
	
	
	while(1)
	{
		cnt ++ ;
		rt_thread_delay(500);
		LED5_TOGGLE;
		rt_kprintf("hello world[%d]\n",cnt);
		rt_thread_delay(500);
	}
}



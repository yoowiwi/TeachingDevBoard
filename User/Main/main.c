
#include "include.h"

int main(int argc,char* argv[])
{
	
	LED_InitConfig();
	KEY_InitConfig();
	
	while(1)
	{
		rt_thread_delay(500);
		LED5_TOGGLE;
		rt_thread_delay(500);
	}
}



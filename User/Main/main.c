
#include "include.h"

uint32_t cnt = 0;
char buff[] = {};

int main(int argc,char* argv[])
{
	
	LED_InitConfig();
	KEY_InitConfig();
	OLED_InitConfig();
	
	OLED_ShowString(0,0,"Hello World");
	OLED_Refresh_Gram();
	
	while(1)
	{
		cnt ++ ;
		rt_thread_delay(500);
		LED5_TOGGLE;
		rt_kprintf("hello world[%d]\n",cnt);
		OLED_Clear();
		rt_sprintf(buff,"%d",cnt);
		OLED_ShowString(60,0,buff);
		OLED_Refresh_Gram();
		rt_thread_delay(500);
	}
}




#include "include.h"

void LED_InitConfig(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(LED_RCC,ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Pin = LED5_Pin;
	GPIO_Init(LED5_GPIOx,&gpio);
	gpio.GPIO_Pin = LED6_Pin;
	GPIO_Init(LED6_GPIOx,&gpio);
	gpio.GPIO_Pin = LED7_Pin;
	GPIO_Init(LED7_GPIOx,&gpio);
	
	LED5_OFF;LED6_OFF;LED7_OFF;
}



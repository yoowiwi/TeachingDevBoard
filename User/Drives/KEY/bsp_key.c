
#include "include.h"

void KEY_InitConfig(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(KEY_RCC,ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = KEY_Pin;
	GPIO_Init(KEY_GPIOx,&gpio);
}



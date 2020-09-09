#ifndef _LED
#define _LED

#include "include.h"

#define LED_RCC				RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC

#define LED5_GPIOx		GPIOC
#define LED5_Pin			GPIO_Pin_5
#define LED6_GPIOx		GPIOB
#define LED6_Pin			GPIO_Pin_0
#define LED7_GPIOx		GPIOB
#define LED7_Pin			GPIO_Pin_1

#define LED5_ON				LED5_GPIOx->BRR		= LED5_Pin
#define LED5_OFF			LED5_GPIOx->BSRR	= LED5_Pin
#define LED6_ON				LED6_GPIOx->BRR 	= LED6_Pin
#define LED6_OFF			LED6_GPIOx->BSRR 	= LED6_Pin
#define LED7_ON				LED7_GPIOx->BRR 	= LED7_Pin
#define LED7_OFF			LED7_GPIOx->BSRR 	= LED7_Pin

#define LED5_TOGGLE		LED5_GPIOx->ODR	 ^= LED5_Pin	
#define LED6_TOGGLE		LED6_GPIOx->ODR	 ^= LED6_Pin		
#define LED7_TOGGLE		LED7_GPIOx->ODR	 ^= LED7_Pin			

void LED_InitConfig(void);

#endif


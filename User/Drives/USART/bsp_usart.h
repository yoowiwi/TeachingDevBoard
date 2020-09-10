#ifndef _USART_H
#define	_USART_H

#include "include.h"

#define		USART_CONSOLE		USART1

#define		RCC_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); \
													RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
#define		USART1_GPIO			GPIOA
#define		USART1_TX_Pin		GPIO_Pin_9
#define		USART1_RX_Pin		GPIO_Pin_10


void USART1_InitConfig(uint32_t baud);

char rt_hw_console_getchar(void);
void rt_hw_console_output(const char *str);

void usart_send_byte(USART_TypeDef * pUSARTx, uint8_t ch);
void usart_send_string(USART_TypeDef * pUSARTx, char *str);

#endif



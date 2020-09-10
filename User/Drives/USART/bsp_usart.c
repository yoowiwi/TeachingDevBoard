
#include "include.h"

char rt_hw_console_getchar(void)
{
    int ch = -1;
    if (USART_GetFlagStatus(USART_CONSOLE, USART_FLAG_RXNE) != RESET)
    {
        ch = USART_CONSOLE->DR & 0xff;
				USART_ClearFlag(USART_CONSOLE, USART_FLAG_RXNE);
    }
    else
    {
        if(USART_GetFlagStatus(USART_CONSOLE, USART_FLAG_ORE) != RESET)
        {
            USART_ClearFlag(USART_CONSOLE, USART_FLAG_ORE);
        }
//        rt_thread_mdelay(10); // 会导致只接收到一个字符，原因不详 
    }
    return ch;
}

void rt_hw_console_output(const char *str)
{
	rt_enter_critical();
	while(*str != '\0')
	{
		if(*str == '\n')
		{
			USART_SendData(USART_CONSOLE, '\r');
			while (USART_GetFlagStatus(USART_CONSOLE, USART_FLAG_TXE) == RESET);
		}
		USART_SendData(USART_CONSOLE, *str++);
		while (USART_GetFlagStatus(USART_CONSOLE, USART_FLAG_TXE) == RESET);		
	}
	rt_exit_critical();
}

void USART1_InitConfig(uint32_t baud)
{
	RCC_USART1_ENABLE();
	
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = USART1_TX_Pin;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART1_GPIO,&gpio);
	gpio.GPIO_Pin = USART1_RX_Pin;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART1_GPIO,&gpio);
	
	USART_InitTypeDef usart;
	usart.USART_BaudRate = baud;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&usart);
	USART_Cmd(USART1,ENABLE);
	
}

void usart_send_byte(USART_TypeDef * pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx,ch);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void usart_send_string(USART_TypeDef * pUSARTx, char *str)
{
    unsigned int k = 0;
    do{
        usart_send_byte(pUSARTx, *(str+k));
        k++;
    }while( *(str+k) != '\0' );
    while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

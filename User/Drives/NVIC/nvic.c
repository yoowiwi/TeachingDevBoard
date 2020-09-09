
#include "nvic.h"

void NVIC_Config(uint8_t IRQn, uint8_t PrePri, uint8_t SubPri)
{
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannel = IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = PrePri;
	nvic.NVIC_IRQChannelSubPriority = SubPri;
	NVIC_Init(&nvic);
}


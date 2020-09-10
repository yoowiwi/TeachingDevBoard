#ifndef _OLED_H
#define _OLED_H

#include "include.h"

#define	RCC_OLED_ENABLE()		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);\
														RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
														
#define	OLED_SPIx				SPI1
														
#define	OLED_SCL_GPIO		GPIOA
#define	OLED_SDA_GPIO		GPIOA
#define	OLED_RES_GPIO		GPIOA
#define	OLED_DC_GPIO		GPIOA

#define	OLED_SCL_Pin		GPIO_Pin_5
#define	OLED_SDA_Pin		GPIO_Pin_7
#define	OLED_RES_Pin		GPIO_Pin_6
#define	OLED_DC_Pin			GPIO_Pin_4

#define OLED_SDA_Clr() 	GPIO_ResetBits(OLED_SDA_GPIO,OLED_SDA_Pin)
#define OLED_SCL_Clr() 	GPIO_ResetBits(OLED_SCL_GPIO,OLED_SCL_Pin)
#define OLED_RES_Clr()	GPIO_ResetBits(OLED_RES_GPIO,OLED_RES_Pin)
#define OLED_DC_Clr() 	GPIO_ResetBits(OLED_DC_GPIO,OLED_DC_Pin)

#define OLED_SDA_Set() 	GPIO_SetBits(OLED_SDA_GPIO,OLED_SDA_Pin) 
#define OLED_SCL_Set() 	GPIO_SetBits(OLED_SCL_GPIO,OLED_SCL_Pin)  
#define OLED_RES_Set() 	GPIO_SetBits(OLED_RES_GPIO,OLED_RES_Pin)  
#define OLED_DC_Set() 	GPIO_SetBits(OLED_DC_GPIO,OLED_DC_Pin)  

typedef enum
{
	OLED_CMD,
	OLED_DATA
}OLED_WR_MODE;

void OLED_InitConfig(void);
void oled_write_byte(uint8_t byte,OLED_WR_MODE mod);
void OLED_Refresh_Gram(void);		   					   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowString(u8 x,u8 y,const u8 *p);

#endif

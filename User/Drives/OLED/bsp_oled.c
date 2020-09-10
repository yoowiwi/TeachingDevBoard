
#include "include.h"
#include "font.h"

void OLED_InitConfig()
{
	GPIO_InitTypeDef gpio;
	SPI_InitTypeDef spi1;
	
	RCC_OLED_ENABLE();
	
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = OLED_RES_Pin;
	GPIO_Init(OLED_RES_GPIO,&gpio);
	gpio.GPIO_Pin = OLED_DC_Pin;
	GPIO_Init(OLED_DC_GPIO,&gpio);
	
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = OLED_SCL_Pin;
	GPIO_Init(OLED_SCL_GPIO,&gpio);
	gpio.GPIO_Pin = OLED_SDA_Pin;
	GPIO_Init(OLED_SDA_GPIO,&gpio);
	
	spi1.SPI_Mode = SPI_Mode_Master;
	spi1.SPI_DataSize = SPI_DataSize_8b;
	spi1.SPI_FirstBit = SPI_FirstBit_MSB;
	spi1.SPI_CPHA = SPI_CPHA_2Edge;
	spi1.SPI_CPOL = SPI_CPOL_High;
	spi1.SPI_NSS = SPI_NSS_Soft;
	spi1.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spi1.SPI_CRCPolynomial = 0;
	SPI_Init(OLED_SPIx,&spi1);
	SPI_Cmd(OLED_SPIx,ENABLE);	
	
	OLED_RES_Clr();
	rt_thread_delay(10);	
	OLED_RES_Set();
	
	oled_write_byte(0xAE,OLED_CMD); // �ر���ʾ
	oled_write_byte(0xD5,OLED_CMD); // ����ʱ�ӷ�Ƶ����,��Ƶ��
	oled_write_byte(0x80,OLED_CMD);   // [3:0],��Ƶ����;[7:4],��Ƶ��
	oled_write_byte(0xA8,OLED_CMD); // ��������·��
	oled_write_byte(0X3F,OLED_CMD); // Ĭ��0X3F(1/64) 
	oled_write_byte(0xD3,OLED_CMD); // ������ʾƫ��
	oled_write_byte(0X00,OLED_CMD); // Ĭ��Ϊ0
	oled_write_byte(0x40,OLED_CMD); // ������ʾ��ʼ�� [5:0],����.									    
	oled_write_byte(0x8D,OLED_CMD); // ��ɱ�����
	oled_write_byte(0x14,OLED_CMD); // bit2������/�ر�
	oled_write_byte(0x20,OLED_CMD); // �����ڴ��ַģʽ
	oled_write_byte(0x02,OLED_CMD); // [1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	oled_write_byte(0xA1,OLED_CMD); // ���ض�������,bit0:0,0->0;1,0->127;
	oled_write_byte(0xC0,OLED_CMD); // ����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	oled_write_byte(0xDA,OLED_CMD); // ����COMӲ����������
	oled_write_byte(0x12,OLED_CMD); // [5:4]����
	oled_write_byte(0x81,OLED_CMD); // �Աȶ�����
	oled_write_byte(0x7F,OLED_CMD); // 1~255;Ĭ��0X7F (��������,Խ��Խ��)
	oled_write_byte(0xD9,OLED_CMD); // ����Ԥ�������
	oled_write_byte(0xf1,OLED_CMD); // [3:0],PHASE 1;[7:4],PHASE 2;
	oled_write_byte(0xDB,OLED_CMD); // ����VCOMH ��ѹ����
	oled_write_byte(0x30,OLED_CMD); // [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	oled_write_byte(0xA4,OLED_CMD); // ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	oled_write_byte(0xA6,OLED_CMD); // ������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	oled_write_byte(0xAF,OLED_CMD); // ������ʾ
	OLED_Clear();
}

void oled_write_byte(uint8_t byte,OLED_WR_MODE mod)
{
	if(mod == OLED_DATA)
	{
		OLED_DC_Set();
	}
	else
	{
		OLED_DC_Clr();
	}

	while (SPI_I2S_GetFlagStatus(OLED_SPIx, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(OLED_SPIx, byte); 
	while (SPI_I2S_GetFlagStatus(OLED_SPIx, SPI_I2S_FLAG_RXNE) == RESET);
}

u8 OLED_GRAM[128][8];	 
/*------------------------------------------------------------------------------
�������ƣ�OLED_Refresh_Gram
����������OLED���º���
�����������
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		oled_write_byte(0xb0+i,OLED_CMD);    // ����ҳ��ַ��0~7��
		oled_write_byte(0x00,OLED_CMD);      // ������ʾλ�á��е͵�ַ
		oled_write_byte(0x10,OLED_CMD);      // ������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
			oled_write_byte(OLED_GRAM[n][i],OLED_DATA);
		}
	}   
}	   			 

/*------------------------------------------------------------------------------
�������ƣ�OLED_Clear
����������OLED�������� 
�����������
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_Clear(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)
	{
		for(n=0;n<128;n++)
		{
			OLED_GRAM[n][i]=0X00;
		}
	}		
	OLED_Refresh_Gram();					// ������ʾ
}

/*------------------------------------------------------------------------------
�������ƣ�OLED���㺯��
������������������ 
���������x:0~127��y:0~63��t:1 ��� 0,���;
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;// ������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
	{
		OLED_GRAM[x][pos]|=temp;
	}
	else 
		OLED_GRAM[x][pos]&=~temp;	    
}
/*------------------------------------------------------------------------------
�������ƣ�OLED_Fill
����������OLED��亯��
���������x1,y1,x2,y2�������ĶԽ����꣬ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63��dot:0,���;1,���	
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)
		{
			OLED_DrawPoint(x,y,dot);
		}
	}													    
	OLED_Refresh_Gram();																		// ������ʾ
}

/*------------------------------------------------------------------------------
�������ƣ�OLED_ShowChar
����������OLED�ַ���ʾ���ܺ�������ָ��λ����ʾһ���ַ�,���������ַ���
���������x:0~127��y:0~63��mode:0,������ʾ;1,������ʾ��size:ѡ������ 16/12 
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';																						// �õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
			if(size==12)
			{
				//temp=oled_asc2_1206[chr][t];  											// ����1206����
			}
			else 
			{
				temp=oled_asc2_1608[chr][t];		 										// ����1608���� 
			}			
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)OLED_DrawPoint(x,y,mode);
				else OLED_DrawPoint(x,y,!mode);
				temp<<=1;
				y++;
				if((y-y0) == size)
				{
					y=y0;
					x++;
					break;
				}
			}  	 
    }          
}


/*------------------------------------------------------------------------------
�������ƣ�OLED_ShowString
����������OLED�ַ�����ʾ����
���������x,y:������ꣻ*p:�ַ�����ʼ��ַ����16����
���ز�������
��    ע����
------------------------------------------------------------------------------*/
void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX)
				{
					x=0;
					y+=16;
				}
        if(y>MAX_CHAR_POSY)
				{
					y=x=0;
					OLED_Clear();
				}
        OLED_ShowChar(x,y,*p,16,1);	 
        x+=8;
        p++;
    }  
}	

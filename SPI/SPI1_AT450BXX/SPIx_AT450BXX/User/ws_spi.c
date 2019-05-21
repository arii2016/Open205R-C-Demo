/*********************************************************************************************************
*
* File                : sw_spi.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include "stm32f2xx.h"
#include "config.h"
#include "ws_spi.h"

void SPI_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStruct;	 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(Open205R_SPIx_SCK_GPIO_CLK | Open205R_SPIx_MISO_GPIO_CLK | Open205R_SPIx_MOSI_GPIO_CLK,ENABLE);
	#ifdef OpenSPI1
		RCC_APB2PeriphClockCmd(Open205R_SPIx_CLK,ENABLE);
	#else
		RCC_APB1PeriphClockCmd(Open205R_SPIx_CLK,ENABLE);
	#endif
	
	GPIO_PinAFConfig(Open205R_SPIx_SCK_GPIO_PORT, Open205R_SPIx_SCK_SOURCE,  Open205R_SPIx_SCK_AF);
	GPIO_PinAFConfig(Open205R_SPIx_MISO_GPIO_PORT, Open205R_SPIx_MISO_SOURCE, Open205R_SPIx_MISO_AF);
	GPIO_PinAFConfig(Open205R_SPIx_MOSI_GPIO_PORT, Open205R_SPIx_MOSI_SOURCE, Open205R_SPIx_MOSI_AF);
	
	GPIO_InitStructure.GPIO_Pin = Open205R_SPIx_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
	GPIO_Init(Open205R_SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Open205R_SPIx_MISO_PIN;
	GPIO_Init(Open205R_SPIx_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Open205R_SPIx_MOSI_PIN;
	GPIO_Init(Open205R_SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);

	SPI_I2S_DeInit(Open205R_SPIx);
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low ;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft ;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(Open205R_SPIx, &SPI_InitStruct);

	SPI_Cmd(Open205R_SPIx, ENABLE);

}

void SPIx_Send_byte(u16 data)
{
	while(SPI_I2S_GetFlagStatus(Open205R_SPIx, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open205R_SPIx,data);

	while(SPI_I2S_GetFlagStatus(Open205R_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(Open205R_SPIx);
}

u16 SPIx_Receive_byte(void)
{
	while(SPI_I2S_GetFlagStatus(Open205R_SPIx, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open205R_SPIx,0x00);
	
	while(SPI_I2S_GetFlagStatus(Open205R_SPIx, SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(Open205R_SPIx);
}




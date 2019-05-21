/*********************************************************************************************************
*
* File                : ws_spi.h
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

#ifndef __SPI_H
#define __SPI_H

void SPI_Configuration(void);
void SPIx_Send_byte(u16 data);
u16 SPIx_Receive_byte(void);

#endif /*__SPI_H*/

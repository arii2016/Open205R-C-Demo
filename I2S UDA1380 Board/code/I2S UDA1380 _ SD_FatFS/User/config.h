#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include "stm32f2xx.h"

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
	#define Open207V_USARTx                        	USART2
	#define Open207V_USARTx_CLK                    	RCC_APB1Periph_USART2
	
	#define Open207V_USARTx_TX_PIN                 	GPIO_Pin_2
	#define Open207V_USARTx_TX_GPIO_PORT           	GPIOA
	#define Open207V_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207V_USARTx_TX_SOURCE              	GPIO_PinSource2
	#define Open207V_USARTx_TX_AF                  	GPIO_AF_USART2
	
	
	#define Open207V_USARTx_RX_PIN                 	GPIO_Pin_3
	#define Open207V_USARTx_RX_GPIO_PORT           	GPIOA
	#define Open207V_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207V_USARTx_RX_SOURCE              	GPIO_PinSource3
	#define Open207V_USARTx_RX_AF                  	GPIO_AF_USART2
	
	#define Open207V_USARTx_CTS_PIN                 GPIO_Pin_3
	#define Open207V_USARTx_CTS_GPIO_PORT           GPIOD
	#define Open207V_USARTx_CTS_GPIO_CLK            RCC_AHB1Periph_GPIOD
	#define Open207V_USARTx_CTS_SOURCE              GPIO_PinSource3
	#define Open207V_USARTx_CTS_AF                  GPIO_AF_USART2
	
	#define Open207V_USARTx_RTS_PIN                 GPIO_Pin_4
	#define Open207V_USARTx_RTS_GPIO_PORT           GPIOD
	#define Open207V_USARTx_RTS_GPIO_CLK            RCC_AHB1Periph_GPIOD
	#define Open207V_USARTx_RTS_SOURCE              GPIO_PinSource4
	#define Open207V_USARTx_RTS_AF                  GPIO_AF_USART2
	
	#define Open207V_USARTx_IRQn                    USART2_IRQn



#endif	  /*_CONFIG_H*/


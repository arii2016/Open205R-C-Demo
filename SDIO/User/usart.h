#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f2xx.h"
//#include "config.h"
/**
 * @brief Definition for COM port1, connected to USART1
 */ 

#define Open_USART                        USART2
#define Open_USART_CLK                    RCC_APB1Periph_USART2
#define Open_USART_TX_PIN                 GPIO_Pin_2
#define Open_USART_TX_GPIO_PORT           GPIOA
#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART_TX_SOURCE              GPIO_PinSource2
#define Open_USART_TX_AF                  GPIO_AF_USART2
#define Open_USART_RX_PIN                 GPIO_Pin_3
#define Open_USART_RX_GPIO_PORT           GPIOA
#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define Open_USART_RX_SOURCE              GPIO_PinSource3
#define Open_USART_RX_AF                  GPIO_AF_USART2
#define Open_USART_IRQn                   USART2_IRQn



void USART_Configuration(void);
void USART_NVIC_Config(void);

#endif /*_USART_H*/

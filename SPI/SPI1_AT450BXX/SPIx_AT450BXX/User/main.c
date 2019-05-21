/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "config.h"
#include "usart.h"
#include "ws_AT45DBXX.h"
#include <string.h>
#include <stdio.h>

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */
	u8 num=0;
	u8 ID[4];
	u8 tmp;
 

	Open207_LEDInit();	
	USART_Configuration();
	USART_NVIC_Config();
	printf("\r\nWelcome to WaveShare STM32F2 series MCU Board Open207V\r\n");

	AT45DBXX_Init();
	printf("AT45DBXX had been Init!\r\n");
	AT45DBXX_Read_ID(ID);
	printf("AT45DBXX ID is");
	for(num=0;num<4;num++)
	{
		printf(" 0x%x ",ID[num]);
	}
	printf("\r\n");

	printf("\r\nFALSH AT45DBXX Write Test: \r\n");
	for(num=0;num<255;num++) /*Written to the flash*/
	{
		write_buffer((u16)num,num);
		printf("%3d ",num);
	}
	printf("\r\nFALSH AT45DBXX Read Test: \r\n");

	for(num=0;num<255;num++) /*Read the flash*/
	{
		tmp=read_buffer((u16)num);
		printf("%3d ",tmp);
	}
	printf("\r\nFALSH AT45DBXX Read Test Succeed!\r\n");
	while (1)
	{
		GPIO_SetBits(Open_LED_GPIO , Open_GPIO_Pin_LED1);
		GPIO_SetBits(Open_LED_GPIO , Open_GPIO_Pin_LED2);
		GPIO_SetBits(Open_LED_GPIO , Open_GPIO_Pin_LED3);
		GPIO_SetBits(Open_LED_GPIO , Open_GPIO_Pin_LED4);
		Delay(0x5fffff);
		GPIO_ResetBits(Open_LED_GPIO , Open_GPIO_Pin_LED1);
		GPIO_ResetBits(Open_LED_GPIO , Open_GPIO_Pin_LED2);
		GPIO_ResetBits(Open_LED_GPIO , Open_GPIO_Pin_LED3);
		GPIO_ResetBits(Open_LED_GPIO , Open_GPIO_Pin_LED4);
		Delay(0x5fffff);
	}
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {

  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
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
#include "usart.h"
#include "config.h"
#include "User_systick.h"
//#include "stm32_eval.h"

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

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

  /* GPIOG Periph clock enable */
	RCC_ClocksTypeDef SYS_Clocks;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOA, ENABLE);
  delay_10us(1);
  /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  USART_Configuration();  
	/* Enable HSE */   
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait till HSE is ready and if Time out is reached exit */
	while(RCC_WaitForHSEStartUp()!=SUCCESS);
 	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//RCC_SYSCLKSource_PLLCLK RCC_SYSCLKSource_HSE

	RCC_GetClocksFreq(&SYS_Clocks);

	USART_Configuration();
	
	SysTick_Config((uint32_t)90);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
	printf("\r\nWelcome to WaveShare STM32F2 series MCU Board Open207Z Test\r\n");
	printf("Show The MCU USEING CLK:\r\n");
	printf("SYSCLK:%dM\r\n",SYS_Clocks.SYSCLK_Frequency/1000000);
	printf("HCLK:%dM\r\n",SYS_Clocks.HCLK_Frequency/1000000);
	printf("PCLK1:%dM\r\n",SYS_Clocks.PCLK1_Frequency/1000000);
	printf("PCLK2:%dM\r\n",SYS_Clocks.PCLK2_Frequency/1000000);
  delay_10us(1);
  /* Configure MCO1 pin(PA8) in alternate function */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

// 	printf("\r\nWelcome to WaveShare STM32F2 series MCU Board Open207Z Test\r\n");
// 	printf("Show The MCU USEING CLK:\r\n");
// 	printf("SYSCLK:%dM\r\n",SYS_Clocks.SYSCLK_Frequency/1000000);
// 	printf("HCLK:%dM\r\n",SYS_Clocks.HCLK_Frequency/1000000);
// 	printf("PCLK1:%dM\r\n",SYS_Clocks.PCLK1_Frequency/1000000);
// 	printf("PCLK2:%dM\r\n",SYS_Clocks.PCLK2_Frequency/1000000);   
	
  /* HSE clock selected to output on MCO1 pin(PA8)*/
  RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);

  while (1)
  {
	GPIO_SetBits(GPIOB,GPIO_Pin_0); 
	GPIO_SetBits(GPIOB,GPIO_Pin_1); 
	GPIO_SetBits(GPIOB,GPIO_Pin_2); 
	GPIO_SetBits(GPIOB,GPIO_Pin_3); 
 	Delay(0x000fffff);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	Delay(0x000fffff);
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

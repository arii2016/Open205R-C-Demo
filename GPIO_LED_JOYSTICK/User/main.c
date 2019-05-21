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
#include "config.h"

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

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

	uint8_t Key;
	Open207_LEDInit();
	Open207_JOYSTICK_KEY_Init();

	Key=5;
	/* Infinite loop */
	while (1)
	{
 	//JOYSTICK  A(PA4) B(PA6)  C(PB15)  D(PC6)  PRESS(PC7)
	// user(PB1) 
	//wakeup(PA0)
		if(!(GPIOC->IDR & (1<<4)))
			Key=1;
		else if(!(GPIOC->IDR & (1<<5)))
			Key=2;
		else if(!(GPIOC->IDR & (1<<6)))
			Key=3;
		else if(!(GPIOC->IDR & (1<<7)))
			Key=4;
		else if(!(GPIOC->IDR & (1<<13)))
			Key=0;


		else if(!(GPIOA->IDR & (1<<1)))
			Key=5;
		else if(!(GPIOA->IDR & (1<<0)))
			Key=6;
	
		switch(Key)
		{
			case 0:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
				break;
			case 1:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			Delay(0x5fffff);
				break;
			case 2:
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			Delay(0x5fffff);
				break;
			case 3:
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			Delay(0x5fffff);
				break;
			case 4:
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
				break;
			case 5:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
				break;
			case 6:
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);

			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			Delay(0x5fffff);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
				break;
			}
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

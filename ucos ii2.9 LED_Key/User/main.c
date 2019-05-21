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
#include "ucos_ii.h"
#include <includes.h>
//�궨��
#define OS_MINI_STACK_SIZE 128

#define TASK_Start_PRIO 4
#define TASK_Key_PRIO   5
#define TASK_LED_PRIO   6

//�����ջ
static  OS_STK TaskStartStk[OS_MINI_STACK_SIZE];
static  OS_STK TaskLEDStk[OS_MINI_STACK_SIZE];
static  OS_STK TaskKeyStk[OS_MINI_STACK_SIZE];

OS_EVENT * msg_key; 
void Delay(__IO uint32_t nCount);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


static INT8U Taskkey(void* p_arg)
{   
	uint8_t Key;
		Key=0;
	for(;;)
	{OSTimeDly(10);
		if(!(GPIOC->IDR & (1<<4)))
			Key=1;
		else if(!(GPIOC->IDR & (1<<5)))
			Key=2;
		else if(!(GPIOC->IDR & (1<<6)))
			Key=3;
		else if(!(GPIOC->IDR & (1<<7)))
			Key=4;
		else if(!(GPIOC->IDR & (1<<13)))
			Key=5;
		else Key=0;
		 if(Key)OSMboxPost(msg_key,(void*)Key);
		
// 		OSTimeDly(10);
//		return Key;
// 			GPIO_SetBits(GPIOB , GPIO_Pin_0);
// 			OSTimeDly(100);
// 			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
// 			OSTimeDly(100);
	}
}
static void TaskLED(void * p_arg)
{ uint8_t k=1,err;
	for(;;)
	{ 
		
		switch(k)
		{
			case 0:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
				break;
			case 1:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			OSTimeDly(1000);
				break;
			case 2:
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			OSTimeDly(1000);
				break;
			case 3:
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			OSTimeDly(1000);
				break;
			case 4:
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
				break;
			case 5:
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
				break;
			case 6:
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);

			GPIO_SetBits(GPIOB , GPIO_Pin_0);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_0);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_1);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_1);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_2);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_2);
			
			GPIO_SetBits(GPIOB , GPIO_Pin_3);
			OSTimeDly(1000);
			GPIO_ResetBits(GPIOB , GPIO_Pin_3);
				break;
			}
	 k=(u32)OSMboxPend(msg_key,10,&err); 
  }
}
static INT8U TaskStart(void* p_arg)
{   
  INT8U  os_err;
  msg_key=OSMboxCreate((void*)0);
	os_err = OSTaskCreate((void (*)(void *)) Taskkey,				
                          (void          * ) 0,							
                          (OS_STK        * )&TaskKeyStk[OS_MINI_STACK_SIZE - 1],		
                          (INT8U           ) TASK_Key_PRIO  );
	os_err = OSTaskCreate((void (*) (void *)) TaskLED,
                        (void *) 0,
                        (OS_STK *) &TaskLEDStk[OS_MINI_STACK_SIZE - 1],
                        (INT8U) TASK_LED_PRIO);
	OSTaskSuspend(TASK_Start_PRIO);
	return (os_err);
}
INT32S main(void)
{
  INT8U  os_err;
	int  *y;
	*y=1;
	Open207_LEDInit();
	Open207_JOYSTICK_KEY_Init();
	
  OS_CPU_SysTickInit();
	
  OSInit(); //Initialize "uC/OS-II, The Real-Time Kernel". 
	
	os_err = OSTaskCreate((void (*) (void *)) TaskStart,
                        (void *) 0,
                        (OS_STK *) &TaskStartStk[OS_MINI_STACK_SIZE - 1],
                        (INT8U) TASK_Start_PRIO);
	
	OSTimeSet(0);
	OSStart();  //Start multitasking (i.e. give control to uC/OS-II).  
  return (os_err);
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

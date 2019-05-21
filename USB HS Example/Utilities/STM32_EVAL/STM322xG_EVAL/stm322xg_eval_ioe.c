/**
  ******************************************************************************
  * @file    stm322xg_eval_ioe.c
  * @author  MCD Application Team
  * @version V4.6.2
  * @date    22-July-2011
  * @brief   This file provides a set of functions needed to manage the STMPE811
  *          IO Expander devices mounted on STM322xG-EVAL evaluation board(MB786)
  *          RevA and RevB.
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

  /* File Info : ---------------------------------------------------------------
  
    Note:
    -----
    - This driver uses the DMA method for sending and receiving data on I2C bus
      which allow higher efficiency and reliability of the communication.  
  
    SUPPORTED FEATURES:
      - IO Read/write : Set/Reset and Read (Polling/Interrupt)
      - Joystick: config and Read (Polling/Interrupt)
      - Touch Screen Features: Single point mode (Polling/Interrupt)
      - TempSensor Feature: accuracy not determined (Polling).

    UNSUPPORTED FEATURES:
      - Row ADC Feature is not supported (not implemented on STM322xG_EVAL board)
  ----------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm322xg_eval_ioe.h"

/**
  * @brief  Initializes and Configures the two IO_Expanders Functionalities 
  *         (IOs, Touch Screen ..) and configures all STM324xG_EVAL necessary
  *         hardware (GPIOs, APB clocks ..).
  * @param  None
  * @retval IOE_OK if all initializations done correctly. Other value if error.
  */
uint8_t IOE_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	/*--------------------------------------------------------------------------------
	
	Key GPIO Config
	
	--------------------------------------------------------------------------------*/
	/* Periph clock enable */
	RCC_AHB1PeriphClockCmd(JOY_A_KEY_RCC_AHBPeriph | JOY_B_KEY_RCC_AHBPeriph |  
						   JOY_C_KEY_RCC_AHBPeriph | JOY_D_KEY_RCC_AHBPeriph| JOY_CTR_KEY_RCC_AHBPeriph, ENABLE);
	
	/* Configure Input pushpull mode */
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = JOY_A_KEY_Pin;
	GPIO_Init(JOY_A_KEY_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = JOY_B_KEY_Pin;
	GPIO_Init(JOY_B_KEY_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = JOY_C_KEY_Pin;
	GPIO_Init(JOY_C_KEY_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = JOY_D_KEY_Pin;
	GPIO_Init(JOY_D_KEY_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = JOY_CTR_KEY_Pin;
	GPIO_Init(JOY_CTR_KEY_Port, &GPIO_InitStructure);

  return IOE_OK; 
} 


/**
  * @brief  Returns the current Joystick status.
  * @param  None
  * @retval The code of the Joystick key pressed: 
  *   @arg  JOY_NONE
  *   @arg  JOY_SEL
  *   @arg  JOY_DOWN
  *   @arg  JOY_LEFT
  *   @arg  JOY_RIGHT
  *   @arg  JOY_UP
  */
JOYState_TypeDef
 IOE_JoyStickGetState(void)
{
	if(!GPIO_ReadInputDataBit(JOY_C_KEY_Port,JOY_C_KEY_Pin))
		return JOY_LEFT;
	else if(!GPIO_ReadInputDataBit(JOY_A_KEY_Port,JOY_A_KEY_Pin))
		return JOY_UP;
	else if(!GPIO_ReadInputDataBit(JOY_D_KEY_Port,JOY_D_KEY_Pin))
		return JOY_DOWN;
	else if(!GPIO_ReadInputDataBit(JOY_B_KEY_Port,JOY_B_KEY_Pin))
		return JOY_RIGHT;
	//else if(!GPIO_ReadInputDataBit(JOY_CTR_KEY_Port,JOY_CTR_KEY_Pin))
		//return JOY_SEL;
	return JOY_NONE;
}

__IO JOYState_TypeDef keydone = JOY_NONE;

JOYState_TypeDef Key_ReadIOPin(void)
{
	if(keydone == JOY_NONE)
	{ 
		if(!GPIO_ReadInputDataBit(JOY_A_KEY_Port,JOY_A_KEY_Pin))
		{
			keydone = JOY_LEFT;
			return JOY_NONE;
		}   
		else if(!GPIO_ReadInputDataBit(JOY_B_KEY_Port,JOY_B_KEY_Pin))
		{
			keydone = JOY_UP;
			return JOY_NONE;
		}
		else if(!GPIO_ReadInputDataBit(JOY_C_KEY_Port,JOY_C_KEY_Pin))
		{	
			keydone = JOY_DOWN;
			return JOY_NONE;
		}
		else if(!GPIO_ReadInputDataBit(JOY_D_KEY_Port,JOY_D_KEY_Pin))
		{
			keydone = JOY_RIGHT;
			return JOY_NONE;
		}
		else if(!GPIO_ReadInputDataBit(JOY_CTR_KEY_Port,JOY_CTR_KEY_Pin))
		{
			keydone = JOY_SEL;
			return JOY_NONE;
		}	  
	}
	else if(keydone != JOY_NONE)
	{
		if(GPIO_ReadInputDataBit(JOY_B_KEY_Port,JOY_B_KEY_Pin) && keydone == JOY_LEFT)
		{
			keydone = JOY_NONE;
			return JOY_LEFT;
		}
		else if(GPIO_ReadInputDataBit(JOY_A_KEY_Port,JOY_A_KEY_Pin) && keydone == JOY_UP)
		{
			keydone = JOY_NONE;
			return JOY_UP;
		}
		else if(GPIO_ReadInputDataBit(JOY_C_KEY_Port,JOY_C_KEY_Pin) && keydone == JOY_DOWN)
		{
			keydone = JOY_NONE;
			return JOY_DOWN;
		}
		else if(GPIO_ReadInputDataBit(JOY_D_KEY_Port,JOY_D_KEY_Pin) && keydone == JOY_RIGHT)
		{
			keydone = JOY_NONE;
			return JOY_RIGHT;
		}
		else if(GPIO_ReadInputDataBit(JOY_CTR_KEY_Port,JOY_CTR_KEY_Pin) && keydone == JOY_SEL)
		{
			keydone = JOY_NONE;
			return JOY_SEL;
		}
	}
	return JOY_NONE;
}
/**
  * @}
  */      
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

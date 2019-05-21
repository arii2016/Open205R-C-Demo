/**
  ******************************************************************************
  * @file    stm322xg_eval_ioe.h
  * @author  MCD Application Team
  * @version V4.6.2
  * @date    22-July-2011
  * @brief   This file contains all the functions prototypes for the
  *          stm322xg_eval_ioe.c driver.
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
    SUPPORTED FEATURES:
      - IO Read/write : Set/Reset and Read (Polling/Interrupt)
      - Joystick: config and Read (Polling/Interrupt)
      - Touch Screen Features: Single point mode (Polling/Interrupt)
      - TempSensor Feature: accuracy not determined (Polling).

    UNSUPPORTED FEATURES:
      - Row ADC Feature is not supported (not implemented on STM322xG_EVAL board)
  ----------------------------------------------------------------------------*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM322xG_EVAL_IOE_H
#define __STM322xG_EVAL_IOE_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM322xG_EVAL
  * @{
  */
    
/** @defgroup STM322xG_EVAL_IOE 
  * @{
  */    


/** @defgroup STM322xG_EVAL_IOE_Exported_Types
  * @{
  */ 

/** 
  * @brief  Touch Screen Information structure  
  */ 

/** 
  * @brief  Joystick State definitions  
  */ 
#ifndef __STM32_EVAL_H
typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef
;
#endif /* __STM32_EVAL_H */
 
/** 
  * @brief  IO_Expander Error codes  
  */ 
typedef enum
{
  IOE_OK = 0,
  IOE_FAILURE, 
  IOE_TIMEOUT,
  PARAM_ERROR,
  IOE1_NOT_OPERATIONAL, 
  IOE2_NOT_OPERATIONAL
}IOE_Status_TypDef;

/** 
  * @brief  Touch Screen Information structure  
  */
   
#define JOY_A_KEY_Port					GPIOC
#define JOY_A_KEY_Pin					GPIO_Pin_4
#define JOY_A_KEY_RCC_AHBPeriph			RCC_AHB1Periph_GPIOC

#define JOY_B_KEY_Port					GPIOC
#define JOY_B_KEY_Pin					GPIO_Pin_5
#define JOY_B_KEY_RCC_AHBPeriph			RCC_AHB1Periph_GPIOC

#define JOY_C_KEY_Port					GPIOC
#define JOY_C_KEY_Pin					GPIO_Pin_6
#define JOY_C_KEY_RCC_AHBPeriph			RCC_AHB1Periph_GPIOC

#define JOY_D_KEY_Port					GPIOC
#define JOY_D_KEY_Pin					GPIO_Pin_7
#define JOY_D_KEY_RCC_AHBPeriph			RCC_AHB1Periph_GPIOC

#define JOY_CTR_KEY_Port				GPIOC
#define JOY_CTR_KEY_Pin					GPIO_Pin_13
#define JOY_CTR_KEY_RCC_AHBPeriph		RCC_AHB1Periph_GPIOC
/** 
  * @brief  Configuration and initialization functions  
  */
uint8_t IOE_Config(void);
JOYState_TypeDef
 IOE_JoyStickGetState(void);
JOYState_TypeDef Key_ReadIOPin(void);

#endif
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */       
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

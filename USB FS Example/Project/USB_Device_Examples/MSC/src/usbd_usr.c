/**
  ******************************************************************************
  * @file    usbd_usr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-July-2011
  * @brief   This file includes the user application layer
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
#include "usbd_usr.h"
#include  "lcd_log.h"
#include <stdio.h>
/** @addtogroup USBD_USER
  * @{
  */

/** @addtogroup USBD_MSC_DEMO_USER_CALLBACKS
  * @{
  */
  
/** @defgroup USBD_USR 
  * @brief    This file includes the user application layer
  * @{
  */ 

/** @defgroup USBD_USR_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_USR_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_USR_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_USR_Private_Variables
  * @{
  */ 
/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBD_Usr_cb_TypeDef USR_cb =
{
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,
};

/**
  * @}
  */

/** @defgroup USBD_USR_Private_Constants
  * @{
  */ 

#define USER_INFORMATION1  "INFO : Single Lun configuration" 
#define USER_INFORMATION2  "INFO : microSD is used"
/**
  * @}
  */



/** @defgroup USBD_USR_Private_FunctionPrototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_USR_Private_Functions
  * @{
  */ 

/**
* @brief  Displays the message on LCD on device lib initialization
* @param  None
* @retval None
*/
void USBD_USR_Init(void)
{
  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);   
  
  /* Initialize the LCD */

#ifdef USE_STM3210C_EVAL
  STM3210C_LCD_Init();  
#else
  STM322xG_LCD_Init();
#endif
  LCD_LOG_Init();
  
#ifdef USE_USB_OTG_HS 
  LCD_LOG_SetHeader(" USB OTG HS MSC Device");
#else
  LCD_LOG_SetHeader(" USB OTG FS MSC Device");
#endif
  LCD_UsrLog("> USB device library started.\n"); 
  LCD_LOG_SetFooter ("     USB Device Library v1.0.0" );
  
  
  /* Information panel */
  LCD_SetTextColor(Green);
  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 42, USER_INFORMATION1);
  LCD_DisplayStringLine( LCD_PIXEL_HEIGHT - 30, USER_INFORMATION2);
  LCD_SetTextColor(LCD_LOG_DEFAULT_COLOR);  
 
}

/**
* @brief  Displays the message on LCD on device reset event
* @param  speed : device speed
* @retval None
*/
void USBD_USR_DeviceReset (uint8_t speed)
{
 switch (speed)
 {
   case USB_OTG_SPEED_HIGH: 
     LCD_LOG_SetFooter ("     USB Device Library v1.0.0  [HS]" );
     break;

  case USB_OTG_SPEED_FULL: 
     LCD_LOG_SetFooter ("     USB Device Library v1.0.0  [FS]" );
     break;
 default:
     LCD_LOG_SetFooter ("     USB Device Library v1.0.0  [??]" );
     
 }
}


/**
* @brief  Displays the message on LCD on device config event
* @param  None
* @retval Staus
*/
void USBD_USR_DeviceConfigured (void)
{
  LCD_UsrLog("> MSC Interface started.\n");

}
/**
* @brief  Displays the message on LCD on device suspend event 
* @param  None
* @retval None
*/
void USBD_USR_DeviceSuspended(void)
{
    LCD_UsrLog("> Device In suspend mode.\n");
}


/**
* @brief  Displays the message on LCD on device resume event
* @param  None
* @retval None
*/
void USBD_USR_DeviceResumed(void)
{

}

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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

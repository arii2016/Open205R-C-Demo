/*********************************************************************************************************
*
* File                : main.c
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "usart.h"
#include "sdcard.h"
#include <string.h>
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */




/*******************************************************************************
* Function Name  : Delay
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


unsigned char Start_Flag=0;

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BlockSize            512 /* Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)

#define NumberOfBlocks       2  /* For Multi Blocks operation (Read/Write) */
#define MultiBufferWordsSize ((BlockSize * NumberOfBlocks) >> 2)

#define Operate_Block 0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SD_CardInfo SDCardInfo;
u32 Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];
u32 Buffer_MultiBlock_Tx[MultiBufferWordsSize], Buffer_MultiBlock_Rx[MultiBufferWordsSize];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
SD_Error Status = SD_OK;
ErrorStatus HSEStartUpStatus;

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(ENABLE);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
//    RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
* Function Name  : NVIC_Config
* Description    : Configures SDIO IRQ channel.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  u32 i;
  RCC_Configuration();
  USART_Configuration();   
  NVIC_Configuration();
		
//  while(!Start_Flag);
	
  /*-------------------------- SD Init ----------------------------- */
  Status = SD_Init();
  printf("    \r\n\r\n01. ----- SD_Init Status:%d\r\n",Status);

  if (Status == SD_OK)
  {				                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 +                    
    printf("          Initialize SD card successfully!\r\n\r\n");
    /*----------------- Read CSD/CID MSD registers ------------------*/
    Status = SD_GetCardInfo(&SDCardInfo);
    printf("02. ----- SD_GetCardInfo Status:%d\r\n",Status);
  }
  
  if (Status == SD_OK)
  {
    printf("          Get SD card infomation successfully!\r\n          Block size:%x, Card type:%x\r\n\r\n",SDCardInfo.CardBlockSize,SDCardInfo.CardType);  
    /*----------------- Select Card --------------------------------*/
    Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
    printf("03. ----- SD_SelectDeselect Status:%d\r\n",Status);
  }
  
  if (Status == SD_OK)
  {
    printf("          Select SD card successfully!\r\n\r\n");
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
    printf("04. ----- SD_EnableWideBusOperation Status:%d\r\n",Status);
  }
  
  /*------------------- Block Erase -------------------------------*/
  if (Status == SD_OK)
  {
    printf("          Enable wide bus operation successfully!\r\n\r\n");
    /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
    Status = SD_Erase(Operate_Block*BlockSize, (Operate_Block+1)*BlockSize);
    printf("05. ----- SD_Erase Status:%d\r\n",Status);
  }
 
  /* Set Device Transfer Mode to DMA */
  if (Status == SD_OK)
  {  
    printf("          Erase block %d successfully!\r\n          All the data is 0x00\r\n\r\n",Operate_Block);
    Status = SD_SetDeviceMode(SD_DMA_MODE);
    printf("06. ----- SD_SetDeviceMode Status:%d\r\n",Status);
  }

  if (Status == SD_OK)
  {
    printf("          Set SD card mode successfully!\r\n\r\n");
    memset(Buffer_MultiBlock_Rx,0xfe,sizeof(Buffer_MultiBlock_Rx));

    Status = SD_ReadMultiBlocks(Operate_Block*BlockSize, Buffer_MultiBlock_Rx, BlockSize, NumberOfBlocks);

    printf("07. ----- SD_ReadMultiBlocks Status:%d\r\n",Status);
  }
  
  if (Status == SD_OK)
  {
	  printf("          Read 2 blocks from block %d sucessfully!\r\n          All the data is:\r\n",Operate_Block);  //karlno add:20100505 for debug
	  for(i=0;i<sizeof(Buffer_MultiBlock_Rx)>>2;i++)
	  {
		  printf("%02x:0x%08x ",i,Buffer_MultiBlock_Rx[i]);
	  }
	  printf("\r\n\r\n");
  }

  /*------------------- Block Read/Write --------------------------*/
  /* Fill the buffer to send */
  memset(Buffer_Block_Tx, 0x88,sizeof(Buffer_Block_Tx));


  if (Status == SD_OK)
  {
    /* Write block of 512 bytes on address 0 */
    Status = SD_WriteBlock(Operate_Block*BlockSize, Buffer_Block_Tx, BlockSize);
    printf("08. ----- SD_WriteBlock Status:%d\r\n",Status);
  }
  
  if (Status == SD_OK)
  {
    printf("          Write block %d successfully!\r\n          All the data is 0x88\r\n\r\n",Operate_Block);  //karlno add:20100505 for debug
    /* Read block of 512 bytes from address 0 */
    Status = SD_ReadBlock(Operate_Block*BlockSize, Buffer_Block_Rx, BlockSize);
    printf("09. ----- SD_ReadBlock Status:%d\r\n",Status);
  }

  if (Status == SD_OK)
  {
	  printf("          Read block %d successfully!\r\n          All the data is:\r\n",Operate_Block);  //karlno add:20100505 for debug
	  for(i=0;i<sizeof(Buffer_Block_Rx)>>2;i++)
	  {
		  printf("%02x:0x%08x ",i,Buffer_Block_Rx[i]);
	  }
	  printf("\r\n\r\n");
  }
  
  /*--------------- Multiple Block Read/Write ---------------------*/
  /* Fill the buffer to send */
  memset(Buffer_MultiBlock_Tx, 0x66, sizeof(Buffer_MultiBlock_Tx));

  if (Status == SD_OK)
  {
    /* Write multiple block of many bytes on address 0 */
    Status = SD_WriteMultiBlocks((Operate_Block+2)*BlockSize, Buffer_MultiBlock_Tx, BlockSize, NumberOfBlocks);
    printf("10. ----- SD_WriteMultiBlocks Status:%d\r\n",Status);
  }
  
  if (Status == SD_OK)
  {
    printf("          Write 2 blocks from block %d successfully!\r\n          All the data is 0x66\r\n\r\n",Operate_Block+2);  //karlno add:20100505 for debug
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks((Operate_Block+2)*BlockSize, Buffer_MultiBlock_Rx, BlockSize, NumberOfBlocks);
    printf("11. ----- SD_ReadMultiBlocks Status:%d\r\n",Status);
  }

  
  if (Status == SD_OK)
  {
    printf("          Read 2 blocks from block %d successfully\r\n          All the data is:\r\n",Operate_Block+2);  //karlno add:20100505 for debug
    for(i=0;i<sizeof(Buffer_MultiBlock_Rx)>>2;i++)
    {
      printf("%02x:0x%08x ",i,Buffer_MultiBlock_Rx[i]);
    }
    printf("\r\n\r\n");
  }
    while(1);
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


/************************ (C) COPYLEFT 2010 Leafgrass *************************

* File Name          : LTM022A69B.h
* Author             : Librae
* Last Modified Date : 08/10/2010
* Description        : This file provides the 
						LTM022A69B LCD related functions' declaration.

******************************************************************************/
#ifndef __LTM022A69B_H__
#define __LTM022A69B_H__
#include "stm32f2xx.h"
#include "../Common/fonts.h"
/*
typedef enum
{		                           
    DC_CMD  = 0,	//command
	DC_DATA = 1		//data
} DCType;

//if IO for LCD is to be changed, just modify the constants below
#define LCD_X_SIZE		240	//LCD width
#define LCD_Y_SIZE		320	//LCD height
*/


//color define
#define     CYAN		 0x07FF
#define     PURPLE		 0xF81F
#define     RED          0XF800	  //��ɫ
#define     GREEN        0X07E0	  //��ɫ
#define     BLUE         0X001F	  //��ɫ
#define     WHITE        0XFFFF	  //��ɫ
#define     BLACK        0X0000	  //��ɫ
#define     YELLOW       0XFFE0	  //��ɫ
#define     ORANGE       0XFC08	  //��ɫ
#define     GRAY  	     0X8430   //��ɫ
#define     LGRAY        0XC618	  //ǳ��ɫ
#define     DARKGRAY     0X8410	  //���ɫ
#define     PORPO        0X801F	  //��ɫ
#define     PINK         0XF81F	  //�ۺ�ɫ
#define     GRAYBLUE     0X5458   //����ɫ
#define     LGRAYBLUE    0XA651   //ǳ����ɫ
#define     DARKBLUE     0X01CF	  //�����ɫ
#define 	LIGHTBLUE    0X7D7C	  //ǳ��ɫ 

/* Port configuration for LPC1114
16-bit serial interface (No reading in serial interface mode)
    CPU:LPC1114         LCD module
    (SPI0   ====>   LCD's data SPI interface)
    PIO0_6(SCK0)    ---->   LCD_SCL PIN
    PIO0_9(MOSI0)   ---->   LCD_SCI PIN
    PIO0_2(SSEL0)   ---->   LCD_nCS PIN
    (other 5 pins)
    PIO1_11 ---->   LCD_nRST PIN
    PIO1_10 ---->   LCD_nRS PIN
    PIO1_9  ---->   LCD_nRD PIN
    PIO1_8  ---->   LCD_nWR PIN
    PIO2_6  ---->   LCD_BLPWM PIN(backlight controll)
    ensure initialization this port fininshed.
*/


/* PB5( RS )   PD6( CS )  PB6 ( RST )  PB4(TOUCH_CS)  */



#define LCD_RST_H()		GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LCD_RST_L()		GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#define LCD_RS_H()		GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define LCD_RS_L()		GPIO_ResetBits(GPIOB,GPIO_Pin_8)


#define LCD_CS_H()		GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define LCD_CS_L()		GPIO_ResetBits(GPIOB,GPIO_Pin_7)

// typedef struct 
// {
//   int16_t X;
//   int16_t Y;
// } Point,  * pPoint;   

#define LCD_PIXEL_HEIGHT       0x0140
#define LCD_PIXEL_WIDTH        0x00F0
#define LCD_DEFAULT_FONT         Font16x24
void SPI0_Init(void);
unsigned char SPI0_communication(unsigned char send_char);


//=============================================================================
//							LCD Basic Functions
//=============================================================================

void LCD_WRITE_REG(unsigned int index);
void LCD_WRITE_COMMAND(unsigned int index, unsigned int data);
void LCD_WRITE_DATA(unsigned int data);
void lcd_init(void);

//=============================================================================
//							LCD Application Functions
//=============================================================================
void LCD_Clear(uint16_t color_background);

void lcd_clear_area(unsigned int color_front, 
                    unsigned char x, 
                    unsigned int y, 
                    unsigned int width, 
                    unsigned height);
void lcd_clear_Rect(unsigned int color_front, 
                    unsigned int x0, 
                    unsigned int y0, 
                    unsigned int x1, 
                    unsigned int y1);
void LCD_SetCursor(unsigned char x, unsigned int y);

unsigned char LCD_GetPoint(unsigned char x, unsigned int y);


void LCD_DisplayChar(uint16_t Line, uint16_t Column, uint8_t Ascii);            //ok
void LCD_DisplayStringLine(uint16_t Line, uint8_t *ptr);                        //ok
void LCD_ClearLine(uint16_t Line);                                              //ok
sFONT *LCD_GetFont(void);
void LCD_SetFont(sFONT *fonts);                                                  //
void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t height, uint16_t width);      //ok
void LCD_DrawFullRect(uint16_t x, uint16_t y, uint16_t height, uint16_t width);  //ok
void LCD_WriteRAM_Prepare(void);

void lcd_display_GB2312(unsigned char gb, 
                        unsigned int color_front, 
                        unsigned int color_background, 
                        unsigned char postion_x, 
                        unsigned char postion_y);

void lcd_display_image(const unsigned char *img, 
                       unsigned char x, 
                       unsigned int y, 
                       unsigned int width, 
                       unsigned height);

void lcd_draw_dot(unsigned int x,
                  unsigned int y,
                  unsigned int color_front);

void lcd_draw_bigdot(unsigned int   color_front,
                     unsigned int    x,
                     unsigned int    y );


unsigned char lcd_draw_line(
                        unsigned int x0,
                        unsigned int y0,
                        unsigned int x1,
                        unsigned int y1,
												unsigned int color);

//��ʾ����
void lcd_display_number(unsigned int x,
                        unsigned int y,
                        unsigned long num,
                        unsigned char num_len);


void lcd_display_test(void);


#endif

#ifndef __WH1604__
#define __WH1604__

#include "stm32f4xx_hal.h"



#define SET_A      HAL_GPIO_WritePin( GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
#define SET_WR     HAL_GPIO_WritePin( GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define SET_E      HAL_GPIO_WritePin( GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

#define RESET_A    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
#define RESET_WR   HAL_GPIO_WritePin( GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
#define RESET_E    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);


#define delay_lcd  1

 
void WriteCommandLCD(unsigned char data);
void OutLCD(char *string_lcd1, char *string_lcd2,char *string_lcd3,char *string_lcd4);
void WriteDataLCD(unsigned char data);
void InitLCD();










#endif
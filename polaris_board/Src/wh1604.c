#include "wh1604.h"
#include "stm32f4xx_hal.h"



const char ASCII_WIN[64] = 
{
0x41, 0xa0, 0x42, 0xa1, 0xe0, 0x45, 0xa3, 0xa4,
0xa5, 0xa6, 0x4b, 0xa7, 0x4d, 0x48, 0x4f, 0xa8,
0x50, 0x43, 0x54, 0xa9, 0xaa, 0x58, 0xe1, 0xab,
//0xac, 0xe2, 0xad, 0xae, 0x62, 0xaf, 0xb1, 0xb2,
0xac, 0xe2, 0xad, 0xae, 0x62, 0xaf, 0xb0, 0xb1,
0x61, 0xb2, 0xb3, 0xb4, 0xe3, 0x65, 0xb6, 0xb7,
0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0x6f, 0xbe,
0x70, 0x63, 0xbf, 0x79, 0xe4, 0x78, 0xe5, 0xc0,
0xc1, 0xe6, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7 
};

void OUT_Port(char data){
  char i;
  uint16_t pin=0x01;
  
  for (i=0;i<=7;i++){
    if((data&0x01)==1) HAL_GPIO_WritePin( GPIOB, (uint16_t)pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin( GPIOB, (uint16_t)pin, GPIO_PIN_RESET);
    data = data>>1;
    pin = pin<<1;
  }  
}

void WriteCommandLCD(unsigned char data)  {
  
  
  RESET_WR
  RESET_A
  RESET_E
  OUT_Port(data);
  HAL_Delay(delay_lcd);
  SET_E
  HAL_Delay(delay_lcd);
  RESET_E  
  RESET_WR
  RESET_A
  RESET_E
  HAL_Delay(delay_lcd);
}

void WriteDataLCD(unsigned char data)  {
  
  RESET_WR
  SET_A
  RESET_E
  if(data>=192) data=ASCII_WIN[data-192];
  OUT_Port(data);
  HAL_Delay(delay_lcd);
  SET_E
  HAL_Delay(delay_lcd);
  RESET_E  
  RESET_WR
  RESET_A
  RESET_E
  HAL_Delay(delay_lcd);
}
void InitLCD(){
  WriteCommandLCD(0x01);//38
  WriteCommandLCD(0x06);//80
  WriteCommandLCD(0x0C);//0c
  WriteCommandLCD(0x38);//06
  
}
void OutLCD(char *string_lcd1, char *string_lcd2,char *string_lcd3,char *string_lcd4 ) {
  
  int i;
  
 
  WriteCommandLCD(0x80);//06
  for (i=0; i<=15; i++)  WriteDataLCD(string_lcd1[i]);    
  WriteCommandLCD(0x88);
  WriteCommandLCD(0xc0);//c0
  for (i=0; i<=15; i++)  WriteDataLCD(string_lcd2[i]);
  WriteCommandLCD(0x90);
  for (i=0; i<=15; i++)  WriteDataLCD(string_lcd3[i]);
  WriteCommandLCD(0xD0);
  for (i=0; i<=15; i++)  WriteDataLCD(string_lcd4[i]);
   
}


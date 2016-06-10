

#include "timer.h"
#include "mxconstants.h"
#include "stm32f4xx_hal.h"

static int time_ch1=0;
static int time_ch2=0;
static char flag_ch1=0;
static char flag_ch2=0;
static char led1=0;
static char bl_led1=0;
static char led2=0;
static char bl_led2=0;


void StartTimerCH1(){
  flag_ch1=1;
}
void StopTimerCH1(){
  flag_ch1=0;
}
void StartTimerCH2(){
  flag_ch2=1;
}
void StopTimerCH2(){
  flag_ch2=0;
}


void SetTimerCH1(int _time){
  time_ch1 = _time;
}
void SetTimerCH2(int _time){
  time_ch2 = _time;
}
void ResetTimerCH1(){
  time_ch1 = 0;
}
void ResetTimerCH2(){
  time_ch2 = 0;
}
int GetTimerCH1(){
  return time_ch1;
}
int GetTimerCH2(){
  return time_ch2;
}

void ON_LED1()  {
  led1 =1;
}
void OFF_LED1()  {
  HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
  led1 =0;
}
void SetBlinkLED1(){
  bl_led1=1;
}
void ResetBlinkLED1(){
  bl_led1=0;
}
void ON_LED2()  {
  led2 =1;
  
}
void OFF_LED2()  {
  HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
  led2 =0;
}
void SetBlinkLED2(){
  bl_led2=1;
}
void ResetBlinkLED2(){
  bl_led2=0;
}

void Timer(){
  static char counter=0;
  static char l1=0;
  static char l2=0;
  if ((led1)&&(bl_led1)){
    if(l1) HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    l1^=1;
  }
  if((led1)&&(!bl_led1)){
    HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
  }
  if(!led1)HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
  
  if ((led2)&&(bl_led2)){
    if(l2) HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
    else HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    l2^=1;
  }
  if((led2)&&(!bl_led2)){
    HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
  }
  if(!led2)HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
  
  
  
  counter++;
  if(counter<60) return;
  counter =0;
  if(flag_ch1){
    if (time_ch1>0)time_ch1--;
  }
  if(flag_ch2)  {
    if (time_ch2>0)time_ch2--;
  }

  
}
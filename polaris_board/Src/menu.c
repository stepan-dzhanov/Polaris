#include "wh1604.h"
#include "stm32f4xx_hal.h"
#include "encoder.h"
#include "channel_driver.h"
#include "timer.h"
#include "protocol.h"


#define CURRENT_MAX 1.0
#define CURRENT_MIN 0
#define CURRENT_STEP 0.01
#define TIME_MAX 40
#define TIME_MIN 5
#define TIME_STEP 5
#define ANODE_MIN 1
#define ANODE_MAX 2
#define ANODE_STEP 1

#define CUR1 0
#define CUR2 1
#define TIME1 2
#define TIME2 3
#define ANODE1 4
#define ANODE2 5
#define RETURN 6
#define HOST_CONTROL 7

char str1[32],str2[32],str3[32],str4[32];
static float current_ch1=0.01;
static float current_ch2=0.01;
static signed char time_ch1 = 5;
static signed char time_ch2 = 5;
static char anode_ch1 =1;
static char anode_ch2 =1;


extern TIM_HandleTypeDef htim8;



void AddPointer(char _stpointer, char _check){
  switch (_stpointer){
  case 0:
    if(_check) {
      str1[0]='-';
      str1[1]='>';
    }
    else {
      str1[0]='<';
      str1[1]='>';
    }
    break;
  case 1:
    if(_check) {
      str2[0]='-';
      str2[1]='>';
    }
    else {
      str2[0]='<';
      str2[1]='>';
    }
    break;
  case 2:
    if(_check) {
      str3[0]='-';
      str3[1]='>';
    }
    else {
      str3[0]='<';
      str3[1]='>';
    }
    break;
  case 3:
    if(_check) {
      str4[0]='-';
      str4[1]='>';
    }
    else {
      str4[0]='<';
      str4[1]='>';
    }
    break;
    
    
    
  }
  
}
void ChangeData(char _param, signed char _add){
  
  

    switch (_param){
    case CUR1:
      current_ch1 +=CURRENT_STEP*_add;
      if(current_ch1>CURRENT_MAX) current_ch1 = CURRENT_MAX;
      if(current_ch1<CURRENT_MIN) current_ch1 = CURRENT_MIN;
      break;
    case CUR2:
      current_ch2 +=CURRENT_STEP*_add;
      if(current_ch2>CURRENT_MAX) current_ch2 = CURRENT_MAX;
      if(current_ch2<CURRENT_MIN) current_ch2 = CURRENT_MIN;
      break;
    case TIME1:
      time_ch1 +=TIME_STEP*_add;
      if(time_ch1>TIME_MAX) time_ch1 = TIME_MAX;
      if(time_ch1<TIME_MIN) time_ch1 = TIME_MIN;
      break;
    case TIME2:
      time_ch2 +=TIME_STEP*_add;
      if(time_ch2>TIME_MAX) time_ch2 = TIME_MAX;
      if(time_ch2<TIME_MIN) time_ch2 = TIME_MIN;
      break; 
    case ANODE1:
      anode_ch1 +=ANODE_STEP*_add;
      if(anode_ch1>ANODE_MAX) anode_ch1 = ANODE_MAX;
      if(anode_ch1<ANODE_MIN) anode_ch1 = ANODE_MIN;
      break;  
    case ANODE2:
      anode_ch2 +=ANODE_STEP*_add;
      if(anode_ch2>ANODE_MAX) anode_ch2 = ANODE_MAX;
      if(anode_ch2<ANODE_MIN) anode_ch2 = ANODE_MIN;
      break;  
    }
   
}



void CH1Menu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=0;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {CUR1,TIME1,ANODE1,RETURN};
   

   ResetEncoderPosition();
   
   SetEncoderStep(4);
   while(41)    {
     
     current_position = GetEncoderPosition();
     shift = current_position-last_position;
     last_position = current_position;
     
     if(type_pointer){
       en_pos += shift;
       if (en_pos<0)  en_pos=0;   
       if (en_pos>3)  en_pos=3;
       }
     
     else ChangeData(pointer[en_pos], shift);
     
     if (GetEncoderButton()) {
       if(pointer[en_pos]==RETURN) {
         if (anode_ch1==2)SET_AN_RES1
         else RESET_AN_RES1
         ResetEncoderPosition();
         return;
       }
       type_pointer ^=1; 
       HAL_Delay(100);
     }
     
     sprintf(str1,"  1 Ток,мА  %.2f",current_ch1);
     sprintf(str2,"  1 Врем,мин  %.2d",time_ch1);
     sprintf(str3,"  1 Аноды,шт   %.1d",anode_ch1);
     sprintf(str4,"    Выйти       ");
     
     AddPointer(en_pos, type_pointer);
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(100);
   }
   
}
void CH2Menu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=0;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {CUR2,TIME2,ANODE2,RETURN};
   

   ResetEncoderPosition();
   
   SetEncoderStep(4);
   while(41)    {
     
     current_position = GetEncoderPosition();
     shift = current_position-last_position;
     last_position = current_position;
     
     if(type_pointer){
       en_pos += shift;
       if (en_pos<0)  en_pos=0;   
       if (en_pos>3)  en_pos=3;
       }
     
     else ChangeData(pointer[en_pos], shift);
     
     if (GetEncoderButton()) {
       if(pointer[en_pos]==RETURN) {
         if (anode_ch2==2)SET_AN_RES2
         else RESET_AN_RES2
         ResetEncoderPosition();
         return;
       }
       type_pointer ^=1; 
       HAL_Delay(100);
     }
     
     sprintf(str1,"  2 Ток,мА  %.2f",current_ch2);
     sprintf(str2,"  2 Врем,мин  %.2d",time_ch2);
     sprintf(str3,"  2 Аноды,шт   %.1d",anode_ch2);
     sprintf(str4,"    Выйти       ");
     
     AddPointer(en_pos, type_pointer);
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(100);
   }
   
}


void DischargeMenu() {
   
  
  
   while(41)    {
     
    
     
     
     
    
     
    
     sprintf(str1,"  Батарея       ");
     sprintf(str2,"  разряжена     ");
     sprintf(str3,"  полностью!!   ");
     sprintf(str4,"                ");
     
    
   
     
     
    
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(10);
   }
   
}




void ProcedureMenu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=1;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {0,CUR1,CUR2,RETURN};
   int tm;   

   ResetEncoderPosition();
   
   SetEncoderStep(4);
   SetTimerCH1(time_ch1);
   SetTimerCH2(time_ch2);
   
   while(41)    {
     
     current_position = GetEncoderPosition();
     shift = current_position-last_position;
     last_position = current_position;
     
     if(type_pointer){
       en_pos += shift;
       if (en_pos<1)  en_pos=1;   
       if (en_pos>3)  en_pos=3;
       }
     
     else ChangeData(pointer[en_pos], shift);
     
     if (GetEncoderButton()) {
       if(pointer[en_pos]==RETURN) {
         ResetEncoderPosition();
         RunCH1(1, 1, anode_ch1);
         ResetStatusCH1();
         RunCH2(1, 1, anode_ch2);
         ResetStatusCH2();
        // OFF_CH1();
        // OFF_CH2();
         
         return;
       }
       type_pointer ^=1; 
       HAL_Delay(100);
     }
     
    
     sprintf(str1," Кан. Параметры ");
     sprintf(str2,"  1Ток%.2f Мин%.2d",current_ch1,(GetTimerCH1()));
     sprintf(str3,"  2Ток%.2f Мин%.2d",current_ch2,(GetTimerCH2()));
     sprintf(str4,"  Завершить     ");
     
     AddPointer(en_pos, type_pointer);
     
     if ( (GetStatusCH1())&&(GetTimerCH1()>0)  ){
       if(RunCH1((int)(current_ch1*1000), 0, anode_ch1)==NO_CONTACT_CH)     {
         StopTimerCH1();
       }
       else {
         StartTimerCH1();
       }
     }
     if ( (GetStatusCH1())&&(GetTimerCH1()==0)  ){
       RunCH1(0, 1, anode_ch1);
      
     }
     if ( (!GetStatusCH1())&&(GetTimerCH1()>0)  ){
       StopTimerCH1();
       RunCH1(0, 1, anode_ch1);
     }
     
     
     
     if ( (GetStatusCH2())&&(GetTimerCH2()>0)  ){
       if(RunCH2((int)(current_ch2*1000), 0, anode_ch2)==NO_CONTACT_CH)     {
         StopTimerCH2();
       }
       else {
         StartTimerCH2();
       }
     }
     if ( (GetStatusCH2())&&(GetTimerCH2()==0)  ){
       RunCH2(0, 1, anode_ch2);
     }
     if ( (!GetStatusCH2())&&(GetTimerCH2()>0)  ){
       StopTimerCH2();
       RunCH2(0, 1, anode_ch2);
     }
     
     
    
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(10);
     if(GetBatteryVoltage()<9.3) {
       RunCH2(0, 0, anode_ch2);
       RunCH1(0, 0, anode_ch1);
       OFF_LED2();
       OFF_LED1();
     //  OFF_CH1();
     //  OFF_CH2();
       DischargeMenu();
       
     }
   }   
}


void PCMenu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=0;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {0,RETURN,RETURN};
   int tm; 
   
   StartExchange();
   ResetEncoderPosition();
   
   SetEncoderStep(4);
  
   while(41)    {
     
     current_position = GetEncoderPosition();
     shift = current_position-last_position;
     last_position = current_position;
     
     if(type_pointer){
       en_pos += shift;
       if (en_pos<0)  en_pos=0;   
       if (en_pos>1)  en_pos=1;
       }
     
     else ChangeData(pointer[en_pos], shift);
     
     if (GetEncoderButton()) {
       if(pointer[en_pos]==RETURN) {
         ResetEncoderPosition();
         StopTimerCH1();
         RunCH1(0, 1, 0);
         StopExchange();
         return;
       }
      
       HAL_Delay(100);
     }
     
    
     sprintf(str1,"  Управление ПК ");
     sprintf(str2,"  Выход         ");
     sprintf(str3,"                ");
     sprintf(str4,"                ");
     
     AddPointer(en_pos, type_pointer);
     
   
     
     
    
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(10);
     EventProcessing();
      if(GetBatteryVoltage()<9.3) DischargeMenu();
   }
   
}


void ServiceMenu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=1;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {0,HOST_CONTROL,RETURN};
   int tm;   

   ResetEncoderPosition();
   
   SetEncoderStep(4);
  
   while(41)    {
     
     current_position = GetEncoderPosition();
     shift = current_position-last_position;
     last_position = current_position;
     
     if(type_pointer){
       en_pos += shift;
       if (en_pos<1)  en_pos=1;   
       if (en_pos>2)  en_pos=2;
       }
     
     else ChangeData(pointer[en_pos], shift);
     
     if (GetEncoderButton()) {
       if(pointer[en_pos]==RETURN) {
         ResetEncoderPosition();
         return;
       }
       if(pointer[en_pos]==HOST_CONTROL) {
         ResetEncoderPosition();
         PCMenu();
       }
     
       HAL_Delay(100);
     }
     
    
     sprintf(str1,"  Батарея %.2f  ", GetBatteryVoltage()+0);
     sprintf(str2,"  Управление ПК ");
     sprintf(str3,"  Выход         ");
     sprintf(str4,"                ");
     
     AddPointer(en_pos, type_pointer);
     
   
     
     
    
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(10);
      if(GetBatteryVoltage()<9.3) DischargeMenu();
   }
   
}






void MainMenu() {
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=0;
   static int current_position=0;
   static int last_position=0;

   
   ON_CH1();
   HAL_Delay(500);
   ON_CH2();
   SetEncoderStep(4);
   current_position = GetEncoderPosition();
   shift = current_position-last_position;
   last_position = current_position;
   
   if(type_pointer){
     en_pos += shift;
     if (en_pos<0)  en_pos=0;   
     if (en_pos>3)  en_pos=3;
     }
   
   else ChangeData(en_pos, shift);
   
   if (GetEncoderButton()) {
     switch(en_pos){
     case 0:
       ResetEncoderPosition();
       CH1Menu();
       SetEncoderPosition(current_position);
       break;
     case 1:
       ResetEncoderPosition();
       CH2Menu();
       SetEncoderPosition(current_position);
       break;
     case 2:
       ResetEncoderPosition();
       ProcedureMenu();
       SetEncoderPosition(current_position);
       break;
       case 3:
       ResetEncoderPosition();
       ServiceMenu();
       SetEncoderPosition(current_position);
       break;
      
     }
    // type_pointer ^=1; 
     HAL_Delay(100);
   }
  
   sprintf(str1,"  Установки К1  ");
   sprintf(str2,"  Установки К2  ");
   sprintf(str3,"  Процедура     ");
   sprintf(str4,"  Сервис        ");
   AddPointer(en_pos, type_pointer);
   OutLCD(str1,str2,str3,str4);
   HAL_Delay(100);
   if(GetBatteryVoltage()<9.3) DischargeMenu();
   
}



void ChargeMenu() {
   volatile int pwm = 3350;
   volatile signed int tmp;
   volatile float current, voltage,c;
   
   static char type_pointer=1;
   signed char shift =0;
   static signed int en_pos=1;
   static int current_position=0;
   static int last_position=0;
   char pointer[] = {0,HOST_CONTROL,RETURN};
   int tm;   

   TIM8->CCR4 = pwm;
   HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
   //while(1);
  
   while(41)    {
     
     
     
     current = GetBatteryCurrent();
     voltage = GetBatteryVoltage();
     
     sprintf(str1,"  I     %.2f  A ", current);
     sprintf(str2,"  U      %.2f V", voltage);
     sprintf(str3,"  Идет заряд      ");
     sprintf(str4,"  батареи         ");
     
     if (voltage <12.63)       {
       if ((current+1.0)>0) pwm +=1;
       if ((current+1.0)<0) pwm -=1;
     }
     else {
       if (voltage>=12.66) pwm -=1;
       if ((voltage>=12.63)&&(voltage<12.65)) pwm +=1;
       if ((current>-0.15)||(voltage>=13.2)){
        
         HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_4);
         while (voltage>12.3){
           current = GetBatteryCurrent();
           voltage = GetBatteryVoltage()+0;
     
           sprintf(str1,"    %.2f V        ", voltage);
           sprintf(str2,"   Отключите      ", voltage);
           sprintf(str3,"   Устройство     ",70);
           sprintf(str4," Заряд окончен   ");
           OutLCD(str1,str2,str3,str4);
           HAL_Delay(1000);          
         }
         HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
         
         
       }
     }
     
 
     
     
     TIM8->CCR4 = pwm;
     
     
     
   
     
     
    
     OutLCD(str1,str2,str3,str4);
     HAL_Delay(100);
   }
   
}




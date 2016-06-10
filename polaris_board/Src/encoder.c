

#include "encoder.h"
#include <math.h>

static char button = 0;
static signed int position = 0;
static signed int pos = 0;
int cur_phaze=0;
int prev_phaze=0;
char step = 2;
char ch1_status=0;
char ch2_status=0;

char GetStatusCH1(){
  return ch1_status;
}
char GetStatusCH2(){
  return ch2_status;
}
void ResetStatusCH2(){
  ch2_status=0;
}

void ResetStatusCH1(){
  ch1_status=0;
}

void SetEncoderStep(char _step){
  step=_step;
}


void ResetEncoderPosition(){
  pos=0;
  position=0;
}
void SetEncoderPosition(int _position){
  position = _position;
  pos = 0;
}


signed int GetEncoderPosition(){
  signed int pos;
  pos = position;
//  position = 0;
  return pos;
}

char GetEncoderButton(){
  char but;
  but = button;
  button = 0;
  return but;
}


void UpdateGlobalPos__soft_qei() {
        char a,b;
        a = HAL_GPIO_ReadPin(ButtonM_GPIO_Port, ButtonM_Pin);
        b = HAL_GPIO_ReadPin(ButtonP_GPIO_Port, ButtonP_Pin);
        b = b<<1;
        a |=b;
   	cur_phaze = a&0x03;
	switch(prev_phaze){
		case 0:	switch(cur_phaze){
					case 0://error?
							break;
					case 1: position++;
							break;
					case 2: position--;
							break;
					case 3://error?
							break;
				}
				break;
		case 1: switch(cur_phaze){
					case 0: position--;
							break;
					case 1://error?
							break;
					case 2://error?
							break;
					case 3:	position++;
							break;
				}
				break;
		case 2: switch(cur_phaze){
					case 0: position++;
							break;
					case 1: //error?
							break;
					case 2: //error?
							break;
					case 3:	position--;
							break;
				}
				break;
		case 3: switch(cur_phaze){
					case 0: //error?
							break;
					case 1: position--;
							break;
					case 2: position++;
							break;
					case 3:	//error?
							break;
				}
				break;
	}
	prev_phaze = cur_phaze;


}


__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  switch (GPIO_Pin){
  case ButtonOK_Pin:

    button=1;
 
    break;
  case ButtonP_Pin:
 
     if(HAL_GPIO_ReadPin(ButtonM_GPIO_Port, ButtonM_Pin)==1) {
      pos++;
     if (abs(pos)>=step){
        position++;
        pos=0;
      }
    }
    //UpdateGlobalPos__soft_qei();
    break;
  case ButtonM_Pin:
 
   if(HAL_GPIO_ReadPin(ButtonP_GPIO_Port, ButtonP_Pin)==1) {
      pos--;
      if (abs(pos)>=step){
        position--;
        pos=0;
      }
    }
   break;
  case CH1_Pin:
    ch1_status ^=1;
    break;
  case CH2_Pin:
    ch2_status ^=1;
    break;
   
   // UpdateGlobalPos__soft_qei();
    break; 
  default:
    break;
    
  }
  
  
  
}
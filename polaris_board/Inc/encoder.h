#ifndef __ENCODER__
#define __ENCODER__

#include "stm32f4xx_hal.h"
#include "mxconstants.h"




signed int GetEncoderPosition();
char GetEncoderButton();
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void ResetEncoderPosition();
void SetEncoderPosition(int _position);
void SetEncoderStep(char _step);
char GetStatusCH1();
char GetStatusCH2();
void ResetStatusCH2();
void ResetStatusCH1();
#endif
#ifndef __CHANNEL__
#define __CHANNEL__

//#include "mxconstants.h"
#include "stm32f4xx_hal.h"

typedef enum {OK_CH,NO_CONTACT_CH,STOP_CH,ERROR_CH,PAUSE_CH}channel_status_t;




int GetADC1();
void SetDAC1(int data);
channel_status_t RunCH1(float _current, char stop, char anode);
channel_status_t RunCH2(float _current, char stop, char anode);
void MX_ADC1_Init(void);
void ON_CH1();
void ON_CH2();
void OFF_CH1();
void OFF_CH2();
float GetExternalVoltage();
float GetBatteryVoltage();
float GetBatteryCurrent();

#define SET_ONPOW1      HAL_GPIO_WritePin( ON_POW1_GPIO_Port, ON_POW1_Pin, GPIO_PIN_SET);
#define RESET_ONPOW1    HAL_GPIO_WritePin( ON_POW1_GPIO_Port, ON_POW1_Pin, GPIO_PIN_RESET);

#define SET_CSDAC1      HAL_GPIO_WritePin( CS_DAC1_GPIO_Port, CS_DAC1_Pin, GPIO_PIN_SET);
#define RESET_CSDAC1    HAL_GPIO_WritePin( CS_DAC1_GPIO_Port, CS_DAC1_Pin, GPIO_PIN_RESET);

#define SET_ONPOW2      HAL_GPIO_WritePin( ON_POW2_GPIO_Port, ON_POW2_Pin, GPIO_PIN_SET);
#define RESET_ONPOW2    HAL_GPIO_WritePin( ON_POW2_GPIO_Port, ON_POW2_Pin, GPIO_PIN_RESET);

#define SET_CSDAC2      HAL_GPIO_WritePin( CS_DAC2_GPIO_Port, CS_DAC2_Pin, GPIO_PIN_SET);
#define RESET_CSDAC2    HAL_GPIO_WritePin( CS_DAC2_GPIO_Port, CS_DAC2_Pin, GPIO_PIN_RESET);


#define SET_CSADC2      HAL_GPIO_WritePin( CS_ADC2_GPIO_Port, CS_ADC2_Pin, GPIO_PIN_SET);
#define RESET_CSADC2    HAL_GPIO_WritePin( CS_ADC2_GPIO_Port, CS_ADC2_Pin, GPIO_PIN_RESET);

#define SET_CSADC1      HAL_GPIO_WritePin( CS_ADC1_GPIO_Port, CS_ADC1_Pin, GPIO_PIN_SET);
#define RESET_CSADC1    HAL_GPIO_WritePin( CS_ADC1_GPIO_Port, CS_ADC1_Pin, GPIO_PIN_RESET);

#define SET_AN_RES1     HAL_GPIO_WritePin( AN_RES1_GPIO_Port, AN_RES1_Pin, GPIO_PIN_SET);
#define RESET_AN_RES1   HAL_GPIO_WritePin( AN_RES1_GPIO_Port, AN_RES1_Pin, GPIO_PIN_RESET);

#define SET_AN_RES2     HAL_GPIO_WritePin( AN_RES2_GPIO_Port, AN_RES2_Pin, GPIO_PIN_SET);
#define RESET_AN_RES2   HAL_GPIO_WritePin( AN_RES2_GPIO_Port, AN_RES2_Pin, GPIO_PIN_RESET);




#define ENTER_NUM 1   // 1 = 100 msec
#define U_MAX 500
#define CURRENT_INC 100

#define RESISTANCE1 20
#define RESISTANCE2 20


#endif
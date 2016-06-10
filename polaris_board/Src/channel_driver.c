
#include "stm32f4xx_hal.h"
#include "channel_driver.h"


ADC_HandleTypeDef hadc1;

extern SPI_HandleTypeDef hspi1;

//DAC_HandleTypeDef hdac;



void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION12b;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = EOC_SINGLE_CONV;
  HAL_ADC_Init(&hadc1);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

float GetExternalVoltage(){
  
  volatile int adcResult;
  float result;
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
  
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  adcResult = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  result = (0.00080586*(float)adcResult*6.0569)+0.61;
  return result;
  
  
}

float GetBatteryVoltage(){
  
  volatile int adcResult;
  float result;
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
  
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  adcResult = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  result = (0.00080586*(float)adcResult*6.18745);
  return result;
  
  
}

float GetBatteryCurrent(){
  
  volatile int adcResult;
  float result;
  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
  
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  adcResult = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  result = ((0.00080586*(float)adcResult)-1.22)/1.195;
  return result;
  
  
}





/* DAC init function */
//void MX_DAC_Init(void)
//{

 // DAC_ChannelConfTypeDef sConfig;

    /**DAC Initialization 
    */
//  hdac.Instance = DAC;
//  HAL_DAC_Init(&hdac);

    /**DAC channel OUT1 config 
    */
 // sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
 // sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
 // HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1);

//}


void ON_CH1(){
  
 
  SET_ONPOW1
  SET_CSDAC1
  SET_CSADC1
  //HAL_Delay(5000);
  //SET_AN_RES1
    
  
}
void ON_CH2(){
  
 
  SET_ONPOW2
  SET_CSDAC2
  SET_CSADC2
  //HAL_Delay(5000);
  //SET_AN_RES2
 
    
  
}
void OFF_CH2(){
  RESET_ONPOW2
}
void OFF_CH1(){
  RESET_ONPOW1
}




int GetADC1()   {
  uint8_t txData[2];
  uint8_t rxData[4];
  int result;
  txData [0] = 0x11;
  txData [1] = 0;
  RESET_CSADC1
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSADC1
  result = rxData[0];
  result = result<<8;
  result |= rxData[1];
  result = result&0x0FFF;
  return result;
}

int GetADC2()   {
  uint8_t txData[2];
  uint8_t rxData[4];
  int result;
  txData [0] = 0x11;
  txData [1] = 0;
  RESET_CSADC2
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSADC2
  result = rxData[0];
  result = result<<8;
  result |= rxData[1];
  result = result&0x0FFF;
  return result;
}



int GetADC11()   {
  uint8_t txData[2];
  uint8_t rxData[4];
  int result;
  txData [0] = 0x19;
  txData [1] = 0;
  RESET_CSADC1
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSADC1
  result = rxData[0];
  result = result<<8;
  result |= rxData[1];
  result = result&0x0FFF;
  return result;
}
int GetADC21()   {
  uint8_t txData[2];
  uint8_t rxData[4];
  int result;
  txData [0] = 0x19;
  txData [1] = 0;
  RESET_CSADC2
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSADC2
  result = rxData[0];
  result = result<<8;
  result |= rxData[1];
  result = result&0x0FFF;
  return result;
}


int GetADC_1()   {
  int adcResult;
  
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 100);
  adcResult = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  return adcResult;
  
}

void SetDAC1(int data){
  uint8_t txData[2];
  uint8_t rxData[4];
  txData [0] = (data>>8);
  txData [1] = (data);
  
  RESET_CSDAC1
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSDAC1
  
  /*HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, data);*/
  
}

void SetDAC2(int data){
  uint8_t txData[2];
  uint8_t rxData[4];
  txData [0] = (data>>8);
  txData [1] = (data);
  
  RESET_CSDAC2
  HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, 100);
  SET_CSDAC2
  
  /*HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, data);*/
  
}





channel_status_t RunCH1(float _current, char stop, char anode)       {
  static char state = OK_CH;
  static int enter_counter=0;
  int current;
  static int last_current=0; 
  int voltage, voltage1;
  
  enter_counter++;
  if(enter_counter<ENTER_NUM) return PAUSE_CH;
  
 // if (anode==1)RESET_AN_RES1
 // else SET_AN_RES1
  
  enter_counter = 0;
  current = (int)(_current*12.6764);  //12.4334
  
  if ((stop)&&(last_current==0)) {
    SetDAC1(0);
    last_current = 0;
    OFF_LED1();  
    return STOP_CH;
  }
  if ((stop)&&(_current==1)) {
    SetDAC1(0);
    last_current = 0;
    OFF_LED1();  
    return STOP_CH;
  }
  
  
  
  
  if(last_current<current) {
    last_current +=CURRENT_INC;
    if(last_current>current){
      last_current=current;
    }
    SetDAC1(last_current);
  }
  if(last_current>current) {
    last_current -= CURRENT_INC;
    if(last_current<current){
      last_current=current;
    }
    SetDAC1(last_current);
  }
  voltage = GetADC1()+1;
  voltage1 = GetADC11()+1;
  //if (voltage>2800){
    //return NO_CONTACT_CH;
  //}
  
 
  ON_LED1();
  
  if(anode==2)  {
    if ( ((last_current/voltage1)<RESISTANCE1)||((last_current/voltage)<RESISTANCE1) ) {
      SetBlinkLED1();
      state  = NO_CONTACT_CH;
      last_current = 0;
      
    }
     if ( ((last_current/voltage1)>=RESISTANCE1)||((last_current/voltage)>=RESISTANCE1) ) {
      ResetBlinkLED1();
      state = OK_CH;
    }
    
   
     
    
  }
  if ((anode == 1)){
    if ((last_current/voltage1)<RESISTANCE1) {
      SetBlinkLED1();
      last_current = 0;
      state  = NO_CONTACT_CH;
     
    }
    if ((last_current/voltage1)>=RESISTANCE1) {
      ResetBlinkLED1();
      state = OK_CH;
    }
  }
  return state;
  
}




channel_status_t RunCH2(float _current, char stop, char anode)       {
  static char state = OK_CH;
  static int enter_counter=0;
  int current;
  static int last_current=0; 
  int voltage, voltage1;
  
  enter_counter++;
  if(enter_counter<ENTER_NUM) return PAUSE_CH;
  
 // if (anode==1)SET_AN_RES2
 // else RESET_AN_RES2
  
  enter_counter = 0;
  current = (int)(_current*12.6764);  //12.4334
  
  if ((stop)&&(last_current==0)) {
    SetDAC2(0);
    last_current = 0;
    OFF_LED2();  
    return STOP_CH;
  }
  if ((stop)&&(_current==1)) {
    SetDAC2(0);
    last_current = 0;
    OFF_LED2();  
    return STOP_CH;
  }
  
  
  
  
  if(last_current<current) {
    last_current +=CURRENT_INC;
    if(last_current>current){
      last_current=current;
    }
    SetDAC2(last_current);
  }
  if(last_current>current) {
    last_current -= CURRENT_INC;
    if(last_current<current){
      last_current=current;
    }
    SetDAC2(last_current);
  }
  voltage = GetADC2()+1;
  voltage1 = GetADC21()+1;
  //if (voltage>2800){
    //return NO_CONTACT_CH;
  //}
  
 
  ON_LED2();
  
  if(anode==2)  {
    if ( ((last_current/voltage1)<RESISTANCE2)||((last_current/voltage)<RESISTANCE2) ) {
      SetBlinkLED2();
      state  = NO_CONTACT_CH;
      last_current = 0;
      
    }
     if ( ((last_current/voltage1)>=RESISTANCE2)||((last_current/voltage)>=RESISTANCE2) ) {
      ResetBlinkLED2();
      state = OK_CH;
    }
    
   
     
    
  }
  if ((anode == 1)){
    if ((last_current/voltage1)<RESISTANCE2) {
      SetBlinkLED2();
      //last_current = 0;
      state  = NO_CONTACT_CH;
     
    }
    if ((last_current/voltage1)>=RESISTANCE2) {
      ResetBlinkLED2();
      state = OK_CH;
    }
  }
  return state;
  
}
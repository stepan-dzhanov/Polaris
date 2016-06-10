
#include "protocol.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "channel_driver.h"

static uint8_t RxData[128];
static   uint8_t point =0;
UART_HandleTypeDef huart4;
static char ready=0;

static int _current_ch1=0;
static int _current_ch2=0;
static char _time_ch1 = 5;
static char _time_ch2 = 5;
static char _anode_ch1 =1;
static char _anode_ch2 =1;
static char _status_ch1 =0;
static char _status_ch2 =0;
static char end_ch1=0;
static char end_ch2=0;
static char stop_exchange=0;

void StopExchange(){
  stop_exchange = 1;
  _current_ch1=0;
  _current_ch2=0;
_time_ch1 = 5;
_time_ch2 = 5;
 _anode_ch1 =1;
_anode_ch2 =1;
_status_ch1 =0;
_status_ch2 =0;
end_ch1=0;
end_ch2=0; 
}
void StartExchange(){
  stop_exchange = 0;
}

void ON_LineControlCH1(){
   if ( (_status_ch1)&&(GetTimerCH1()>0)  ){
       if(RunCH1(_current_ch1, 0, 0)==NO_CONTACT_CH)     {
         StopTimerCH1();
       }
       else StartTimerCH1();
   }
     if ( (_status_ch1)&&(GetTimerCH1()==0)  ){
       RunCH1(0, 0, 0);
       //end_ch1=1;
     }
   if ( (!_status_ch1)&&(GetTimerCH1()==0)  ){
       RunCH1(0, 0, 0);
       
     }
    
     if ( (!_status_ch1)&&(GetTimerCH1()>0)  ){
       StopTimerCH1();
       RunCH1(_current_ch1, 1, 0);
     }
}

void ON_LineControlCH2(){
  ;
}





int EventProcessing(){
  int t_current_ch1=0;
  int t_current_ch2=0;
  char t_time_ch1 = 5;
  char t_time_ch2 = 5;
  char t_anode_ch1 =1;
  char t_anode_ch2 =1;
  char t_status_ch1 =0;
  char t_status_ch2 =0;
  uint8_t tx[32];
  static char bat=0;
  int tm;
  
  
  static char old_status_ch1=0;
  static char old_status_ch2=0;
  int temp;
  
  if(ready)  {
    t_status_ch1 = RxData[1];
    t_anode_ch1 = RxData[0];
    t_time_ch1 = RxData[2];
    t_current_ch1 = RxData[3];
    t_current_ch1 = t_current_ch1<<8;
    t_current_ch1 |= RxData[4];
    
    t_status_ch2 = RxData[6];
    t_anode_ch2 = RxData[5];
    t_time_ch2 = RxData[7];
    t_current_ch2 = RxData[8];
    t_current_ch2 = t_current_ch2<<8;
    t_current_ch2 |= RxData[9];
   // for(temp=0;temp<sizeof(RxData);temp++) RxData[temp]=0;   
    _status_ch1=t_status_ch1;
    _current_ch1=t_current_ch1;
    if((!old_status_ch1)&&(t_status_ch1)){
      _anode_ch1=t_anode_ch1;
      _status_ch1=t_status_ch1;
      _current_ch1=t_current_ch1;
      _time_ch1=t_time_ch1;
      end_ch1=0;
      old_status_ch1 = 1;
      SetTimerCH1(1*t_time_ch1);
      StartTimerCH1();
      
    }
    if((old_status_ch1)&&(!t_status_ch1)) {
      old_status_ch1 = 0;   
      //ResetTimerCH1();
    }
    
    
    
   
    tm = GetTimerCH1();
    tx[0] = (char)tm;
    tm = GetTimerCH2();
    tx[3] = (char)tm;
    tx[1] = (char)(GetADC1()/100);//Voltage1_1
    tx[2] = 0;//Voltage1_2
    tx[4] = 0;//Voltage2_1
    tx[5] = 0;//Voltage2_2
    if(bat)tx[6] = 75;//Battery
    else tx[6] = 82;
    tx[7] = end_ch1;//end procedure1
    tx[8] = end_ch2;//end procedure1
    
    
    bat ^=1;
    tx[9] = '\n';
    tx[10] = '\r';
    HAL_UART_Transmit(&huart4, tx, 11, 10);
    ready = 0;
   
    
  }
   ON_LineControlCH1();
  return 1;
   //ON_LineControlCH2();
  
  
  
  
  
  
  
  
  
}

void DataReceive(){
  uint8_t b;
  if(stop_exchange) {
    b = (uint8_t) (huart4.Instance->DR & (uint16_t) 0x00ff);
    return;
  }
  if(ready)     return;
  
  b = (uint8_t) (huart4.Instance->DR & (uint16_t) 0x00ff);
  RxData[point++]=b;
 
  if(point>=sizeof(RxData)) {
    point =0;
  }

  if((RxData[point-1]=='\r')&&(RxData[point-2]=='\n')) {
    if(point<12){
      point=0;
      return;
    }
    ready=1;
    point =0;
  }
  
  
}


void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
    /* Peripheral clock enable */
    __UART4_CLK_ENABLE();
  
    /**UART4 GPIO Configuration    
    PA0-WKUP     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
    
  /* USER CODE BEGIN UART4_MspInit 1 */
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
  /* USER CODE END UART4_MspInit 1 */
  }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __UART4_CLK_DISABLE();
  
    /**UART4 GPIO Configuration    
    PA0-WKUP     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_11);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(UART4_IRQn);

  }
  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */

}

void MX_UART4_Init()
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart4);

}

void MX_UART4_DeInit(void){
  point=0;
  ready =0;
  HAL_UART_MspDeInit(&huart4);
}
#ifndef __PROTOCOL__
#define __PROTOCOL__

void DataReceive();
void MX_UART4_Init(void);

int EventProcessing();
void StopExchange();
void StartExchange();
#endif
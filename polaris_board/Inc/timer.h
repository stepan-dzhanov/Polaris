#ifndef __TIMER3M__
#define __TIMER3M__


int GetTimerCH1();
void SetTimerCH1(int _time);
void SetTimerCH2(int _time);
void ResetTimerCH1();
void ResetTimerCH2();
int GetTimerCH2();
void Timer();
void StartTimerCH1();
void StopTimerCH1();
void StartTimerCH2();
void StopTimerCH2();


void ON_LED1()  ;
void OFF_LED1()  ;
void SetBlinkLED1();
void ResetBlinkLED1();
void ON_LED2() ;
void OFF_LED2() ;
void SetBlinkLED2();
void ResetBlinkLED2();






#endif
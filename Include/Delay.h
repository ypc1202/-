#ifndef _DELAY_H_
#define _DELAY_H_

void Timer0_Delay10us(UINT32 u32CNT);
void Timer1_Delay10us(UINT32 u32CNT);
void Timer2_Delay10us(UINT32 u32CNT);
void Timer3_Delay10us(UINT32 u32CNT);
void Timer0_Delay1ms (UINT32 u32CNT);
void Timer1_Delay1ms (UINT32 u32CNT);
void Timer2_Delay1ms (UINT32 u32CNT);
void Timer3_Delay1ms (UINT32 u32CNT);
void WakeUp_Timer_Delay25ms(UINT32 u32CNT);
void Random_Delay(void) reentrant; //reentrant --> 在中斷 ISR 調用此 function 時候

#endif
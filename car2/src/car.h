#ifndef _CAR_H
#define _CAR_H

#include "msp430.h"

#define left_low1 P2OUT&=~BIT6
#define left_low2 P2OUT&=~BIT7
#define right_low1 P2OUT&=~BIT5
#define right_low2 P1OUT&=~BIT7

#define left_high1 P2OUT|=BIT6
#define left_high2 P2OUT|=BIT7
#define right_high1 P2OUT|=BIT5
#define right_high2 P1OUT|=BIT7


#define PWM1  TA1CCR1
#define PWM2  TA1CCR2

void motor_init(void);//IO口初始化
void PWM_init(void);//PWM初始化

void motorrun1(int flag);
void motorrun2(int flag);
void motorrun3(int flag);
//void motorrun4(int flag);
void motorrun5(int flag);

void run1();
void run2();
void run3();
void run4();
void run5();

void run_pid1();
void run_pid2();
void run_pid3();
void run_pid4();
void run_pid5();

void back1();
void back2();

void turnleftsmall1();
void turnleftsmall2();
void turnleftsmall3();
void turnleftsmall4();
void turnleftsmall5();

void turnleftbig1();
void turnleftbig2();
void turnleftbig3();
void turnleftbig4();
void turnleftbig5();

void turnrightsmall1();
void turnrightsmall2();
void turnrightsmall3();
void turnrightsmall4();
void turnrightsmall5();

void turnrightbig1();
void turnrightbig2();
void turnrightbig3();
void turnrightbig4();
void turnrightbig5();

void stop();



#endif

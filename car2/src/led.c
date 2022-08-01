//P1.0:LED1

#include "led.h"
#include "msp430.h"

void led_init()
{
 P1DIR |= BIT0;
P1OUT |= BIT0;  //默认点亮LED1

P1DIR |= BIT3;
P1OUT &= ~BIT3;  //默认关闭蜂鸣器
}


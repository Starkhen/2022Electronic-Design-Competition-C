//P1.0:LED1

#include "led.h"
#include "msp430.h"

void led_init()
{
 P1DIR |= BIT0;
P1OUT |= BIT0;  //Ĭ�ϵ���LED1

P1DIR |= BIT3;
P1OUT &= ~BIT3;  //Ĭ�Ϲرշ�����
}


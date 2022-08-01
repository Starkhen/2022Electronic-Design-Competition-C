//P1.0:LED1
//P1.3:������
//P1.1  P1.6:����
//

#include "led.h"
#include "msp430.h"

void led_init()
{
 P1DIR |= BIT0;
P1OUT |= BIT0;  //Ĭ�ϵ���LED1

P1DIR |= BIT3;
P1OUT &= ~BIT3;  //Ĭ�Ϲرշ�����

P1DIR &= ~BIT1;     //P1.1��Ϊ����(��ʡ��)
P1REN |= BIT1;      //����P1.1�ڲ�����������
P1OUT |= BIT1;      //����������Ϊ����


P1DIR &= ~BIT6;     //P1.6��Ϊ����(��ʡ��)
P1REN |= BIT6;      //����P1.6�ڲ�����������
P1OUT |= BIT6;      //����������Ϊ����

}

int key_scan()
{
    if((P1IN & BIT1)==0 && (P1IN & BIT6)==0)    return 0;
    else if((P1IN & BIT1)==0 && (P1IN & BIT6)==BIT6)    return 1;
        else if((P1IN & BIT1)==BIT1 && (P1IN & BIT6)==0)    return 2;
            else if((P1IN & BIT1)==BIT1 && (P1IN & BIT6)==BIT6)    return 3;
                else    return 0;
}



//P1.0:LED1
//P1.3:蜂鸣器
//P1.1  P1.6:按键
//

#include "led.h"
#include "msp430.h"

void led_init()
{
 P1DIR |= BIT0;
P1OUT |= BIT0;  //默认点亮LED1

P1DIR |= BIT3;
P1OUT &= ~BIT3;  //默认关闭蜂鸣器

P1DIR &= ~BIT1;     //P1.1设为输入(可省略)
P1REN |= BIT1;      //启用P1.1内部上下拉电阻
P1OUT |= BIT1;      //将电阻设置为上拉


P1DIR &= ~BIT6;     //P1.6设为输入(可省略)
P1REN |= BIT6;      //启用P1.6内部上下拉电阻
P1OUT |= BIT6;      //将电阻设置为上拉

}

int key_scan()
{
    if((P1IN & BIT1)==0 && (P1IN & BIT6)==0)    return 0;
    else if((P1IN & BIT1)==0 && (P1IN & BIT6)==BIT6)    return 1;
        else if((P1IN & BIT1)==BIT1 && (P1IN & BIT6)==0)    return 2;
            else if((P1IN & BIT1)==BIT1 && (P1IN & BIT6)==BIT6)    return 3;
                else    return 0;
}



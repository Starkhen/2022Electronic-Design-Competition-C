#include "car.h"
#include "delay.h"
#include "uart.h"

extern int stop_flag;
int i;

//01为正转
void motor_init()//IO口初始化
{
  P2DIR |= BIT6;
  P2DIR |= BIT7;     //P2.6 p2.7为输出
  P2SEL &= ~BIT6; //将P2.6复用为io
  P2SEL &= ~BIT7; //将P2.7复用为io
  P2SEL2 &= ~BIT6;
  P2SEL2 &= ~BIT7;

  P2DIR |= BIT5;
  P1DIR |= BIT7;    //P2.3 p2.4为输出

}

void PWM_init()
{
    P2DIR |= BIT2+BIT4;
    P2SEL |= BIT2+BIT4; //设置为定时器复用
    P2SEL2 &= ~(BIT2 | BIT4); //设置为定时器复用
    TA1CCR0 = 512-1; //PWM周期，频率=32768/500
    TA1CCTL1 = OUTMOD_7; //CCR0输出模式7
    TA1CCR1 = 384; //CCR1
    TA1CCTL2 = OUTMOD_7; //CCR2输出模式7
    TA1CCR2 = 128; //CCR2
    //开启定时器
    TA1CTL = TASSEL_2 + MC_1 + TACLR; //定时器时钟设置为32768Hz的ACLK，配置为增模式，清空TA0R


}


void motorrun1(int flag)
{
     switch(flag)
        {
            case 0:run1();break;
            case 1:turnleftsmall1();break;
            case 2:turnleftbig1();delay_ms(100);break;
            case 3:turnrightsmall1();break;
            case 4:turnrightbig1();break;
            default:stop();
                    P1OUT |=BIT3;
                    delay_ms(200);
                    while(i<1000)
                    {
                    UARTSendString("STOP!\n",6);        //只发一次可能不够
                    i++;
                    }
                    delay_ms(5000);
                    P1OUT &=~BIT3;
                    stop_flag=1;
                    break;
        }

}

void motorrun2(int flag)
{
     switch(flag)
        {
            case 0:run2();break;
            case 1:turnleftsmall2();break;
            case 2:turnleftbig2();break;
            case 3:turnrightsmall2();break;
            case 4:turnrightbig2();break;
            default:stop();
                    P1OUT |=BIT3;
                    delay_ms(200);
                    while(i<1000)
                    {
                    UARTSendString("STOP!\n",6);        //只发一次可能不够
                    i++;
                    }
                    delay_ms(5000);
                    P1OUT &=~BIT3;
                    stop_flag=1;
                    break;
        }

}

void motorrun3(int flag)
{
     switch(flag)
        {
            case 0:run3();break;
            case 1:turnleftsmall3();break;
            case 2:turnleftbig3();break;
            case 3:turnrightsmall3();break;
            case 4:turnrightbig3();break;
            default:stop();
                    P1OUT |=BIT3;
                    delay_ms(200);
                    while(i<1000)
                    {
                    UARTSendString("STOP!\n",6);        //只发一次可能不够
                    i++;
                    }
                    delay_ms(5000);
                    P1OUT &=~BIT3;
                    stop_flag=1;
                    break;
        }

}


void motorrun4(int flag)
{
     switch(flag)
        {
            case 0:run2();break;
            case 1:turnleftsmall2();break;
            case 2:turnleftbig2();break;
            case 3:turnrightsmall2();break;
            case 4:turnrightbig2();break;
            case 6:delay_ms(5);stop();delay_ms(5000);break;
            default:stop();
                    P1OUT |=BIT3;
                    delay_ms(200);
                    while(i<1000)
                    {
                    UARTSendString("STOP!\n",6);        //只发一次可能不够
                    i++;
                    }
                    delay_ms(5000);
                    P1OUT &=~BIT3;
                    stop_flag=1;
                    break;
        }

}

void run1()
{
    left_low1;left_high2;
    right_low1;right_high2;
  PWM1=180;
  PWM2=180;
 }

void run2()
{
    left_low1;left_high2;
    right_low1;right_high2;
  PWM1=310;
  PWM2=310;
 }

void run3()
{
    left_low1;left_high2;
    right_low1;right_high2;
  PWM1=360;
  PWM2=360;
 }

void run4()
{
    left_low1;left_high2;
    right_low1;right_high2;
  PWM1=450;
  PWM2=450;
 }

void back()
{
    left_high1;left_low2;
    right_high1;right_low2;
    PWM1=50;
    PWM2=50;
}


void turnleftsmall1()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=50;
    PWM2=280;
 }

void turnleftsmall2()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=90;
    PWM2=300;
 }

void turnleftsmall3()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=90;
    PWM2=300;
 }

void turnleftsmall4()//小幅度
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=100;
    PWM2=500;
 }

void turnleftbig1()//大幅度
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=50;
    PWM2=200;
 }

void turnleftbig2()//大幅度
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=120;
    PWM2=320;
 }

void turnleftbig3()//大幅度
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=100;
    PWM2=320;
 }

void turnleftbig4()//大幅度
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=400;
    PWM2=500;
 }

void turnrightsmall1()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=300;
    PWM2=60;
 }

void turnrightsmall2()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=400;
    PWM2=50;
 }

void turnrightsmall3()//小幅度
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=390;
    PWM2=50;
 }

void turnrightsmall4()//小幅度
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=500;
    PWM2=100;
 }

void turnrightbig1()//大幅度
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=320;
    PWM2=130;
 }

void turnrightbig2()//大幅度
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=380;
    PWM2=150;
 }

void turnrightbig3()//大幅度
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=380;
    PWM2=180;
 }

void turnrightbig4()//大幅度
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=500;
    PWM2=400;
 }

void stop()
{
    left_low1;left_low2;
    right_low1;right_low2;
}

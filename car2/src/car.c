#include "car.h"
#include "delay.h"
#include "PID.h"
#include "distance.h"

extern int deta_pwm;
extern int stop_flag;

//01Ϊ��ת
void motor_init()//IO�ڳ�ʼ��
{
  P2DIR |= BIT6;
  P2DIR |= BIT7;     //P2.6 p2.7Ϊ���
  P2SEL &= ~BIT6; //��P2.6����Ϊio
  P2SEL &= ~BIT7; //��P2.7����Ϊio
  P2SEL2 &= ~BIT6;
  P2SEL2 &= ~BIT7;

  P2DIR |= BIT5;
  P1DIR |= BIT7;    //P2.3 p2.4Ϊ���

}

void PWM_init()
{
    P2DIR |= BIT2+BIT4;
    P2SEL |= BIT2+BIT4; //����Ϊ��ʱ������
    P2SEL2 &= ~(BIT2 | BIT4); //����Ϊ��ʱ������
    TA1CCR0 = 512-1; //PWM���ڣ�Ƶ��=32768/500
    TA1CCTL1 = OUTMOD_7; //CCR0���ģʽ7
    TA1CCR1 = 384; //CCR1
    TA1CCTL2 = OUTMOD_7; //CCR2���ģʽ7
    TA1CCR2 = 128; //CCR2
    //������ʱ��
    TA1CTL = TASSEL_2 + MC_1 + TACLR; //��ʱ��ʱ������Ϊ32768Hz��ACLK������Ϊ��ģʽ�����TA0R


}


void motorrun1(int flag)
{
     switch(flag)
        {
            case 0: if(distance>60)             {run1();}
                        else if (distance<15)   {back1();}
                                else            {run_pid1();}
                    break;
            case 1:turnleftsmall1();break;
            case 2:turnleftbig1();break;
            case 3:turnrightsmall1();break;
            case 4:turnrightbig1();break;
            default:stop();P1OUT |=BIT3;delay_ms(5000);P1OUT &=~BIT3;stop_flag=1;break;    //��Ҫ�Ӹ����������䲻��
        }

}

void motorrun2(int flag)
{
     switch(flag)
        {
            case 0: if(distance>40)             {run2();}
                        else if (distance<15)   {back2();}
                                else            {run_pid2();}
                    break;
            case 1:turnleftsmall2();break;
            case 2:turnleftbig2();delay_ms(20);break;
            case 3:turnrightsmall2();break;
            case 4:turnrightbig2();break;
            default:stop();P1OUT |=BIT3;delay_ms(5000);P1OUT &=~BIT3;stop_flag=1;break;    //��Ҫ�Ӹ����������䲻��
        }

}

void motorrun3(int flag)
{
     switch(flag)
        {
            case 0: if(distance>23)             {run3();}
                        else if (distance<10)   {back1();}
                                else            {run_pid3();}
                    break;
            case 1:turnleftsmall3();break;
            case 2:turnleftbig3();break;
            case 3:turnrightsmall3();break;
            case 4:turnrightbig3();break;
            default:stop();P1OUT |=BIT3;delay_ms(5000);P1OUT &=~BIT3;stop_flag=1;break;    //��Ҫ�Ӹ����������䲻��
        }

}


void motorrun5(int flag)
{
     switch(flag)
        {
            case 0: if(distance>70)             {run5();}
                        else if (distance<10)   {back1();}
                                else            {run_pid5();}
                    break;
            case 1:turnleftsmall5();break;
            case 2:turnleftbig5();break;
            case 3:turnrightsmall5();break;
            case 4:turnrightbig5();break;
            default:stop();P1OUT |=BIT3;delay_ms(5000);P1OUT &=~BIT3;stop_flag=1;break;    //��Ҫ�Ӹ����������䲻��
        }

}

void run_pid1()
{
    left_low1;left_high2;
    right_low1;right_high2;
    deta_pwm=get_pid(160,0,1,distance);
    deta_pwm=Limit_Pwm(deta_pwm,-70,70);
    PWM1=180+deta_pwm;
    PWM2=180+deta_pwm;
 }

void run_pid2()
{
    left_low1;left_high2;
    right_low1;right_high2;
    deta_pwm=get_pid(50,0,10,distance);
    deta_pwm=Limit_Pwm(deta_pwm,-50,30);
    PWM1=310+deta_pwm;
    PWM2=310+deta_pwm;
 }

void run_pid3()
{
    left_low1;left_high2;
    right_low1;right_high2;
    deta_pwm=get_pid(60,0,1,distance);
    deta_pwm=Limit_Pwm(deta_pwm,-40,40);
    PWM1=180+deta_pwm;
    PWM2=180+deta_pwm;
 }

void run_pid5()
{
    left_low1;left_high2;
    right_low1;right_high2;
    deta_pwm=get_pid(40,0,30,distance);
    deta_pwm=Limit_Pwm(deta_pwm,-150,100);
    PWM1=180+deta_pwm;
    PWM2=180+deta_pwm;
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
    PWM1=300;
    PWM2=300;
 }

void run3()
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=200;
    PWM2=200;
 }

void run5()
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=85;
    PWM2=85;
 }




void back1()
{
    left_high1;left_low2;
    right_high1;right_low2;
    PWM1=50;
    PWM2=50;
}

void back2()
{
    left_high1;left_low2;
    right_high1;right_low2;
    PWM1=120;
    PWM2=120;
}

void turnleftsmall1()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=50;
    PWM2=250;
 }

void turnleftsmall2()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=80;
    PWM2=310;
 }

void turnleftsmall3()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=50;
    PWM2=320;
 }

void turnleftsmall5()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=30;
    PWM2=130;
 }



void turnleftbig1()//�����
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=30;
    PWM2=250;
 }

void turnleftbig2()//�����
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=100;
    PWM2=310;
 }

void turnleftbig3()//�����
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=60;
    PWM2=250;
 }

void turnleftbig5()//�����
{
    left_high1;left_low2;
    right_low1;right_high2;
    PWM1=80;
    PWM2=150;
 }

void turnrightsmall1()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=300;
    PWM2=60;
 }

void turnrightsmall2()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=390;
    PWM2=50;
 }

void turnrightsmall3()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=420;
    PWM2=50;
 }

void turnrightsmall5()//С����
{
    left_low1;left_high2;
    right_low1;right_high2;
    PWM1=250;
    PWM2=30;
 }



void turnrightbig1()//�����
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=300;
    PWM2=90;
 }

void turnrightbig2()//�����
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=300;
    PWM2=50;
 }

void turnrightbig3()//�����
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=400;
    PWM2=160;
 }

void turnrightbig5()//�����
{
    left_low1;left_high2;
    right_high1;right_low2;
    PWM1=200;
    PWM2=90;
 }




void stop()
{
    left_low1;left_low2;
    right_low1;right_low2;
}

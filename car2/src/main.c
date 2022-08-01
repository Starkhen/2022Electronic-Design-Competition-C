 #include <msp430.h>
#include "led.h"
#include "car.h"
#include "xunji.h"
#include "uart.h"
#include "distance.h"
#include "delay.h"



int deta_pwm;
int flag=0;     //ѭ�����Ľ������
int stop_flag=0;
int key_flag=0;
int panduan=0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // �رտ��Ź���ʱ��

 /*����DCOΪ1MHz*/
    DCOCTL = CALDCO_1MHZ;
   BCSCTL1 = CALBC1_1MHZ;
 /*����SMCLK��ʱ��ԴΪDCO*/
    BCSCTL2 &= ~SELS;
/*SMCLK�ķ�Ƶϵ����Ϊ1*/
   BCSCTL2 &= ~(DIVS0 | DIVS1);

    led_init();
    motor_init();//IO�ڳ�ʼ��
    PWM_init();//PWM��ʼ��
    xunji_Init();
    distance_init();
    uart_init();

    _EINT();
  //  __bis_SR_register(GIE);//��ȫ���ж�

    while(1)
   {
      send_15us();  //����15us�ĸߵ�ƽ

    if(iscomend)
      {
       uart_detect();
       iscomend=0;
      } //����յ�ǰ����STOP!�źţ���ֹͣ

    if(key_flag==1) {flag=xunji1_detect();motorrun1(flag);}
    if(key_flag==2) {flag=xunji2_detect();motorrun2(flag);}
    if(key_flag==3) {
        flag=xunji3_detect();
        if(panduan!=1)
        {
        motorrun3(flag);
        }else {motorrun5(flag);}
    }
    if(key_flag==4) {flag=xunji4_detect();motorrun1(flag);}
    if(stop_flag==1){stop();P1OUT |=BIT3;delay_ms(5000);P1OUT &=~BIT3;break;}
   }
}



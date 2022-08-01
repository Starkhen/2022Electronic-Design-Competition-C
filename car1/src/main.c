 #include <msp430.h>
#include "led.h"
#include "car.h"
#include "xunji.h"
#include "uart.h"
#include "delay.h"



int key_flag=0; //����ѡ�����
int flag=0;     //ѭ�����Ľ������
int stop_flag=0;        //ֹͣ�������

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
    uart_init();

    key_flag=key_scan();

    _EINT();
  //  __bis_SR_register(GIE);//��ȫ���ж�

    delay_ms(3000); //��ʱ2��ȴ���������
    while(1)
   {
       // UARTSendString("flag3!\n",7);
          if(key_flag==0)
          {
             UARTSendString("flag1!\n",7);
            flag=xunji1_detect();
            motorrun1(flag);
          }else if(key_flag==1)
          {
           UARTSendString("flag2!\n",7);
              flag=xunji2_detect();
              motorrun2(flag);
          }else if(key_flag==2)
          {
           UARTSendString("flag3!\n",7);
              flag=xunji3_detect();
              motorrun3(flag);
          }else if(key_flag==3)
          {
             UARTSendString("flag4!\n",7);
              flag=xunji4_detect();
              motorrun4(flag);
          }
          if(stop_flag==1)   break;  //�˳�����
   }
}



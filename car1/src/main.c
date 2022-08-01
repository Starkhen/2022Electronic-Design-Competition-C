 #include <msp430.h>
#include "led.h"
#include "car.h"
#include "xunji.h"
#include "uart.h"
#include "delay.h"



int key_flag=0; //按键选择变量
int flag=0;     //循迹检测的结果变量
int stop_flag=0;        //停止程序变量

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // 关闭看门狗定时器

 /*配置DCO为1MHz*/
    DCOCTL = CALDCO_1MHZ;
   BCSCTL1 = CALBC1_1MHZ;
 /*配置SMCLK的时钟源为DCO*/
    BCSCTL2 &= ~SELS;
/*SMCLK的分频系数置为1*/
   BCSCTL2 &= ~(DIVS0 | DIVS1);

     led_init();
    motor_init();//IO口初始化
    PWM_init();//PWM初始化
    xunji_Init();
    uart_init();

    key_flag=key_scan();

    _EINT();
  //  __bis_SR_register(GIE);//打开全局中断

    delay_ms(3000); //延时2秒等待蓝牙连接
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
          if(stop_flag==1)   break;  //退出程序
   }
}



//5路循迹
//cgq1 P1.4 cgq2 P1.5   cgq3 P2.0   cgq4 P2.1   cgq5 P2.3
//xunji_detect可以检测，返回值为对应姿态
//返回0：直走    1：左小转       2：左大转   3：右小转   4右大转  5:停
//可在xunji_detect中调整第几条黑线转

//要xunji_Init()初始化光电对管IO口
//要根据具体的题目要求改blackall的判断
#include "xunji.h"
#include "delay.h"
#include "stdio.h"
#include "led.h"

void xunji_Init(void)
{
    P1DIR &= ~BIT4;
    P1DIR &= ~BIT5;
    P2DIR &= ~BIT0;
    P2DIR &= ~BIT1;
    P2DIR &= ~BIT3;

    P1REN |= BIT4;
    P1OUT |= BIT4;
    P1REN |= BIT5;
    P1OUT |= BIT5;
    P2REN |= BIT0;
    P2OUT |= BIT0;
    P2REN |= BIT1;
    P2OUT |= BIT1;
    P2REN |= BIT3;
    P2OUT |= BIT3;
}



int xunji1_detect()
 {
         static int c;
         static int blackall;
         if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,计数
         {
             delay_ms(20);
             if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
             blackall++;

         }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  左大转弯
//           {
//               return 2;
//           }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  左大转弯
//           {
//              return 2;
//           }
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 右小转
                   return 3;
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 右小转
                   return 3;
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 右大转
                   return 4;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 右大转
                 return 4;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 右小转
                 return 3;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 右大转
                 return 4;
           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 左大转弯
              return 2;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 左小转弯
             return 1;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 左小转弯
             return 1;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
//          {
//               return 4;
//           }
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 右小转弯
             return 3;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 直走
             return 0;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 右大转弯
//           {
//              return 4;
//          }
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 右小转弯
             return 3;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 右大转弯
              return 4;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 抖动
             return 0;   //可能要写个抖动的


         if(c!=blackall)
         {
              if(blackall==1)
              {c++;return 5;         //检测到第一条全黑时，掉头
              }
              if(blackall==2)
              {c++;return 5;         //检测到第二条全黑时，停
              }
          }

          return 0;
}



 int xunji2_detect()
  {
          static int c;
          static int blackall;
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,计数
          {
              delay_ms(35);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;


          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  左大转弯
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  左大转弯
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 右大转
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 右大转
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 右小转
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 右大转
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 左大转弯
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 左小转弯
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 左小转弯
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 直走
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 右大转弯
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 右大转弯
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 抖动
              return 0;   //可能要写个抖动的


          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 0;         //检测到第一条全黑时，掉头
               }
               if(blackall==2)
               {c++;return 5;         //检测到第二条全黑时，停
               }
           }

           return 0;
 }

 int xunji3_detect()
  {
          static int c;
          static int blackall;
    if(blackall==0 || blackall==1)
    {
        LED1_OFF;
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,计数
          {
              delay_ms(35);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;

          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  左大转弯
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  左大转弯
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 右大转
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 右大转
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 右小转
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 右大转
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 左大转弯
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 左小转弯
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 左小转弯
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 直走
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 右大转弯
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 右大转弯
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 抖动
              return 0;   //可能要写个抖动的
    }else
    {
        LED1_ON;
        if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,计数
        {
            delay_ms(35);
            if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
            blackall++;

        }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  左大转弯
//           {
//               return 2;
//           }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  左大转弯
//           {
//              return 2;
//           }
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 左小转
                  return 1;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 左大转
                  return 2;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 左大转
                  return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 左小转
                return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 左大转
                return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 左大转
                return 2;
          if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 左大转弯
             return 2;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 左小转弯
            return 1;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 左小转弯
            return 1;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
//          {
//               return 4;
//           }
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 右小转弯
            return 3;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 直走
            return 0;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 右大转弯
//           {
//              return 4;
//          }
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 右小转弯
            return 3;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 右大转弯
             return 4;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 抖动
            return 0;   //可能要写个抖动的
    }

          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 0;         //检测到第一条全黑时，掉头
               }
               if(blackall==2)
               {c++;return 0;         //检测到第二条全黑时，停
               }
               if(blackall==3)
               {c++;return 5;         //检测到第二条全黑时，停
               }

           }

           return 0;
 }

 int xunji4_detect()
  {
          static int c;
          static int blackall;
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,计数
          {
              delay_ms(20);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;

          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  左大转弯
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  左大转弯
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 右小转
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 右大转
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 右大转
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 右小转
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 右大转
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 左大转弯
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 左小转弯
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 左小转弯
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 直走
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 右大转弯
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 右小转弯
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 右大转弯
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 抖动
              return 0;   //可能要写个抖动的


          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 6;         //等停
               }
               if(blackall==2)
               {c++;return 5;         //检测到第二条全黑时，停
               }
           }

           return 0;
 }

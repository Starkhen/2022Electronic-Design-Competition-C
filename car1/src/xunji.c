//5·ѭ��
//cgq1 P1.4 cgq2 P1.5   cgq3 P2.0   cgq4 P2.1   cgq5 P2.3
//xunji_detect���Լ�⣬����ֵΪ��Ӧ��̬
//����0��ֱ��    1����Сת       2�����ת   3����Сת   4�Ҵ�ת  5:ͣ
//����xunji_detect�е����ڼ�������ת

//Ҫxunji_Init()��ʼ�����Թ�IO��
//Ҫ���ݾ������ĿҪ���blackall���ж�
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
         if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,����
         {
             delay_ms(20);
             if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
             blackall++;

         }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  ���ת��
//           {
//               return 2;
//           }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  ���ת��
//           {
//              return 2;
//           }
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 ��Сת
                   return 3;
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 ��Сת
                   return 3;
             if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 �Ҵ�ת
                   return 4;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 �Ҵ�ת
                 return 4;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 ��Сת
                 return 3;
             if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 �Ҵ�ת
                 return 4;
           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 ���ת��
              return 2;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 ��Сת��
             return 1;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 ��Сת��
             return 1;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
//          {
//               return 4;
//           }
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 ��Сת��
             return 3;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 ֱ��
             return 0;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 �Ҵ�ת��
//           {
//              return 4;
//          }
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 ��Сת��
             return 3;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 �Ҵ�ת��
              return 4;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 ����
             return 0;   //����Ҫд��������


         if(c!=blackall)
         {
              if(blackall==1)
              {c++;return 5;         //��⵽��һ��ȫ��ʱ����ͷ
              }
              if(blackall==2)
              {c++;return 5;         //��⵽�ڶ���ȫ��ʱ��ͣ
              }
          }

          return 0;
}



 int xunji2_detect()
  {
          static int c;
          static int blackall;
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,����
          {
              delay_ms(35);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;


          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  ���ת��
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  ���ת��
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 �Ҵ�ת
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 �Ҵ�ת
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 ��Сת
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 �Ҵ�ת
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 ���ת��
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 ��Сת��
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 ��Сת��
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 ֱ��
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 �Ҵ�ת��
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 �Ҵ�ת��
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 ����
              return 0;   //����Ҫд��������


          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 0;         //��⵽��һ��ȫ��ʱ����ͷ
               }
               if(blackall==2)
               {c++;return 5;         //��⵽�ڶ���ȫ��ʱ��ͣ
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
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,����
          {
              delay_ms(35);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;

          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  ���ת��
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  ���ת��
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 �Ҵ�ת
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 �Ҵ�ת
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 ��Сת
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 �Ҵ�ת
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 ���ת��
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 ��Сת��
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 ��Сת��
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 ֱ��
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 �Ҵ�ת��
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 �Ҵ�ת��
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 ����
              return 0;   //����Ҫд��������
    }else
    {
        LED1_ON;
        if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,����
        {
            delay_ms(35);
            if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
            blackall++;

        }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  ���ת��
//           {
//               return 2;
//           }
//           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  ���ת��
//           {
//              return 2;
//           }
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 ��Сת
                  return 1;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 ���ת
                  return 2;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 ���ת
                  return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 ��Сת
                return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 ���ת
                return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 ���ת
                return 2;
          if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 ���ת��
             return 2;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 ��Сת��
            return 1;
          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 ��Сת��
            return 1;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
//          {
//               return 4;
//           }
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 ��Сת��
            return 3;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 ֱ��
            return 0;
//          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 �Ҵ�ת��
//           {
//              return 4;
//          }
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 ��Сת��
            return 3;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 �Ҵ�ת��
             return 4;
         if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 ����
            return 0;   //����Ҫд��������
    }

          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 0;         //��⵽��һ��ȫ��ʱ����ͷ
               }
               if(blackall==2)
               {c++;return 0;         //��⵽�ڶ���ȫ��ʱ��ͣ
               }
               if(blackall==3)
               {c++;return 5;         //��⵽�ڶ���ȫ��ʱ��ͣ
               }

           }

           return 0;
 }

 int xunji4_detect()
  {
          static int c;
          static int blackall;
          if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)) //X000X,����
          {
              delay_ms(20);
              if(((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2))
              blackall++;

          }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00011  ���ת��
 //           {
 //               return 2;
 //           }
 //           if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //00111  ���ת��
 //           {
 //              return 2;
 //           }
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01011 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01101 ��Сת
                    return 3;
              if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //01110 �Ҵ�ת
                    return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11010 �Ҵ�ת
                  return 4;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //10110 ��Сת
                  return 3;
              if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //10101 �Ҵ�ת
                  return 4;
            if(((P1IN & BIT4)==16)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //01111 ���ת��
               return 2;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10011 ��Сת��
              return 1;
            if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==32)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //10111 ��Сת��
              return 1;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11000
 //          {
 //               return 4;
 //           }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11001 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==1)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11011 ֱ��
              return 0;
 //          if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==8)) //11100 �Ҵ�ת��
 //           {
 //              return 4;
 //          }
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==2)&&((P2IN & BIT3)==0)) //11101 ��Сת��
              return 3;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==8)) //11110 �Ҵ�ת��
               return 4;
           if(((P1IN & BIT4)==0)&&((P1IN & BIT5)==0)&&((P2IN & BIT0)==0)&&((P2IN & BIT1)==0)&&((P2IN & BIT3)==0)) //11111 ����
              return 0;   //����Ҫд��������


          if(c!=blackall)
          {
               if(blackall==1)
               {c++;return 6;         //��ͣ
               }
               if(blackall==2)
               {c++;return 5;         //��⵽�ڶ���ȫ��ʱ��ͣ
               }
           }

           return 0;
 }

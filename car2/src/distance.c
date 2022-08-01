#include "distance.h"
#include "delay.h"

unsigned int  result1_start,result1_end;
unsigned char index=0;
unsigned int  temp;
double   distance;

void send_15us()
{
         P1OUT&=~BIT6;
         delay_us(20);
         P1OUT|=BIT6;
         delay_us(15);
         P1OUT&=~BIT6;
}

void distance_init()
{
    //����IO
            P1DIR &=~BIT2;   //P1.2,Ϊ��������  ��ECHO
            P1SEL |= BIT2;   // P1.2 = (TA0.CCI1A) = CCIxA.1 --> CCR1��P1.6��Ϊ���룬CCI1A��ָ������//�����ֲ�page43
            P1SEL2 &=~BIT2;

            P1DIR|=BIT6;            //��TRIG,����Ϊ�������
    //���ö�ʱ��
            TACCTL1 = CAP + CCIS_0 + CM_3 + CCIE+SCS;   // ����ģʽ,��׽/�Ƚ�����ѡ��CCIxA,�����غ��½��ض��ߵĲ�׽,ʹ�ܲ�׽/�Ƚ��ж�,CCI1A->p1.2(ʹ�ö�ʱ��ʱ��ͬ����׽�����ź�)
            TACTL |=TASSEL_2 + ID_0 + MC_2+ TAIE+TACLR ;//ѡ��1M��SMCLKʱ�ӣ�����Ƶ������ģʽ��ʹ�ܶ�ʱ��_A�жϣ���λ TAR��ʱ�ӷ�Ƶ�����ͼ�������
            TACCR1=0;//��һ����׽��ִ��ʱ����ʱ��_A �Ĵ�����TAR�������ƽ� TACCRx �Ĵ�����
            TACTL&=~CCIFG;
}


/*==================================TA���жϷ������=========================================
�������ƣ� Timer_A ISR (INTERRUPT SERVICE REGISTER)
�������ܣ� ��ʱ��A�жϷ����Ӻ���,��������ź�������,�½���
����������CCR0������ռ���˸��жϣ���TIMER0_A0_VECTOR,�����ĺ�����TIMER0_A1_VECTOR�����Խ����жϺ�Ҫ�ж���CCR1������CCR2�������жϣ�Ҳ����TAOIV����
TA1IV��Ӧcase  :2 ��4,��������㲻����TAIV����Ĵ��������������һЩ��־λ��Ҫ���ֶ��������λ�ˣ���֮��Ӳ���Լ���λ�����ڲ�����Ӳ������ģ����Ƚ�׼��
=========================================================================================*/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TAIV_ISR(void)
{
         switch(TA0IV)
                {
                 case 2:{                   //ccr1�ж�����
                         if (TACCTL1&CCI)    //�����ش���  ѡ��������źſ���ͨ��CCIλ��ȡ��
                                {
                                     result1_start=CCR1;//��¼��ʼֵ
                                     index=0;  //��0��ʼ����

                                     break;
                                }
                         else
                           {
                                    result1_end=CCR1;          //��¼����ֵ
                                    if(result1_end>result1_start)//����ȿ�ʼ��ֵС����ʾ�����һ�λ��߼��Σ�����һ���0��ʼ�����Ļ��ǲ�����ģ��ⳬ����ʵ�ʲⲻ����ôԶ������и�4�ף�5�׵������Ѿ��ܺ���

                                       temp=result1_end-result1_start;
                                    else
                                       temp=result1_end+index*65535-result1_start;
//����=��ʱ��*�ٶȣ�/2
//����=������������/Ƶ�ʣ�*340/2�� m/s=(temp/1000000)*170 00  cm/s=temp*0.0172 cm/s
                                    distance=temp*0.0172;
                                    if(distance<10)
                                    {
                                    P1OUT|=BIT0;
                                    }
                                    if(distance>=10)
                                    {
                                     P1OUT&=~BIT0;
                                    }
                                    index=0;         //�����������
                                    break;
                           }}
                 case 4: break;
                 case 10:index++;break;  //��ʱ������ж���������ʵ��2,4,10����������.
                 default :break;
                }
}

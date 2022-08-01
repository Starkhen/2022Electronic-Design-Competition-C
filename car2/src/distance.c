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
    //设置IO
            P1DIR &=~BIT2;   //P1.2,为输入引脚  接ECHO
            P1SEL |= BIT2;   // P1.2 = (TA0.CCI1A) = CCIxA.1 --> CCR1，P1.6作为输入，CCI1A，指定输入//数据手册page43
            P1SEL2 &=~BIT2;

            P1DIR|=BIT6;            //接TRIG,设置为输出方向
    //设置定时器
            TACCTL1 = CAP + CCIS_0 + CM_3 + CCIE+SCS;   // 捕获模式,捕捉/比较输入选择CCIxA,上升沿和下降沿二者的捕捉,使能捕捉/比较中断,CCI1A->p1.2(使用定时器时钟同步捕捉输入信号)
            TACTL |=TASSEL_2 + ID_0 + MC_2+ TAIE+TACLR ;//选择1M－SMCLK时钟，不分频，连续模式，使能定时器_A中断；复位 TAR，时钟分频器，和计数方向
            TACCR1=0;//当一个捕捉被执行时，定时器_A 寄存器，TAR，被复制进 TACCRx 寄存器。
            TACTL&=~CCIFG;
}


/*==================================TA的中断服务程序=========================================
函数名称： Timer_A ISR (INTERRUPT SERVICE REGISTER)
函数功能： 定时器A中断服务子函数,捕获待测信号上升沿,下降沿
函数参数：CCR0单独的占用了个中断，是TIMER0_A0_VECTOR,其他的合着用TIMER0_A1_VECTOR，所以进入中断后要判断是CCR1，还是CCR2产生的中断，也就是TAOIV或者
TA1IV对应case  :2 和4,另外如果你不访问TAIV这个寄存器，那你产生的一些标志位就要你手动的软件复位了，反之是硬件自己复位。由于捕获是硬件捕获的，测距比较准。
=========================================================================================*/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TAIV_ISR(void)
{
         switch(TA0IV)
                {
                 case 2:{                   //ccr1中断向量
                         if (TACCTL1&CCI)    //上升沿触发  选择的输入信号可以通过CCI位读取。
                                {
                                     result1_start=CCR1;//记录初始值
                                     index=0;  //从0开始计数

                                     break;
                                }
                         else
                           {
                                    result1_end=CCR1;          //记录结束值
                                    if(result1_end>result1_start)//结果比开始数值小，表示溢出了一次或者几次，但是一般从0开始计数的话是不溢出的，这超声波实际测不了那么远，最多有个4米，5米的样子已经很好了

                                       temp=result1_end-result1_start;
                                    else
                                       temp=result1_end+index*65535-result1_start;
//距离=（时间*速度）/2
//距离=（（计数次数/频率）*340/2） m/s=(temp/1000000)*170 00  cm/s=temp*0.0172 cm/s
                                    distance=temp*0.0172;
                                    if(distance<10)
                                    {
                                    P1OUT|=BIT0;
                                    }
                                    if(distance>=10)
                                    {
                                     P1OUT&=~BIT0;
                                    }
                                    index=0;         //溢出次数清零
                                    break;
                           }}
                 case 4: break;
                 case 10:index++;break;  //定时器溢出中断向量，其实就2,4,10号向量有用.
                 default :break;
                }
}

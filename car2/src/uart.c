#include "uart.h"
#include <msp430.h>
#include "stdint.h"
#include "led.h"

uint8_t combuff[20] = {0};//长度为20的命令缓冲区，用于保存串口命令
uint8_t iscomend = 0;//命令结束？用于判断是否一句完整的命令已经成功接收

extern int stop_flag;
extern int key_flag;

void uart_detect()
{
    const uint8_t charbuff[5][10] = {"flag1","flag2","flag3","flag4","STOP!"};//保存预置命令
    if(combuff[0] == charbuff[0][0] && combuff[4] == charbuff[0][4])//王龙？
    {
        key_flag=1;
    }
    else if(combuff[0] == charbuff[1][0] && combuff[4] == charbuff[1][4])//米靳隆？
    {
        key_flag=2;
    }
    else if(combuff[0] == charbuff[2][0] && combuff[4] == charbuff[2][4])//班长？
    {
        key_flag=3;
    }
    else if(combuff[0] == charbuff[3][0] && combuff[4] == charbuff[3][4])//LED1 On!
    {
        key_flag=4;
    }
    else if(combuff[0] == charbuff[4][0] && combuff[3] == charbuff[4][3])//LED1 Off!
    {
        stop_flag=1;
    }
}


void uart_init(void)
{
    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;

    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*配置波特率为9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*使能端口复用*/
    P1SEL |= BIT1;
    P1SEL2 |= BIT1;

    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;

    //接收中断启用
    IE2 |= UCA0RXIE;
    //清空接收中断标志
    IFG2 &= ~UCA0RXIFG;

}

void UARTSendString(uint8_t *pbuff,uint8_t num)
{
    uint8_t cnt = 0;
    for(cnt = 0;cnt < num;cnt ++)
    {
        while(UCA0STAT & UCBUSY);
        UCA0TXBUF = *(pbuff + cnt);
    }
}


#pragma vector = USCIAB0RX_VECTOR
__interrupt void UART_Receive_ISR(void)
{
    static uint8_t cnt = 0;
    if(IFG2 & UCA0RXIFG)//检测是否是USCI_A0的接收中断，USCI_A0和USIC_B0的接收中断共享同一向量
    {
        IFG2 &= ~UCA0RXIFG;//清除标志位
        combuff[cnt++] = UCA0RXBUF;//保存命令
        cnt %= 20;//防止cnt大于20，导致缓冲区溢出
        if(combuff[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
        {
            cnt = 0;//复位计数器
            iscomend = 1;//命令接收完毕
        }
    }
}

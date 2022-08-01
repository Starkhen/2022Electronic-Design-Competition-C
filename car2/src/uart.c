#include "uart.h"
#include <msp430.h>
#include "stdint.h"
#include "led.h"

uint8_t combuff[20] = {0};//����Ϊ20��������������ڱ��洮������
uint8_t iscomend = 0;//��������������ж��Ƿ�һ�������������Ѿ��ɹ�����

extern int stop_flag;
extern int key_flag;

void uart_detect()
{
    const uint8_t charbuff[5][10] = {"flag1","flag2","flag3","flag4","STOP!"};//����Ԥ������
    if(combuff[0] == charbuff[0][0] && combuff[4] == charbuff[0][4])//������
    {
        key_flag=1;
    }
    else if(combuff[0] == charbuff[1][0] && combuff[4] == charbuff[1][4])//�׽�¡��
    {
        key_flag=2;
    }
    else if(combuff[0] == charbuff[2][0] && combuff[4] == charbuff[2][4])//�೤��
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
    /*��λUSCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*ѡ��USCI_AxΪUARTģʽ*/
    UCA0CTL0 &= ~UCSYNC;

    /*����UARTʱ��ԴΪSMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*���ò�����Ϊ9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*ʹ�ܶ˿ڸ���*/
    P1SEL |= BIT1;
    P1SEL2 |= BIT1;

    /*�����λλ��ʹ��UART*/
    UCA0CTL1 &= ~UCSWRST;

    //�����ж�����
    IE2 |= UCA0RXIE;
    //��ս����жϱ�־
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
    if(IFG2 & UCA0RXIFG)//����Ƿ���USCI_A0�Ľ����жϣ�USCI_A0��USIC_B0�Ľ����жϹ���ͬһ����
    {
        IFG2 &= ~UCA0RXIFG;//�����־λ
        combuff[cnt++] = UCA0RXBUF;//��������
        cnt %= 20;//��ֹcnt����20�����»��������
        if(combuff[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
        {
            cnt = 0;//��λ������
            iscomend = 1;//����������
        }
    }
}

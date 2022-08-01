/*
 * delay.h
 *
 *  Created on: 2022��7��27��
 *      Author: 25309
 */

#ifndef _DELAY_H_
#define _DELAY_H_


#include <msp430.h>


/********************************************************************/
//��ʱ����
//#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
//#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

//������ʱ��Ƶ�ʣ�����ʱʹ��
#define MCLK_C      (1)
#define delay_us(n)  __delay_cycles(n*MCLK_C)
#define delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)



#endif /* SRC_DELAY_H_ */

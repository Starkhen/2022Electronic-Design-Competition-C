#ifndef __XUNJI_H
#define __XUNJI_H
#include "msp430g2553.h"


#define xian_delay 25   //ÿ������״̬������ʱus



void xunji_Init(void);
int xunji1_detect(void);
int xunji2_detect(void);
int xunji3_detect(void);
int xunji4_detect(void);

#endif


#ifndef SRC_LED_H_
#define SRC_LED_H_

#define LED1_ON P1OUT |= BIT0
#define LED1_OFF P1OUT &= ~BIT0

#define BEEP_ON P1OUT |= BIT3
#define BEEP_OFF P1OUT &= ~BIT3

void led_init();

#endif /* SRC_LED_H_ */

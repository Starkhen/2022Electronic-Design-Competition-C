/*
 * PID.h
 *
 *  Created on: 2022��7��29��
 *      Author: 25309
 */

#ifndef SRC_PID_H_
#define SRC_PID_H_

int get_pid(float kp,float ki,float kd,float actual_value );
int Limit_Pwm(int IN,int min,int max);



#endif /* SRC_PID_H_ */

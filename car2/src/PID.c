//����PID�������������Ϊkp��ki��kd��ʵ��ֵ������ֵ=20cm
//Ϊԭ�����pwm_pid
//������pi=0����Ϊ����֪��������ô����
int get_pid(float kp,float ki,float kd,float actual_value )
{
    float bias;
    static float bias_add;      //���Ļ�����        ������
    static float bias_last;     //��һ���жϵ����     ������
    double bias_d=0;                                //   ������
    int pwm_pid=0;      //����Ϊint�ͣ������ǿ��ת��Ϊint����
    bias=actual_value-25;  //���,ʵ��ֵcm-20cm
    bias_add+=bias;             //������
    bias_d=bias-bias_last;    //΢�����λΪ��ÿ��
    pwm_pid=kp*bias+ki*bias_add-kd*bias_d;
    bias_last=bias;     //������ƫ��ֵ����bias_last��̬����
    return pwm_pid;
        //6.���ֻ�û����
}



//PWM�޷���������������ֱ�Ϊ���޷����롢��С��ֵ������ֵ��min<pwm<max,����ֵΪ�޷����ֵ
int Limit_Pwm(int IN,int min,int max)
{
    int OUT=IN;
    if(OUT>max) OUT = max;
    if(OUT<min) OUT = min;
    return OUT;
}




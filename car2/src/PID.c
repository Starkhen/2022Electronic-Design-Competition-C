//计算PID，输入参数依次为kp，ki，kd，实际值，期望值=20cm
//为原电机加pwm_pid
//可以令pi=0，因为还不知道积分怎么清零
int get_pid(float kp,float ki,float kd,float actual_value )
{
    float bias;
    static float bias_add;      //误差的积分项        浮点型
    static float bias_last;     //上一次中断的误差     浮点型
    double bias_d=0;                                //   浮点型
    int pwm_pid=0;      //定义为int型，过会会强制转换为int返回
    bias=actual_value-25;  //误差,实际值cm-20cm
    bias_add+=bias;             //积分项
    bias_d=bias-bias_last;    //微分项，单位为度每秒
    pwm_pid=kp*bias+ki*bias_add-kd*bias_d;
    bias_last=bias;     //将本次偏差值赋给bias_last静态变量
    return pwm_pid;
        //6.积分还没清零
}



//PWM限幅函数，输入参数分别为待限幅输入、最小幅值、最大幅值，min<pwm<max,返回值为限幅后的值
int Limit_Pwm(int IN,int min,int max)
{
    int OUT=IN;
    if(OUT>max) OUT = max;
    if(OUT<min) OUT = min;
    return OUT;
}




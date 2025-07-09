#include "allheader.h"

float Gyro_turn;

// OLED调试输出时使用 Used for OLED debug output
char showbuf[20]={'\0'};
char showbuf2[20]={'\0'};

// Yaw 的误差修正 Error correction for Yaw
float yaw_fix = 0;

// 正前方 Front
float yaw_front ;
float go_front_dir;

//小车开始运动标志位
bool start_flag=0;//1为开始运动

float my_f_abs(float a){
	return a>0?a:-a;
}
int main()
{
    static bool ring = false;
    bsp_init();

    sprintf(showbuf,"Start");
  	OLED_Draw_Line(showbuf, 1, false, true);
    float last_yw = Yaw;
    while(GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)==1)
    {
        sprintf(showbuf,"yaw = %f",Yaw);
        bluetooth_send_string(showbuf);
  		OLED_Draw_Line(showbuf, 2, false, true);
        // When the difference between the Yaw values ??read by MPU6050 twice is less than 0.005, the initialization is considered successful
		// 当连续两次MPU6050读取的Yaw差值小于0.005时视为初始化成功
		if(my_f_abs(Yaw - last_yw) < 0.005 && ring==false){
			BEEP_BEEP = 1;
			ring = true;
			delay_time(10);
			BEEP_BEEP = 0;
		}
		last_yw = Yaw;
		delay_time(50);
        if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)==0)
        {
            yaw_front = Yaw;
            start_flag=1;
            sprintf(showbuf,"Moving");
  		    OLED_Draw_Line(showbuf, 3, false, true);
        }

    }
    // 将此时的Yaw标定为正前方
    // yaw_front = Yaw;
    yaw_fix=yaw_front-Yaw;
	go_front_dir = yaw_front;
    sprintf(showbuf,"yaw_front = %f",yaw_front);
    bluetooth_send_string(showbuf);
    delay_time(10);

    // if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)==0)
    // {
    //     start_flag=1;
    // }

    while(1)
    {
        // sprintf(showbuf,"yawfix = %f\n",yaw_fix);
        // bluetooth_send_string(showbuf);
    }
    return 0;

}

/**
 * @brief 直立环PD控制器
 * @param pitch 俯仰角（单位：度）
 * @param gyro 角速度（单位：度/秒）
 * @return PWM控制量（经过比例微分计算）
 */
int Balance_PD(float pitch,float gyro)
{
    float Kp=100;   // 比例系数
    float Kd=0.6;   // 微分系数
    //  sprintf(showbuf,"pitch = %f\n",pitch);
    //  bluetooth_send_string(showbuf);
    //  sprintf(showbuf,"gyro = %f\n",gyro);
    //  bluetooth_send_string(showbuf);

    return (int)(Kp*pitch+Kd*gyro); // PD控制公式：输出 = Kp*角度 + Kd*角速度
}

/**
 * @brief 速度环PI控制器
 * @param speed 当前速度值（编码器脉冲计数）
 * @param target 目标速度值
 * @return PWM控制量（经过比例积分计算）
 */
int Velocity_PI(int speed,int target)
{
    float Kp=80, Ki=0.35;  // 比例系数 / 积分系数
    static int I=0;         // 积分项累加值

    int error = speed - target;  // 速度偏差计算
    
    I += error;             // 积分项累加（注意防饱和）
    
    return (int)(Kp*error + Ki*I); // PI控制公式：输出 = Kp*误差 + Ki*积分
}

/**
 * @brief 转向环PI控制器
 * @param encoder_left 左电机编码器脉冲数
 * @param encoder_right 右电机编码器脉冲数
 * @param turn 转向目标值（左右轮速差）
 * @return PWM控制量（经过比例积分计算）
 */
// int Turn_PI(int encoder_left,int encoder_right,int turn)
// {
//     float Kp=85, Ki=0.35;  // 比例系数 / 积分系数
//     static int I=0;         // 积分项累加值（带防饱和）

//     const int MAX_I=7400;   // 积分上限
//     const int MIN_I=-7400;  // 积分下限

//     int error=encoder_left-encoder_right+turn; // 转向偏差计算（左右轮差+目标转向）
    
//     I+=error;               // 积分项累加
//     // 积分限幅防饱和处理
//     if(I>MAX_I)I=MAX_I;
//     if(I<MIN_I)I=MIN_I;

//     return (int)(Kp*error+Ki*I); // PI控制公式：输出 = Kp*误差 + Ki*积分
// }

/**************************************************************************
Function: Turn control
Input   : Z-axis angular velocity
Output  : Turn control PWM
函数功能：转向控制 
入口参数：Z轴陀螺仪
返回  值：转向控制PWM
**************************************************************************/
// int Turn_PD(float gyro,float yaw_bias,float yaw)
// {
// 	 static float Turn_Target,turn_PWM; 
// 	 float Kp=2500,Kd;			//修改转向速度，请修改Turn_Amplitude即可 To modify the steering speed, please modify Turn_Smplitude
// 	 Turn_Target=yaw; 
// 	 Kd=20; 
// 	float move_z=5;

//   //===================转向PD控制器 Turn to PD controller=================//
// 	 turn_PWM=Turn_Target*Kp/100+gyro*Kd/100 ; //结合Z轴陀螺仪进行PD控制   Combining Z-axis gyroscope for PD control
// 	//  bluetooth_send_string("Turn_PD Working");
// 	//  sprintf(showbuf,"yaw_bias = %f\n",yaw_bias);
//     //  bluetooth_send_string(showbuf);
//     //  sprintf(showbuf,"yaw = %f\n",Yaw);
//     //  bluetooth_send_string(showbuf);
//     //  sprintf(showbuf,"yawfront = %f\n",yaw_front);
//     //  bluetooth_send_string(showbuf);
//     //  sprintf(showbuf,"yawfix = %f\n",yaw_fix);
//     //  bluetooth_send_string(showbuf);
//     //  sprintf(showbuf,"gyro_z = %f\n",gyro);
//     //  bluetooth_send_string(showbuf);
//     //  sprintf(showbuf,"\n");
//     //  bluetooth_send_string(showbuf);
    
//     return (int) turn_PWM;								 				 //转向环PWM右转为正，左转为负 Steering ring PWM: Right turn is positive, left turn is negative
    
// }

/**
 * @brief 转向环PI控制器
 * @param encoder_left 左电机编码器脉冲数
 * @param encoder_right 右电机编码器脉冲数
 * @param turn 转向目标值（左右轮速差）
 * @return PWM控制量（经过比例积分计算）
 */
int Turn_PI(float gyro,float yaw_bias,int turn)
{
    float Kp=25, Ki=0.35;  // 比例系数 / 积分系数
    static int I=0;         // 积分项累加值（带防饱和）

    const int MAX_I=7400;   // 积分上限
    const int MIN_I=-7400;  // 积分下限

    int error=yaw_bias+turn; // 转向偏差计算（左右轮差+目标转向）
    
    I+=error;               // 积分项累加
    // 积分限幅防饱和处理
    if(I>MAX_I)I=MAX_I;
    if(I<MIN_I)I=MIN_I;

    return (int)(Kp*error+Ki*I); // PI控制公式：输出 = Kp*误差 + Ki*积分
}

void EXTI15_10_IRQHandler() {
    if(MPU6050_INT==0)		
    {   
        EXTI->PR=1<<12;
        // 新版本推荐使用 MPU6050_getDate(1) 
        // 旧版本使用 Read_DMP(); 
            float * data = MPU6050_getDate(1);
            float pitch = data[1];//俯仰角，由于有特殊运算gyro_orientation[9]，（绕物理x轴旋转角度，单位：度）
            float gyro = data[3];//由于有特殊运算gyro_orientation[9]，传感器X轴 → 实际物理Y轴（反向），传感器Y轴 → 实际物理X轴（反向），
                                //传感器Z轴 → 实际物理Z轴（保持原方向），
                                //data[3]（对应angles[3]）实际是物理Y轴的角速度
            Gyro_turn=data[5];
           

            yaw_fix=yaw_front-Yaw;
            int encoder_left = Read_Encoder(MOTOR_ID_ML);
            int encoder_right = Read_Encoder(MOTOR_ID_MR);
            if(start_flag==1)
        {
            //速度不为0
            // static int i=0;
            int velocity=15;//前进速度
            // i++;
            // if(i<500)
            // {
            //     velocity=15;
            // }else if(i>=500 && i<=700){

            //     velocity=0;
            // }else if(i>700&&i<1200)
            // {
            //     velocity=-15;
            // }
            // else
            // {
            //     velocity=0;
            // }
            // //速度不为0

            int motor_pwm_left = Balance_PD(pitch,gyro) + Velocity_PI(encoder_left+encoder_right,velocity) - Turn_PI(Gyro_turn,yaw_fix,0);
            int motor_pwm_right = Balance_PD(pitch,gyro) + Velocity_PI(encoder_left+encoder_right,velocity) + Turn_PI(Gyro_turn,yaw_fix,0);

            motor_pwm_left = PWM_Ignore(motor_pwm_left);
            motor_pwm_left=PWM_Limit(motor_pwm_left,2600,-2600);
            motor_pwm_right = PWM_Ignore(motor_pwm_right);
            motor_pwm_right=PWM_Limit(motor_pwm_right,2600,-2600);

            Set_Pwm(motor_pwm_left,motor_pwm_right);
            // sprintf(showbuf,"yaw = %f",Yaw);
            // sprintf(showbuf,"yaw = %f",Yaw);
            // bluetooth_send_string(showbuf);
  		    // OLED_Draw_Line(showbuf, 2, false, true);
        }

    }
    // sprintf(showbuf,"yaw = %f/n",Yaw);
    // bluetooth_send_string(showbuf);
}

#include "motor.h"

/**************************************************************************
Function: Initialize Motor Interface
Input   : none
Output  : none
�������ܣ���ʼ������ӿ�
��ڲ�������
����  ֵ����
**************************************************************************/
void Balance_Motor_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PC�˿�ʱ�� Enable PC port clock
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	//�˿����� port configuration
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //������� Push pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOC Initialize GPOC according to the set parameters
}



/**************************************************************************
Function: Initialize PWM to drive motor
Input   : arr��Auto reload value��psc��Prescaler coefficient
Output  : none
�������ܣ���ʼ��PWM������������� 
��ڲ�����arr���Զ���װֵ��psc��Ԥ��Ƶϵ��
����  ֵ����
**************************************************************************/
void Balance_PWM_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Period = arr - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 Set the value of the automatic reload register cycle for the next update event loading activity
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  Set the prescaler value used as the divisor of the TIMx clock frequency. No division
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim Set clock division: TDTS=Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ TIM Up Counting Mode
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ  Initialize the time base unit of TIMx based on the parameters specified in TIM_TimeBaseInitStruct

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  Select Timer Mode: TIM Pulse Width Modulation Mode 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��  Compare output enablement
	TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ  Set the pulse value to be loaded into the capture comparison register
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�  Output polarity: TIM output has a relatively high polarity
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  Initialize peripheral TIMx based on the parameters specified in TIM_SICInitStruct
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  Initialize peripheral TIMx based on the parameters specified in TIM_SICInitStruct
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  Initialize peripheral TIMx based on the parameters specified in TIM_SICInitStruct
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  Initialize peripheral TIMx based on the parameters specified in TIM_SICInitStruct

	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE �����ʹ��  Main output enable

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	  CH1 pre load enable
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��    CH2 pre load enable
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��	  CH3 pre load enable
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��    CH4 pre load enable
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���   Enable TIMx pre loaded registers on ARR
	
	
	/* TIM8 enable counter */
	TIM_Cmd(TIM8, ENABLE);                   //ʹ�ܶ�ʱ��8	Enable Timer 8

}


/**************************************************************************
Function: Assign to PWM register
Input   : motor_left��Left wheel PWM��motor_right��Right wheel PWM
Output  : none
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int motor_left,int motor_right)
{
  	// if(motor_left>0){
	// 	L_PWMB = abs(motor_left);
	// 	L_PWMA = 0;
	// }else{
	// 	L_PWMB = 0;
	// 	L_PWMA = abs(motor_left);
	// }

	// if(motor_right>0){
	// 	R_PWMA = abs(motor_right);
	// 	R_PWMB = 0;
	// }else {
	// 	R_PWMA = 0;
	// 	R_PWMB = abs(motor_right);	
	// }
		if(motor_left == 0)//ͣ��
		{
		L_PWMA = 0;
		L_PWMB = 0;
		}
		if(motor_right == 0)
		{
		R_PWMA = 0;
		R_PWMB = 0;
		}
		//����
		if(motor_left>0) //ǰ��
		{
		L_PWMB = abs(motor_left);
		L_PWMA = 0;
		}
		else
		{
		L_PWMB = 0;
		L_PWMA = abs(motor_left);
		}
		//����
		if(motor_right>0) //ǰ��
		{
		R_PWMA = abs(motor_right);
		R_PWMB = 0;
		}
		else //����
		{
		R_PWMA = 0;
		R_PWMB = abs(motor_right);
		}
		 TIM3->CNT = 0;
    TIM4->CNT = 0;
}



int PWM_Ignore(int pulse)
{
	if (pulse > 0) return pulse + MOTOR_IGNORE_PULSE;
  	if (pulse < 0) return pulse - MOTOR_IGNORE_PULSE;
	return pulse;
}

int PWM_Limit(int IN,int max,int min)
{
	int OUT = IN;
	if(OUT>max) OUT = max;
	if(OUT<min) OUT = min;
	return OUT;
}
#include "encoder.h"

/**************************************************************************
Function: Initialize TIM2 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM3��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // ʹ�ܶ�ʱ��3��ʱ�� Enable the clock of Timer 3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PA�˿�ʱ��  Enable PA port clock

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // �˿�����  port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // ��������  Floating input
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   // �����趨������ʼ��GPIOA  Init GPIOA

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					// Ԥ��Ƶ��  Prescaler
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;		// �趨�������Զ���װֵ Set the automatic reset value of the counter
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// ѡ��ʱ�ӷ�Ƶ������Ƶ Choose clock division: no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM���ϼ���    TIM up counting
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ʹ�ñ�����ģʽ3 Use encoder mode 3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10; // �˲�10 Filter 10
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); // ���TIM�ĸ��±�־λ Clear the update flag of TIM
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	// Reset counter
	TIM_SetCounter(TIM3, 0);
	TIM_Cmd(TIM3, ENABLE);
}

/**************************************************************************
Function: Initialize TIM4 to encoder interface mode
Input   : none
Output  : none
�������ܣ���TIM4��ʼ��Ϊ�������ӿ�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // ʹ�ܶ�ʱ��4��ʱ��  Enable the clock of Timer 4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��    Enable PB port clock

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // �˿�����   			port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // ��������   			Floating input
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   // �����趨������ʼ��GPIOB  Init GPIOB

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;					// Ԥ��Ƶ��  Prescaler
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;		// �趨�������Զ���װֵ Set the automatic reset value of the counter
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// ѡ��ʱ�ӷ�Ƶ������Ƶ Choose clock division: no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM���ϼ���   TIM up counting
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // ʹ�ñ�����ģʽ3 Use encoder mode 3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); // ���TIM�ĸ��±�־λ  Clear the update flag of TIM
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	// Reset counter
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);
}

/**************************************************************************
Function: Read encoder count per unit time
Input   : TIMX��Timer
Output  : none
�������ܣ���λʱ���ȡ����������
��ڲ�����TIMX����ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
int Read_Encoder(Motor_ID MYTIMX)
{
	int Encoder_TIM;
	switch (MYTIMX)
	{
	case MOTOR_ID_ML:
		Encoder_TIM = (short)TIM3->CNT;
		TIM3->CNT = 0;
		break;
	case MOTOR_ID_MR:
		Encoder_TIM = (-1)*(short)TIM4->CNT;
		TIM4->CNT = 0;
		break;
	default:
		Encoder_TIM = 0;
	}
	return Encoder_TIM;
}
/**************************************************************************
Function: TIM4 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{
	if (TIM4->SR & 0X0001) // ����ж� Overflow interrupt
	{
	}
	TIM4->SR &= ~(1 << 0); // ����жϱ�־λ 	Clear interrupt flag bit
}
/**************************************************************************
Function: TIM2 interrupt service function
Input   : none
Output  : none
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM3_IRQHandler(void)
{
	if (TIM3->SR & 0X0001) // ����ж� Overflow interrupt
	{
	}
	TIM3->SR &= ~(1 << 0); // ����жϱ�־λ 	   Clear interrupt flag bit
}

/**************************************************************************
Function: Convert encoder reading to speed (mm/s)
Input parameter: None
Return value: Velocity_Left, Velocity_Right; //Wheel speed (mm/s)
�������ܣ�����������ת��Ϊ�ٶȣ�mm/s��
��ڲ�������
����  ֵ��Velocity_Left,Velocity_Right;	//�����ٶ�(mm/s)
**************************************************************************/
// ����ǩ������Ϊ���� float ����
// Function signature changed to return float array
float* Get_Velocity_From_Encoder(int encoder_left, int encoder_right) {
    static float velocities[2];  // ���ڴ洢�����ٶ� For storing two speeds
    float Rotation_Speed_L, Rotation_Speed_R;

    Rotation_Speed_L = encoder_left * Control_Frequency / EncoderMultiples / Reduction_Ratio / Encoder_precision;
    velocities[0] = Rotation_Speed_L * PI * Diameter_67;  // Velocity_Left

    Rotation_Speed_R = encoder_right * Control_Frequency / EncoderMultiples / Reduction_Ratio / Encoder_precision;
    velocities[1] = Rotation_Speed_R * PI * Diameter_67;  // Velocity_Right

    return velocities;  // �����ٶ����� Returns the velocity array
}
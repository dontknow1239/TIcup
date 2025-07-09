#ifndef __ENCODER_H
#define __ENCODER_H

#include "AllHeader.h" 


#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�  It cannot be greater than 65535 because the F103 timer is 16 bits.

// Parameters needed to calculate vehicle speed
// ���㳵��ʱ��Ҫ�õ��Ĳ���
#define PI 3.14159265							//PIԲ����
#define Control_Frequency  200.0	//��������ȡƵ�� Encoder reading frequency
#define Diameter_67  67.0 				//����ֱ��67mm  Wheel diameter 67mm
#define EncoderMultiples   4.0 		//��������Ƶ�� Encoder frequency multiplication
#define Encoder_precision  11.0 	//���������� 11�� Encoder precision 11 lines
#define Reduction_Ratio  30.0			//���ٱ�30 Reduction ratio 30
#define Perimeter  210.4867 			//�ܳ�����λmm Perimeter, unit mm
typedef enum {
    MOTOR_ID_ML = 0,
    MOTOR_ID_MR,
    MAX_MOTOR
} Motor_ID;
int Read_Encoder(Motor_ID);
void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
void TIM4_IRQHandler(void);
void TIM3_IRQHandler(void);
float* Get_Velocity_From_Encoder(int encoder_left, int encoder_right);

#endif

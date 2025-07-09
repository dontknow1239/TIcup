#include "bsp_beep.h"

u32 beep_time = 0;

void Init_Beep(void)
{
	//��ʼ�������������� Initialize the buzzer pin
  GPIO_InitTypeDef GPIO_InitStructure;
	/*��������ʱ��  Enable peripheral clock */
	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE); 
	/*ѡ��Ҫ���Ƶ�����  Select the pin to control */															   
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;	
	/*��������ģʽΪͨ�ÿ�©��� Set the pin mode to general push-pull output */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*������������Ϊ50MHz Set the pin rate to 50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	/*���ÿ⺯������ʼ��BEEP_PORT Call library function to initialize BEEP_PORT */
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
	
	BEEP_BEEP = 0;


/*����ʱ��*/
	// RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);	//����GPIOB��ʱ��
	// 														//ʹ�ø�������ǰ���뿪��ʱ�ӣ����������Ĳ�����Ч
	
	// /*GPIO��ʼ��*/
	// GPIO_InitTypeDef GPIO_InitStructure;					//����ṹ�����
	
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIOģʽ����ֵΪ�������ģʽ
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//GPIO���ţ���ֵΪ��12������
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO�ٶȣ���ֵΪ50MHz
	
	// GPIO_Init(GPIOA, &GPIO_InitStructure);					//����ֵ��Ĺ���������ݸ�GPIO_Init����
	// 														//�����ڲ����Զ����ݽṹ��Ĳ���������Ӧ�Ĵ���
	// 														//ʵ��GPIOB�ĳ�ʼ��
	// GPIO_SetBits(GPIOA, GPIO_Pin_11);


// 	GPIO_InitTypeDef  GPIO_InitStructure;   //��ʼ��
	
//   RCC_APB2PeriphClockCmd(BEEP_RCC,ENABLE);
//   GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�Ϊ50M
//   GPIO_Init(BEEP_PORT, &GPIO_InitStructure);   //�˿ڳ�ʼ��
  
// 	GPIO_SetBits(BEEP_PORT,BEEP_PIN);   //�ߵ�ƽ
// 	BEEP_BEEP = 0;
}

//��������ʱ�� Buzzer on time
//beep_time ��1msΪ��λ  1ms as unit
void open_beep(u32 beep_time) //10ms��һ��  Subtract once every 10ms
{
	beep_time = beep_time/10;
}

// void Start_Beepping(void)//ʵ�ڲ��о��ó���ʹ��
// {
// 		GPIO_ResetBits(GPIOA, GPIO_Pin_11);		//��PB12��������Ϊ�͵�ƽ������������
// 		delay_ms(100);							//��ʱ100ms
// 		GPIO_SetBits(GPIOA, GPIO_Pin_11);		//��PB12��������Ϊ�ߵ�ƽ��������ֹͣ
// 		delay_ms(100);							//��ʱ100ms
// 		GPIO_ResetBits(GPIOA, GPIO_Pin_11);		//��PB12��������Ϊ�͵�ƽ������������
// 		delay_ms(100);							//��ʱ100ms
// 		GPIO_SetBits(GPIOA, GPIO_Pin_11);		//��PB12��������Ϊ�ߵ�ƽ��������ֹͣ
// 		delay_ms(700);							//��ʱ700ms

// }
// void Stop_Beepping(void)
// {
// 	GPIO_SetBits(GPIOA, GPIO_Pin_11);
// }
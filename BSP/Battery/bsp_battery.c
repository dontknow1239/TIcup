#include "bsp_battery.h"


//��ص�������ʼ�� //Initialization of battery level detection
void Battery_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BAT_GPIO_CLK | BAT_ADC_CLK, ENABLE); //ʹ�� BAT_ADC ͨ��ʱ�� //Enable BAT_SDC channel clock
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);							//���� ADC ��Ƶ���� 6  //Set ADC division factor to 6

	//72M/6=12, ADC �������ʱ�Ӳ��ܳ���14M    72M/6=12, ADC maximum input clock cannot exceed 14M
	//PA5 ��Ϊģ��ͨ����������   PA5 is used as analog channel input pin
	GPIO_InitStructure.GPIO_Pin = BAT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ģ������ Analog input
	GPIO_Init(BAT_GPIO_PORT, &GPIO_InitStructure); //��ʼ�� GPIOA.5  initialization GPIOA.5 

	ADC_DeInit(BAT_ADC);												//��λ BAT_ADC,������ BAT_ADC ��ȫ���Ĵ�������Ϊȱʡֵ Reset BAT_SDC and reset all registers of the peripheral BAT_SDC to default values
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC ����ģʽ  ADC independent mode
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//��ͨ��ģʽ  Single channel mode
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//����ת��ģʽ  Single conversion mode
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ�������� The conversion is initiated by software rather than external triggers
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC �����Ҷ���  Right aligned ADC data
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//˳����й���ת���� ADC ͨ������Ŀ  The number of ADC channels for sequential rule conversion
	ADC_Init(BAT_ADC, &ADC_InitStructure);								//����ָ���Ĳ�����ʼ������ ADCx  Initialize peripheral ADCx based on specified parameters
	ADC_Cmd(BAT_ADC, ENABLE);											//ʹ��ָ���� BAT_ADC   Enable specified BAT_daC
	ADC_ResetCalibration(BAT_ADC);										//������λУ׼   Enable reset calibration
	while (ADC_GetResetCalibrationStatus(BAT_ADC))
		;						   //�ȴ���λУ׼���� Waiting for reset calibration to end
	ADC_StartCalibration(BAT_ADC); //���� AD У׼  Enable AD calibration
	while (ADC_GetCalibrationStatus(BAT_ADC))
		; //�ȴ�У׼����  Waiting for calibration to end
	
}


// ��� ADC ֵ, ch:ͨ��ֵ
//Obtain ADC value, ch: channel value
static uint16_t Battery_Get(uint8_t ch)
{
	uint16_t timeout = 1000;
	//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
                // Set the rule group channels of the specified ADC, set their conversion order and sampling time
	ADC_RegularChannelConfig(BAT_ADC, ch, 1, ADC_SampleTime_239Cycles5);
	//ͨ�� 1,�������˳��ֵΪ 1,����ʱ��Ϊ 239.5 ����
                // Channel 1, regular sampling order value is 1, sampling time is 239.5 cycles
	ADC_SoftwareStartConvCmd(BAT_ADC, ENABLE); //ʹ�����ת������   Enable software conversion function
	while (!ADC_GetFlagStatus(BAT_ADC, ADC_FLAG_EOC) && timeout--)
		;									//�ȴ�ת������ Wait for the conversion to finish
	return ADC_GetConversionValue(BAT_ADC); //�������һ�� BAT_ADC �������ת����� Returns the most recent conversion result of the BAT_ADC rule group
}


// ��� ADC ��β���ƽ��ֵ, ch:ͨ��ֵ ; times:��������
//Obtain the average value of multiple ADC measurements, ch: channel value; Times: measurement frequency
uint16_t Battery_Get_Average(uint8_t ch, uint8_t times)
{
	uint16_t temp_val = 0;
	uint8_t t;
	for (t = 0; t < times; t++)
	{
		temp_val += Battery_Get(ch);
	}
	if (times == 4)
	{
		temp_val = temp_val >> 2;
	}
	else
	{
		temp_val = temp_val / times;
	}
	return temp_val;
}


// ��ò��ԭʼ��ѹֵ
//Obtain the measured original voltage value
float Get_Measure_Volotage(void)
{
	uint16_t adcx;
	float temp;
	adcx = Battery_Get(BAT_ADC_CH); //���ͨ��5  Battery Channel 5
	temp = (float)adcx * (3.30f / 4096);
	return temp;
}


// ���ʵ�ʵ�ط�ѹǰ��ѹ
//Obtain the actual voltage of the battery before voltage division
float Get_Battery_Volotage(void)
{
	float temp;
	temp = Get_Measure_Volotage();
	// ʵ�ʲ�����ֵ�ȼ���ó���ֵ��һ��㡣
	//The actual measured value is slightly lower than the calculated value.
	temp = temp * 4.03f;    //temp*(10+3.3)/3.3; 
	return temp;
}

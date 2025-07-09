#include "bsp_beep.h"

u32 beep_time = 0;

void Init_Beep(void)
{
	//初始化蜂鸣器的引脚 Initialize the buzzer pin
  GPIO_InitTypeDef GPIO_InitStructure;
	/*开启外设时钟  Enable peripheral clock */
	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE); 
	/*选择要控制的引脚  Select the pin to control */															   
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;	
	/*设置引脚模式为通用开漏输出 Set the pin mode to general push-pull output */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	/*设置引脚速率为50MHz Set the pin rate to 50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	/*调用库函数，初始化BEEP_PORT Call library function to initialize BEEP_PORT */
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
	
	BEEP_BEEP = 0;


/*开启时钟*/
	// RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);	//开启GPIOB的时钟
	// 														//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	// /*GPIO初始化*/
	// GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				//GPIO引脚，赋值为第12号引脚
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	// GPIO_Init(GPIOA, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
	// 														//函数内部会自动根据结构体的参数配置相应寄存器
	// 														//实现GPIOB的初始化
	// GPIO_SetBits(GPIOA, GPIO_Pin_11);


// 	GPIO_InitTypeDef  GPIO_InitStructure;   //初始化
	
//   RCC_APB2PeriphClockCmd(BEEP_RCC,ENABLE);
//   GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度为50M
//   GPIO_Init(BEEP_PORT, &GPIO_InitStructure);   //端口初始化
  
// 	GPIO_SetBits(BEEP_PORT,BEEP_PIN);   //高电平
// 	BEEP_BEEP = 0;
}

//蜂鸣器打开时长 Buzzer on time
//beep_time ：1ms为单位  1ms as unit
void open_beep(u32 beep_time) //10ms减一次  Subtract once every 10ms
{
	beep_time = beep_time/10;
}

// void Start_Beepping(void)//实在不行就拿出来使用
// {
// 		GPIO_ResetBits(GPIOA, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
// 		delay_ms(100);							//延时100ms
// 		GPIO_SetBits(GPIOA, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
// 		delay_ms(100);							//延时100ms
// 		GPIO_ResetBits(GPIOA, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
// 		delay_ms(100);							//延时100ms
// 		GPIO_SetBits(GPIOA, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
// 		delay_ms(700);							//延时700ms

// }
// void Stop_Beepping(void)
// {
// 	GPIO_SetBits(GPIOA, GPIO_Pin_11);
// }
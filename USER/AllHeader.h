/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // ALLHeader.h
* @author       // lly
* @version      // V1.0
* @date         // 240628
* @brief        // ������е�ͷ�ļ� All related header files
* @details      
* @par History  //
*               
*/


#ifndef __ALLHEADER_H
#define __ALLHEADER_H


//ͷ�ļ� Header Files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "myenum.h"

#include "delay.h"
#include "bsp.h"
#include "bsp_battery.h"
#include "bsp_beep.h"
#include "bsp_LED.h"
#include "bsp_timer.h"
#include "bsp_key.h"

//����
#include "bsp_bluetooth.h"

//Usart
#include "usart.h"	

//OLED
#include "bsp_oled_i2c.h"
#include "bsp_oled.h"

//��ʱ
#include "delay.h"


//Mpu6050
#include "MPU6050.h"

//����
#include "bsp_key.h"

//LED
#include "bsp_LED.h"

//Motor
#include "motor.h"
#include "encoder.h"
// #include "app_motor.h"


//4·ѭ�� 4-way tracking
#include "bsp_irtracking.h"
// #include "app_tracking.h"


//ƽ�⳵������� Balance car overall control
// #include "app_control.h"
// #include "pid_control.h"



#endif



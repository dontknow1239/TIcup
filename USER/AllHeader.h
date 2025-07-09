/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // ALLHeader.h
* @author       // lly
* @version      // V1.0
* @date         // 240628
* @brief        // 相关所有的头文件 All related header files
* @details      
* @par History  //
*               
*/


#ifndef __ALLHEADER_H
#define __ALLHEADER_H


//头文件 Header Files
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

//蓝牙
#include "bsp_bluetooth.h"

//Usart
#include "usart.h"	

//OLED
#include "bsp_oled_i2c.h"
#include "bsp_oled.h"

//延时
#include "delay.h"


//Mpu6050
#include "MPU6050.h"

//按键
#include "bsp_key.h"

//LED
#include "bsp_LED.h"

//Motor
#include "motor.h"
#include "encoder.h"
// #include "app_motor.h"


//4路循迹 4-way tracking
#include "bsp_irtracking.h"
// #include "app_tracking.h"


//平衡车整体控制 Balance car overall control
// #include "app_control.h"
// #include "pid_control.h"



#endif



/*
  ******************************************************************************
  * @file           : MPU6050.h
  * @brief          : MPU6050 External IMU on WALLE Header File
  * @author			: Arath Villanueva (abvillan@calpoly.edu)
  * 				  Devon Bolt (dwbolt@calpoly.edu)
  * @date			: 08, May 2025
  * @version		: Version 1.0
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "main.h"

/*Self Testing Registers*/
#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define WHO_AM_I 0x75

/*MPU6050 Configuration Registers*/
#define MPU_CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

/*Gyroscope Registers*/

/*Accelerometer Registers*/

#endif /* INC_MPU6050_H_ */

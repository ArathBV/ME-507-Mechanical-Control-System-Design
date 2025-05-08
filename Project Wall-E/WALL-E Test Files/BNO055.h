/*
  ******************************************************************************
  * @file           : BNO055.h
  * @brief          : BNO055 IMU Package Header File
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

#ifndef INC_BNO055_H_
#define INC_BNO055_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "main.h"

/* BNO MODE and CALIB ADDR */
#define BNO_ADDR 0x28
#define BNO_CONFIG_MODE 0x00
#define BNO_NDOF_MODE 0x0C
#define BNO_OPR_MODE 0x3D
#define BNO_PWR_ADDR 0x3E
#define BNO_CALIB_ADDR 0x35
#define BNO_UNITSEL_ADDR 0x80
#define BNO_CALIB_COEF_ADDR 0x55

/*GYRO DATA REG and ADDR */
#define GYR_ADDR_0 0x0A
#define GYR_ADDR_1 0x0B
#define GYR_X_LSB 0x14
#define GYR_X_MSB 0x15
#define GYR_Y_LSB 0x16
#define GYR_Y_MSB 0x17
#define GYR_Z_LSB 0x18
#define GYR_Z_MSB 0x19

/*Accelerometer DATA REG Address*/
#define ACCL_ADDR_Config 0x08
#define ACCL_X_LSB 0x08
#define ACCL_X_MSB 0x09
#define ACCL_Y_LSB 0x0A
#define ACCL_Y_MSB 0x0B
#define ACCL_Z_LSB 0x0C
#define ACCL_Z_MSB 0x0D

/* Euler Data REG Addresses*/
#define EUL_X_LSB 0x1A
#define EUL_X_MSB 0x1B
#define EUL_Y_LSB 0x1C
#define EUL_Y_MSB 0x1D
#define EUL_Z_LSB 0x1E
#define EUL_Z_MSB 0x1F

class BNO055{
	private:
		uint32_t imuAddr;
		uint32_t eulX;
		uint32_t eulY;
		uint32_t eulZ;

	public:
		BNO055(void);
		void initIMU(void);
		void imuConfig(void);
		void gyroConfig(void);
		void accelConfig(void);
		void fusionConfig(void);
		void getCalibStatus(void);
		uint32_t *getEulers(void);

};


#endif /* INC_BNO055_H_ */

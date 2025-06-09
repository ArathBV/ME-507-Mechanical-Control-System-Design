/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bno055.h
  * @brief          : Header file containing the class to the BNO055 IMU
  * @author
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

#include "stm32f4xx_hal.h"
#include <cstdint>
#include <iostream>
#include <stdbool.h>


/*
 * @brief BNO055 class for the IMU containing modes of operation, initialization, and reading
 * data
 */
class BNO055{
	public:
		enum class REG: uint8_t{
			CONFIG_MODE = 0x00,
			IMU = 0x08,
			NDOF = 0x0C
		};

		BNO055(I2C_HandleTypeDef *hi2c, uint8_t addr = 0x28);

		bool init_imu(REG mode = REG::NDOF);
		bool updateEuler();
		int16_t getYaw();
		int16_t getRoll();
		int16_t getPitch();

		int16_t pitch;
		int16_t  yaw;
		int16_t roll;


	private:
		I2C_HandleTypeDef* hi2c;
		uint8_t addr;

		bool writeByte(uint8_t reg, uint8_t value);
		bool readLen(uint8_t reg, uint8_t* buffer, uint8_t len);
};


#endif /* INC_BNO055_H_ */

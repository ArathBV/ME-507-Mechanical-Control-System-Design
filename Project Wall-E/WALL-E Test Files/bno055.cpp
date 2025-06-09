/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bno055.h
  * @brief          : File containing the functions to the BNO055 IMU class
  * @author Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
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

#include "bno055.h"

#define OPR_MODE_ADDR     0x3D
#define EULER_H_LSB       0x1A
#define UNIT_SEL_ADDR     0x3B
#define SYS_TRIGGER_ADDR  0x3F
#define PWR_MODE_ADDR     0x3E
#define PAGE_ID_ADDR      0x07


/*
 * @brief Constructor Function to initialize the BNO055 Class
 */
BNO055::BNO055(I2C_HandleTypeDef* hi2c, uint8_t addr)
    : hi2c(hi2c), addr(addr << 1){}


/*
 * @brief Function handles the configuration and initializattion of the BNO055 IMU
 * @return Boolean
 */
bool BNO055::init_imu(REG mode) {
    HAL_Delay(650);
    writeByte(OPR_MODE_ADDR, static_cast<uint8_t>(REG::CONFIG_MODE));
    HAL_Delay(20);

    writeByte(SYS_TRIGGER_ADDR, 0x00);
    writeByte(PWR_MODE_ADDR, 0x00);
    HAL_Delay(10);

    writeByte(PAGE_ID_ADDR, 0);
    writeByte(UNIT_SEL_ADDR, 0x00);

    writeByte(OPR_MODE_ADDR, static_cast<uint8_t>(mode));
    HAL_Delay(20);
    return true;
}

/*
 * @brief Function Updates the Euler values based on the IMU's current readings. Roll
 * Pitch, and Yaw are updated within the class.
 * @return Boolean
 */
bool BNO055::updateEuler() {
    uint8_t buffer[6];
    if (!readLen(EULER_H_LSB, buffer, 6))
    	return false;

    int16_t rawYaw   = (int16_t)((buffer[1] << 8) | buffer[0]);
    int16_t rawRoll  = (int16_t)((buffer[3] << 8) | buffer[2]);
    int16_t rawPitch = (int16_t)((buffer[5] << 8) | buffer[4]);

    yaw   = rawYaw / 16.0f;
    roll  = rawRoll / 16.0f;
    pitch = rawPitch / 16.0f;
    return true;
}

/*
 * @brief Function allows for the user to get the current yaw value
 * @return int16_t
 */
int16_t BNO055::getYaw(){
	return yaw;
}

/*
 * @brief Function allows for the user to get the current roll value
 * @return int16_t
 */
int16_t BNO055::getRoll(){
	return roll;
}

/*
 * @brief Function allows for the user to get the current pitch value
 * @return int16_t
 */
int16_t BNO055::getPitch(){
	return pitch;
}

/*
 * @brief Function writes values to the specified register given by the user.
 * @return Boolean
 */
bool BNO055::writeByte(uint8_t reg, uint8_t value) {
    return HAL_I2C_Mem_Write(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY) == HAL_OK;
}

/*
 * @brief Function reads the current value of the specified register given by the user.
 * @return Boolean
 */
bool BNO055::readLen(uint8_t reg, uint8_t* buffer, uint8_t len) {
    return HAL_I2C_Mem_Read(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT, buffer, len, HAL_MAX_DELAY) == HAL_OK;
}

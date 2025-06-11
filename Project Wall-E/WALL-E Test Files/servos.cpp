/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : servos.cpp
  * @brief          : File containing the functions to the servo
  * @author			: Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
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
#include "servos.h"


/*
 * @brief Constructor Function for Servo Motor Class
 */
Servo::Servo(TIM_HandleTypeDef* htim, uint32_t channel)
    : htim(htim), channel(channel) {}

/*
 * @brief Function starts the PWM Channel for the Servo Movement
 * @return None
 */
void Servo::attach() {
    HAL_TIM_PWM_Start(htim, channel);
}

/*
 * @brief Function stops the PWM Signal received from the PWM
 * @return None
 */
void Servo::detach() {
    HAL_TIM_PWM_Stop(htim, channel);
}

/*
 * @brief Function sets the Servo's motor pulse width to determin the angle at which
 * the servo moves to or holds
 * @return None
 */
void Servo::setPulseWidth(uint16_t pulse_us) {
    if (pulse_us < 1000) pulse_us = 1000;
    //if (pulse_us > 2500) pulse_us = 2500;

    __HAL_TIM_SET_COMPARE(htim, channel, pulse_us);  // Each tick = 1 µs
}

/*
 * @brief Function set's the Servo motor's pulse width based on the desired angle from the servo.
 * @return None
 */
void Servo::setAngle(uint8_t angleDeg) {
	// Clamp angle to [0,180]
	if (angleDeg > 200) angleDeg = 200;

	// Map angle to pulse width in microseconds
	uint16_t pulse = 500 + ((uint16_t)angleDeg * 2000) / 180;  // 500–2500 µs

    setPulseWidth(pulse);
}

/*
 * @brief Function calculates the angle requested to the PWM pulse that is needed to create the angle.
 * @return uint16_t
 */
uint16_t Servo::angleToPulse(uint8_t angleDeg) {
    // Linear map: 0° → 1000 µs, 180° → 2000 µs
    return 1000 + ((angleDeg * 1000) / 180);  // No floats used
}

/*
 * @brief Function sets Servo to start to stop angle incrementing till requested angle
 * @return None
 */
void Servo::startStopAngle(uint8_t angle1, uint8_t angle2){
	uint8_t start = angle1;
	while(start != angle2){
		setAngle(start);
		start += 10;
		if (start > angle2)
			start = angle2;
		HAL_Delay(50);
	}
	while(start != angle1){
		setAngle(start);
		start -= 5;
		if (start < angle1)
			start = angle2;
		HAL_Delay(50);
	}
}

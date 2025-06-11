/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : servos.h
  * @brief          : File containing the class to the servo Motors class that control hand and arm movements
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
#ifndef SERVOS_H
#define SERVOS_H

#include "stm32f4xx_hal.h"

class Servo {
	public:
		Servo(TIM_HandleTypeDef* htim, uint32_t channel);

		void attach();                          // Start PWM
		void detach();                          // Stop PWM
		void setPulseWidth(uint16_t pulse_us);  // Set pulse in microseconds (e.g., 1000–2000)
		void setAngle(uint8_t angleDeg);        // Optional: 0–180 degrees
		void startStopAngle(uint8_t angle1, uint8_t angle2);

	private:
		TIM_HandleTypeDef* htim;
		uint32_t channel;

		uint16_t angleToPulse(uint8_t angleDeg); // Internal map: 0–180 → 1000–2000 µs
	};

#endif


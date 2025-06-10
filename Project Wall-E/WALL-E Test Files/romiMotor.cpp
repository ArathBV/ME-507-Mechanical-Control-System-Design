/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : romiMotor.cpp
  * @brief          : File containing the functions to the ROMI Motors class
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

#include "romiMotor.h"

RomiMotor::RomiMotor(TIM_HandleTypeDef* htim, uint32_t pwmCh,
		GPIO_TypeDef* pwmPort, uint16_t pwmPin,
		GPIO_TypeDef* dirPort, uint16_t dirPin,
		GPIO_TypeDef* enPort, uint16_t enPin)
		:htim(htim), pwmChannel(pwmCh), pwmPort(pwmPort), pwmPin(pwmPin),
		 dirPort(dirPort), dirPin(dirPin), enPort(enPort), enPin(enPin){}

/*
 * @brief Function Enables the motor to operate based on the PWM
 * @return None
 */
void RomiMotor::enable(){
	HAL_GPIO_WritePin(enPort, enPin, GPIO_PIN_SET);
}

/*
 * @brief Function disables the motor to no longer respond to pwm signals
 * @return None
 */
void RomiMotor::disable(){
	HAL_GPIO_WritePin(enPort, enPin, GPIO_PIN_RESET);
}

/*
 * @brief Function Sets the Duty Cycle of the PWM Signal and changes direction based
 * on the duty value
 */
void RomiMotor::setDuty(int duty){
	if (duty > 100) duty = 100;
	if (duty < -100) duty = -100;

	// Set Polarity of PWM Signal
	if (duty < 0){
		HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_SET);
		duty = -duty;
	}
	else{
		HAL_GPIO_WritePin(dirPort, dirPin, GPIO_PIN_RESET);
	}

	// Setting Duty Cycle
	uint32_t pulse = (__HAL_TIM_GET_AUTORELOAD(htim) + 1) * duty / 100;
	    __HAL_TIM_SET_COMPARE(htim, pwmChannel, pulse);

}



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
#include "main.h"
#include <cmath>
//
//#define OV2640_I2C_ADDR 0x60  // 0x30 << 1


/*
 * @brief Construction for the ROMI Motor Class
 */
RomiMotor::RomiMotor(GPIO_TypeDef* enPort, uint16_t enPin,
		GPIO_TypeDef* phPort, uint16_t phPin,
		GPIO_TypeDef* slPort, uint16_t slPin): en_Port(enPort), en_Pin(enPin),
		ph_Port(phPort), ph_Pin(phPin), sl_Port(slPort), sl_Pin(slPin), duty_Cycle(0),
		pwm_Counter(0){}

/*
 * @brief Function Enables the motor to operate based on the PWM
 * @return None
 */
void RomiMotor::enable(){
	HAL_GPIO_WritePin(sl_Port, sl_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(en_Port, en_Pin, GPIO_PIN_SET);
}

/*
 * @brief Function disables the motor to no longer respond to pwm signals
 * @return None
 */
void RomiMotor::disable(){
	HAL_GPIO_WritePin(sl_Port, sl_Pin, GPIO_PIN_RESET);

}

/*
 * @brief Function Sets the Direction of the PWM Signal and changes direction based
 * on the duty value
 */
void RomiMotor::setSpeed(int8_t speed){
	if (speed > 100) speed = 100;
	if (speed < -100) speed = -100;

	duty_Cycle = abs(speed);
    HAL_GPIO_WritePin(ph_Port, ph_Pin, (speed <= 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

}

/*
 * @brief Function uses and internal timer to trigger PWM signals via this function through the use
 * of the PWM/Duty Cycle Given
 * @return None
 */
void RomiMotor::updatePWM(){
	pwm_Counter = (pwm_Counter + 1) % 100;
	if (duty_Cycle == 0){
		HAL_GPIO_WritePin(en_Port, en_Pin, GPIO_PIN_RESET);
	}

	else if (pwm_Counter < duty_Cycle){
		HAL_GPIO_WritePin(en_Port, en_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(en_Port, en_Pin, GPIO_PIN_RESET);
	}
}

int8_t RomiMotor::getDuty(){
	return duty_Cycle;
}



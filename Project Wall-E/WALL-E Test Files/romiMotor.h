/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : romiMotor.h
  * @brief          : File containing the class to the ROMI Motors class
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


#ifndef INC_ROMIMOTOR_H_
#define INC_ROMIMOTOR_H_

#include "stm32f4xx_hal.h"

class RomiMotor{
public:
	RomiMotor(TIM_HandleTypeDef *htim, uint32_t pwm_ch,
			GPIO_TypeDef* pwm_port, uint16_t pwm_pin,
			GPIO_TypeDef *dir_port, uint16_t dir_pin,
			GPIO_TypeDef*en_port, uint16_t en_pin);

	void setDuty(int Duty);
	void enable();
	void disable();

private:
	TIM_HandleTypeDef* htim;
	uint32_t pwmChannel;
	GPIO_TypeDef* pwmPort;
	uint16_t pwmPin;
	GPIO_TypeDef* dirPort;
	uint16_t dirPin;
	GPIO_TypeDef* enPort;
	uint16_t enPin;
};

#endif /* INC_ROMIMOTOR_C_ */

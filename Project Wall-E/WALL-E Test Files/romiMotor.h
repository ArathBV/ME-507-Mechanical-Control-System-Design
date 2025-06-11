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
		RomiMotor(GPIO_TypeDef* enPort, uint16_t enPin,
				GPIO_TypeDef* phPort, uint16_t phPin,
				GPIO_TypeDef* slPort, uint16_t slPin);

		void setSpeed(int8_t);
		void updatePWM();
		void enable();
		void disable();
		int8_t getDuty();

	private:
		GPIO_TypeDef* en_Port;
		uint16_t en_Pin;
		GPIO_TypeDef* ph_Port;
		uint16_t ph_Pin;
		GPIO_TypeDef* sl_Port;
		uint16_t sl_Pin;
		int8_t duty_Cycle;
		uint8_t pwm_Counter;
};

#endif /* INC_ROMIMOTOR_C_ */

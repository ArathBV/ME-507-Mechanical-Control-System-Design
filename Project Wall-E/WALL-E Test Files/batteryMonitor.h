/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : batteryMonitor.h
  * @brief          : File containing the class to a Battery Monitor via the ADC
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

#ifndef INC_BATTERYMONITOR_H_
#define INC_BATTERYMONITOR_H_

#include "stm32f4xx_hal.h"

class BatteryMonitor {
	public:
		BatteryMonitor(ADC_HandleTypeDef* hadc, uint16_t threshold_mV = 7000);
		uint16_t getVoltage_mV();
		bool isLow();

	private:
		ADC_HandleTypeDef* hadc;
		uint16_t threshold_mV;
		uint16_t readVoltageRaw_mV();
};



#endif /* INC_BATTERYMONITOR_H_ */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : batteryMonitor.h
  * @brief          : File containing the functions to the Battery Monitor class that
  * utilizes the ADC on the STM32 chip
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


#include "batteryMonitor.h"

/*
 * @brief Constructor Function for the Battery Monitor Class
 */
BatteryMonitor::BatteryMonitor(ADC_HandleTypeDef* hadc, uint16_t threshold_mV)
    : hadc(hadc), threshold_mV(threshold_mV) {}

/*
 * @brief Function calculates the voltage in mV by reading the ADC and applying
 * the conversion to step up to the appropriate input voltage.
 * @return uint16_t
 */
uint16_t BatteryMonitor::readVoltageRaw_mV() {
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    uint16_t adc_raw = HAL_ADC_GetValue(hadc);
    HAL_ADC_Stop(hadc);

    uint32_t adc_mV = (adc_raw * 3300UL) / 4095;
    uint32_t battery_mV = adc_mV * 11;
    return (uint16_t)battery_mV;
}

/*
 * @brief Function allows for the user to retrieve the voltage of the battery
 * @return uint16_t
 */
uint16_t BatteryMonitor::getVoltage_mV() {
    return readVoltageRaw_mV();
}

/*
 * @brief Function indicates and raises the flag if the voltage is below the threshold
 * provided to the class indicating to charge the LiPo Battery.
 * @return Boolean
 */
bool BatteryMonitor::isLow() {
    return getVoltage_mV() < threshold_mV;
}




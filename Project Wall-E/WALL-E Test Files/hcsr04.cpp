/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : hcsr04.cpp
  * @brief          : File containing the functions to the hcsr04 UltraSonic Sensor
  *  class
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

#include "hcsr04.h"

/*
 * @brief Constructor Function that initializes the class variables/instances
 */
HCSR04::HCSR04(GPIO_TypeDef* trigPort, uint16_t trigPin,
               GPIO_TypeDef* echoPort, uint16_t echoPin,
               TIM_HandleTypeDef* htim)
    : trigPort(trigPort), trigPin(trigPin),
      echoPort(echoPort), echoPin(echoPin),
      htim(htim), startTick(0), endTick(0), measurementReady(false), echowait(false){}

/*
 * @brief Function Triggers the trigger pin to send out a 10us pulse for the echo pin to read
 * @return None
 */
void HCSR04::trigger() {
    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_SET);
    HAL_Delay(0.01); // 10 us pulse
    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
    measurementReady = false;
    echowait = true;
}

/*
 * @brief Function Handles reading the echo pin signal if received any signal at all.
 * @return None
 */
void HCSR04::update() {
	if (!echowait) return;

	    uint32_t timeoutTicks = HAL_GetTick() + 30; // 30ms timeout
	    while (HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_RESET) {
	        if (HAL_GetTick() > timeoutTicks) {
	            echowait = false;
	            measurementReady = true;
	            endTick = startTick = 0;
	            return;
	        }
	    }

	    __HAL_TIM_SET_COUNTER(htim, 0);
	    startTick = __HAL_TIM_GET_COUNTER(htim);

	    timeoutTicks = HAL_GetTick() + 30;
	    while (HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_SET) {
	        if (HAL_GetTick() > timeoutTicks) {
	            echowait = false;
	            measurementReady = true;
	            endTick = startTick = 0;
	            return;
	        }
	    }

	    endTick  = __HAL_TIM_GET_COUNTER(htim);
	    measurementReady = true;
	    echowait = false;
	}

/*
 * @brief Function returns the set variable if the device is ready to measure
 * @return Boolean
 */
bool HCSR04::isMeasurementReady(){
    return measurementReady;
}

/*
 * @brief Function calculates the distance of an object in cm based on the
 * tick count of the echo pin.
 * @return Float
 */
float HCSR04::getDistance() {
	// Measurement Ready Flag Check
    if (!measurementReady) return -1.0f;
    measurementReady = false;

    // Ticks Check if Echo Receives
    if (startTick == 0 && endTick == 0) return -1.0f;

    // Ready For Calculation
    uint32_t pulseDuration = endTick - startTick;
    float distance = (pulseDuration * 0.0343f) / 2.0f;
    return distance;
}

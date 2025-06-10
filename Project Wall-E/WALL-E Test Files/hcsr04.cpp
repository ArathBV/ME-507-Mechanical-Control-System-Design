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
#include "hcsr04.h"

HCSR04::HCSR04(GPIO_TypeDef* trigPort, uint16_t trigPin,
               GPIO_TypeDef* echoPort, uint16_t echoPin,
               TIM_HandleTypeDef* htim)
    : trigPort(trigPort), trigPin(trigPin),
      echoPort(echoPort), echoPin(echoPin),
      htim(htim), distanceCm(0)
{
    HAL_TIM_Base_Start(htim); // Ensure timer is running
}

/*
 * @brief Function Triggers the 10us Pulse on the trigger pin to be read from
 * the echo pin
 * @return None
 */
void HCSR04::trigger() {
    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
    HAL_Delay(1);  // Ensure clean low

    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(htim, 0);
    while (__HAL_TIM_GET_COUNTER(htim) < 10); // 10 us pulse
    HAL_GPIO_WritePin(trigPort, trigPin, GPIO_PIN_RESET);
}

/*
 * @brief Function if the sensor is ready to measure the function triggers then calculates the
 * distance an object is away from the sensor and updates it's variable
 * @return Boolean
 */
bool HCSR04::measure() {
    trigger();

    uint32_t timeoutTick = HAL_GetTick();
    while (HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_RESET) {
        if (HAL_GetTick() - timeoutTick > 50) return false;  // timeout (no echo start)
    }
    uint32_t start = __HAL_TIM_GET_COUNTER(htim);

    timeoutTick = HAL_GetTick();
    while (HAL_GPIO_ReadPin(echoPort, echoPin) == GPIO_PIN_SET) {
        if (HAL_GetTick() - timeoutTick > 50) return false;  // timeout (no echo end)
    }
    uint32_t end = __HAL_TIM_GET_COUNTER(htim);

    uint32_t pulse_us = (end >= start) ? (end - start)
                                       : ((htim->Instance->ARR - start) + end);

    // Speed of sound = 343 m/s = 0.0343 cm/us
    // Distance (cm) = pulse_us / 58 (since: 1 / 0.0343 / 2 ≈ 58)
    distanceCm = pulse_us / 58;

    return true;
}

/*
 * @brief Function allows the user to extract the Distance in cm the object is.
 * @return uint32_t
 */
uint32_t HCSR04::getDistanceCm() {
    return distanceCm;
}


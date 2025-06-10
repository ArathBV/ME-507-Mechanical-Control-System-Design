/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : HCSR04.h
  * @brief          : File containing the class to the HCSR04 Ultrasonic Sensor
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

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include "stm32f4xx_hal.h"

class HCSR04 {
public:
    HCSR04(GPIO_TypeDef* trigPort, uint16_t trigPin,
           GPIO_TypeDef* echoPort, uint16_t echoPin,
           TIM_HandleTypeDef* htim);

    void trigger();
    bool isMeasurementReady();
    float getDistance();
    void update();

private:
    GPIO_TypeDef* trigPort;
    uint16_t trigPin;
    GPIO_TypeDef* echoPort;
    uint16_t echoPin;
    TIM_HandleTypeDef* htim;

    uint32_t startTick;
    uint32_t endTick;
    bool measurementReady;
    bool echowait;
};

#endif /* INC_HCS04_H_ */

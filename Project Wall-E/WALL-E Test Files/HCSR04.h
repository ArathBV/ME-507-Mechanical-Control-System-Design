/*
  ******************************************************************************
  * @file           : HCSR04.h
  * @brief          : Ultrasonic Sensor Header File
  * @author			: Arath Villanueva (abvillan@calpoly.edu)
  * 				  Devon Bolt (dwbolt@calpoly.edu)
  * @date			: 01, May 2025
  * @version		: Version 1.0
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

typedef struct distanceSensor{
	TIM_HandleTypeDef * timer;
	uint32_t echo;
	uint32_t trig;
	uint32_t distance;
}distanceSensor;

void initUltraSonic(distanceSensor*, TIM_HandleTypeDef *, uint32_t, uint32_t);
void enableUltraSonic(distanceSensor*);
void updateDistance(distanceSensor*);
void disableUltraSonic(distanceSensor*);


#endif /* INC_HCSR04_H_ */

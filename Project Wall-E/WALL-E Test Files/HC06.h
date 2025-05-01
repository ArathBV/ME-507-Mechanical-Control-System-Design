/*
  ******************************************************************************
  * @file           : HC06.h
  * @brief          : Bluetooth Serial Device Header File
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

#ifndef INC_HC06_H_
#define INC_HC06_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

void initHC06(UART_HandleTypeDef *);
void sendMessage(UART_HandleTypeDef*, uint8_t *, int);
void recvMessage(UART_HandleTypeDef*, uint8_t *, int);


#endif /* INC_HC06_H_ */

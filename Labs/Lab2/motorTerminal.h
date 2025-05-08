/**
  ******************************************************************************
  * @file           : motorTerminal.h
  * @brief          : Header file containing functiosn for the motor terminal.
  * @author			: Arath Villanueva (abvillan@calpoly.edu)
  * 				Devon Bolt (dwbolt@calpoly.edu)
  * @date			: 23, April 2025
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

#ifndef INC_MOTORTERMINAL_H_
#define INC_MOTORTERMINAL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

#define MAX_BUFF 1024
#define MAX_USER 7
#define MOTORS {1, 2}
#define USER_INPUT ">:"
#define REQ_SIZE 4

void initTerminal(UART_HandleTypeDef*);
void userRequest(UART_HandleTypeDef*, uint8_t*);
int8_t parseRequest(UART_HandleTypeDef*, uint8_t*);



#endif /* INC_MOTORTERMINAL_H_ */

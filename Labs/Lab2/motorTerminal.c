/**
  ******************************************************************************
  * @file           : motorTerminal.c
  * @brief          : Motor terminal functions
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

#include "motorTerminal.h"


/*
 * @brief Initializes the GUI for the Motor Controller Terminal.
 * @return None
 */
void initTerminal(UART_HandleTypeDef* huart){
	  /*Initial Motor Control Messages*/
	  char buffer[MAX_BUFF];

	  // User Interface Initial Transmission
	  int len = sprintf(buffer,"Motor Controller Terminal\r\nMotor 1 and 2 enabled.\r\n");
	  HAL_UART_Transmit(huart, (uint8_t *)buffer, len, 10);
	  memset(buffer, 0, sizeof(buffer));


	  len = sprintf(buffer, USER_INPUT);
	  HAL_UART_Transmit(huart, (uint8_t *)buffer, len, 10);
}

/*
 * @brief Function is used to take in the user response and transmit. User is limited to a 4 character input
 * @return None
 */
void userRequest(UART_HandleTypeDef* huart, uint8_t* request) {
    uint8_t userData;
    int idx = 0;

    while (1) {
        if (HAL_UART_Receive(huart, &userData, 1, HAL_MAX_DELAY) == HAL_OK) {
            if (userData == '\r'){
            	HAL_UART_Transmit(huart, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
            	break;
            }

            if((userData == 0x7f) && idx > 0){
            	idx--;
            	HAL_UART_Transmit(huart, &userData, 1, HAL_MAX_DELAY);
            }

            else if (idx < REQ_SIZE) {
            	HAL_UART_Transmit(huart, &userData, 1, HAL_MAX_DELAY);
                request[idx++] = userData;
            }
        }
    }
}

/*
 * @brief Function Parses the User Request handling for a disable Motors, and Checking for valid
 * argument inputs. Determines the speed provided by the user.
 * @return int8_t
 */
int8_t parseRequest(UART_HandleTypeDef* huart, uint8_t* request){
	char msg[MAX_BUFF];
	int len = 0;

	if(request[0] == '!' && request[1] == '!' && request[2] == '!' && request[3]=='!'){
		len = sprintf(msg, "Disable Motors 1 and 2\r\n");
		HAL_UART_Transmit(huart, (uint8_t*) msg, len, HAL_MAX_DELAY);
		memset(msg, 0, sizeof(msg));
		HAL_UART_Transmit(huart, USER_INPUT, 2, HAL_MAX_DELAY);
		return -102;
	}

	/*User Request Parsing*/
	if((request[0] != 'M') || ( (request[1] < '1') || (request[1] > '2'))){
		len = sprintf(msg, "Invalid Command\r\n");
		HAL_UART_Transmit(huart, (uint8_t*) msg, len, HAL_MAX_DELAY);
		HAL_UART_Transmit(huart, USER_INPUT, 2, HAL_MAX_DELAY);
		memset(msg, 0, sizeof(msg));
		return -101;
	}

	/*User Speed Checking*/
	char hexValue[3];
	hexValue[0] = request[2];
	hexValue[1] = request[3];
	hexValue[2] = "\0";

	int8_t speed = (int8_t) strtol(hexValue, NULL, 16);

	if(speed < -100 || speed > 100){
		len = sprintf(msg, "Invalid Speed Value\r\n");
		HAL_UART_Transmit(huart,(uint8_t*) msg, len, HAL_MAX_DELAY);
		HAL_UART_Transmit(huart, (uint8_t*)USER_INPUT, 2, HAL_MAX_DELAY);
		memset(msg, 0, sizeof(msg));
		return -101;
	}
	len = sprintf(msg, "Motor %c speed set to %d.\r\n", request[1], speed);
	HAL_UART_Transmit(huart, (uint8_t*)msg, len, HAL_MAX_DELAY);
	HAL_UART_Transmit(huart, (uint8_t*)USER_INPUT, 2, HAL_MAX_DELAY);
	return speed;
}




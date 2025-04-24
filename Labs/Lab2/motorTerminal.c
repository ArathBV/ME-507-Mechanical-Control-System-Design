/*
 * motorTerminal.c
 *
 *  Created on: Apr 23, 2025
 *      Author: arath
 */

#include "motorTerminal.h"

/*
 *
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
 *
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
            if (idx < REQ_SIZE) {
            	HAL_UART_Transmit(huart, &userData, 1, HAL_MAX_DELAY);
                request[idx++] = userData;
            }
        }
    }
}

void parseRequest(UART_HandleTypeDef* huart, uint8_t* request){
	HAL_UART_Transmit(huart, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
	HAL_UART_Transmit(huart, request, 4, HAL_MAX_DELAY);
}




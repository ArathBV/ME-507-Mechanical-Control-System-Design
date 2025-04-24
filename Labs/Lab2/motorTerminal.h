/*
 * motorTerminal.h
 *
 *  Created on: Apr 23, 2025
 *      Author: arath
 */

#ifndef INC_MOTORTERMINAL_H_
#define INC_MOTORTERMINAL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

#define MAX_BUFF 1024
#define MAX_USER 7
#define MOTORS {1, 2}
#define USER_INPUT ">:"
#define REQ_SIZE 4

void initTerminal(UART_HandleTypeDef*);
void userRequest(UART_HandleTypeDef*, uint8_t*);
void parseRequest(UART_HandleTypeDef*, uint8_t*);



#endif /* INC_MOTORTERMINAL_H_ */

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

typedef struct MotorController{
	uint32_t CH_A;
	uint32_t CH_B;
	TIM_HandleTypeDef* timer;
	uint32_t dutyCycle;
}MotorController;

void initMotor(MotorController*, TIM_HandleTypeDef*, uint32_t, uint32_t);
void enableMotor(MotorController*);
int setDutyCycle(MotorController*, int32_t);
void disableMotor(MotorController *);


#endif

/**
  ******************************************************************************
  * @file           : pidController.cpp
  * @brief          : File containing the Functions to WALLE PID Controller
  * @author			: Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
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
#include "pidController.h"

/*
 * @brief Constructor Fucntion for PID Controller Class
 */
PIDController::PIDController(float kp, float ki, float kd)
    : Kp(kp), Ki(ki), Kd(kd), prevError(0), integral(0) {}

/*
 * @brief Resets Values of PID
 * @return None
 */
void PIDController::reset() {
    prevError = 0;
    integral = 0;
}

/*
 * @brief Function sets the tuning variables for the PID Controller
 * @return None
 */
void PIDController::setTunings(float kp, float ki, float kd) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
}

/*
 * @brief Function updates the PID based on the new error values and adjusts
 * @return None
 */
float PIDController::update(float error, float dt) {
    integral += error * dt;
    float derivative = (error - prevError) / dt;

    float output = Kp * error + Ki * integral + Kd * derivative;

    prevError = error;
    return output;
}

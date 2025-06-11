/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : WALLE_FSM.cpp
  * @brief          : File containing the Functions for the WALL_E Functionality
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
#include "WALLE_FSM.h"
#include "main.h" // for HAL_Delay if needed

/*
 * @brief WALLE Constructor Function that holds reference to all sensors for use in FSM.
 */
WALLE::WALLE(BNO055& imu, HCSR04& range, RomiMotor& leftMotor, RomiMotor& rightMotor,
		OV2640Camera& camera, Servo& LArm, Servo&LHand, Servo& RArm, Servo&RHand)
    : imu(imu), rangeSensor(range), leftMotor(leftMotor), rightMotor(rightMotor), camera(camera),
	  leftArm(LArm), leftHand(LHand), rightArm(RArm), rightHand(RHand),
      turnPID(1.5f, 0.0f, 0.2f), drivePID(1.0f, 0.01f, 0.1f),
      targetYaw(0.0f), initialYaw(0.0f),currentSegment(0), totalSegments(8), segmentAngle(45.0f),
	  stopTimer(0) {}

/*
 * @brief Function Initializes WALLE and restes the current PID States.
 * @return None
 */
void WALLE::init() {
    turnPID.reset();
    drivePID.reset();
    state = State::START_SCAN;
}

/*
 * @brief Function updates the FSM and peripherals at every call, creating
 * the autonomous WALL_E Bot based on PID.
 * return None
 */
void WALLE::update(float dt) {
    float yaw = imu.getYaw();
    //float yawRate = imu.getYawRateZ();
    uint16_t distance = rangeSensor.getDistanceCm();

    switch (state) {
        case State::START_SCAN:
            scanYawStart = yaw;
            currentSegment = 0;
            turnPID.reset();
            state = State::TURN_SEGMENT;
            break;

        case State::TURN_SEGMENT: {
            float target = normalizeAngle(scanYawStart + currentSegment * segmentAngle);
            float error = normalizeAngle(target - yaw);
            float correction = turnPID.update(error, dt);

            leftMotor.setSpeed(-correction);
            rightMotor.setSpeed(correction);

            if (fabsf(error) < yawTolerance) {
                stopMotors();
                stopTimer = HAL_GetTick();
                state = State::STOP_MEASURE;
            }
            break;
        }

        case State::STOP_MEASURE:
            if (HAL_GetTick() - stopTimer > 500) {
                distances[currentSegment] = rangeSensor.getDistanceCm();
                candidateAngles[currentSegment] = normalizeAngle(scanYawStart + currentSegment * segmentAngle);
                currentSegment++;

                if (currentSegment >= totalSegments) {
                    state = State::FINISH_SCAN;
                } else {
                    turnPID.reset();
                    state = State::TURN_SEGMENT;
                }
            }
            break;

        case State::FINISH_SCAN: {
            uint16_t minDist = 10000;
            int bestIndex = 0;
            for (int i = 0; i < totalSegments; ++i) {
                if (distances[i] < minDist) {
                    minDist = distances[i];
                    bestIndex = i;
                }
            }
            targetYaw = candidateAngles[bestIndex];
            state = State::TURN;
            break;
        }

        case State::TURN: {
            float yawError = normalizeAngle(targetYaw - yaw);
            float correction = turnPID.update(yawError, dt);

            leftMotor.setSpeed(-correction);
            rightMotor.setSpeed(correction);

            if (fabsf(yawError) < yawTolerance) {
                stopMotors();
                initialYaw = yaw;
                drivePID.reset();
                state = State::FORWARD;
            }
            break;
        }

        case State::FORWARD: {
            float yawError = normalizeAngle(initialYaw - yaw);
            float correction = drivePID.update(yawError, dt);

            int baseSpeed = 20;
            leftMotor.setSpeed(baseSpeed + correction);
            rightMotor.setSpeed(baseSpeed - correction);

            if (distance < distanceThreshold) {
                stopMotors();
                state = State::STOP;
            }
            break;
        }

        case State::STOP:
            stopMotors();
            state = State::IDENTIFY;
            break;

        case State::IDENTIFY:
        	closeHands();
        	liftArms();
        	break;
    }
}

void WALLE::simpleUpdate(float dt, float yaw, uint16_t distance){
	switch (state) {
		case State::START_SCAN:
			currentSegment = 0;
			actionDuration = 350; // milliseconds
			actionStartTime = HAL_GetTick();
			leftMotor.setSpeed(-50);
			rightMotor.setSpeed(50);
			state = State::TURN_SEGMENT;
			break;

		case State::TURN_SEGMENT:
			if (HAL_GetTick() - actionStartTime >= actionDuration) {
				stopMotors();
				actionStartTime = HAL_GetTick();
				state = State::STOP_MEASURE;
			}
			break;

		case State::STOP_MEASURE:
			if (HAL_GetTick() - actionStartTime >= 300) {
				distances[currentSegment] = rangeSensor.getDistanceCm();
				currentSegment++;

				if (currentSegment >= totalSegments) {
					uint16_t minDist = 10000;
					int bestIndex = 0;
					for (int i = 0; i < totalSegments; ++i) {
						if (distances[i] < minDist) {
							minDist = distances[i];
							bestIndex = i;
						}
					}
					targetYaw = scanYawStart + bestIndex * segmentAngle;
					actionStartTime = HAL_GetTick();
					actionDuration = 1500;
					leftMotor.setSpeed(50);
					rightMotor.setSpeed(50);
					state = State::FORWARD;
				} else {
					actionStartTime = HAL_GetTick();
					actionDuration = 350;
					leftMotor.setSpeed(-50);
					rightMotor.setSpeed(50);
					state = State::TURN_SEGMENT;
				}
			}
			break;

		case State::FORWARD:
			if (HAL_GetTick() - actionStartTime >= actionDuration || distance < distanceThreshold) {
				stopMotors();
				state = State::STOP;
			}
			break;

		case State::STOP:
			stopMotors();
			break;

		default:
			break;
	}
}

/*
 * @brief Function stops motors completely
 * @return None
 */
void WALLE::stopMotors() {
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
}

float WALLE::normalizeAngle(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}

void WALLE::closeHands(){
	leftHand.setAngle(180);
	rightHand.setAngle(0);
}

void WALLE::liftArms(){
	leftArm.setAngle(180);
	rightArm.setAngle(180);
	HAL_Delay(400);
	leftArm.setAngle(0);
	rightArm.setAngle(0);
}

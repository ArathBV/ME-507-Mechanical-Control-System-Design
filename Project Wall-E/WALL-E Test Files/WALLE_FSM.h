/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : WALLE_FSM.cpp
  * @brief          : File containing the Class for the WALL_E Functionality
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
#ifndef INC_WALLE_FSM_H_
#define INC_WALLE_FSM_H_


#include "bno055.h"
#include "hcsr04.h"
#include "romiMotor.h"
#include "servos.h"
#include "camera.h"
#include "pidController.h"
#include <cmath>

class WALLE {
public:
    WALLE(BNO055& imu, HCSR04& range, RomiMotor& leftMotor, RomiMotor& rightMotor, OV2640Camera& camera,
    		Servo& LArm, Servo&LHand, Servo& RArm, Servo&RHand);

    void init();            // Initializes internal state, resets PIDs
    void update(float dt);  // FSM update function, called in main loop
    void closeHands();
    void liftArms();
    void computerVision();

private:
    enum class State {
    	START_SCAN,
		TURN_SEGMENT,
		STOP_MEASURE,
        FINISH_SCAN,
        TURN,
        FORWARD,
        STOP,
		IDENTIFY
    }state;

    // References to hardware peripherals
    BNO055& imu;
    HCSR04& rangeSensor;
    RomiMotor& leftMotor;
    RomiMotor& rightMotor;
    OV2640Camera& camera;
    Servo& leftArm;
    Servo& leftHand;
    Servo& rightArm;
    Servo& rightHand;

    // PID controllers
    PIDController turnPID;
    PIDController drivePID;

    // FSM control variables
    float targetYaw;        // Yaw to turn to after scan
    float initialYaw;       // Yaw to hold while driving forward
    int currentSegment;
    int totalSegments;
    float segmentAngle;
    int stopTimer;
    float scanYawStart;
    int distances[16];
    int candidateAngles[16];


    // Constants
    const float yawTolerance = 2.0f;       // Degrees of error allowed when turning
    const uint16_t distanceThreshold = 7; // Distance to stop at (cm)

    // Internal helpers
    void stopMotors();
    float normalizeAngle(float angle); // Keeps angles within [-180, 180]
};

#endif /* INC_WALLE_FSM_H_ */

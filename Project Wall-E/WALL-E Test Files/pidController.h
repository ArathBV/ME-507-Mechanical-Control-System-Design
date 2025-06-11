/**
  ******************************************************************************
  * @file           : pidController.h
  * @brief          : File containing the PID Controller Class
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
#ifndef INC_PIDCONTROLLER_H_
#define INC_PIDCONTROLLER_H_


class PIDController {
	public:
		PIDController(float kp, float ki, float kd);

		void reset();
		void setTunings(float kp, float ki, float kd);

		float update(float error, float dt);  // returns output correction

	private:
		float Kp, Ki, Kd;
		float prevError;
		float integral;
	};
#endif /* INC_PIDCONTROLLER_H_ */

#include "motor_driver.h"
#include "main.h"

/*
 * !@brief Function initializes the motor device and struct.
 * !@return None
 */
void initMotor(MotorController* motor, TIM_HandleTypeDef* timer, uint32_t IN1, uint32_t IN2){
	motor->CH_A = IN1;
	motor->CH_B = IN2;
	motor->timer = timer;
	motor->dutyCycle = 0;
}


/*
 *
 */
void enableMotor(MotorController* motor){
	HAL_TIM_PWM_Start_IT((motor->timer), motor->CH_A);
	HAL_TIM_PWM_Start_IT((motor->timer), motor->CH_B);
	HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(motor->timer, motor->CH_A, motor->dutyCycle);
	__HAL_TIM_SET_COMPARE(motor->timer, motor->CH_B, motor->dutyCycle);
	HAL_Delay(1000);
}


/*
 *
 */
int setDutyCycle(MotorController* motor, int duty){
	if ((duty > 100) || (duty < -100)){
		return -1;
	}
	motor->dutyCycle = (duty + 100) * 24;
	__HAL_TIM_SET_COMPARE(motor->timer, motor->CH_A, motor->dutyCycle);
	__HAL_TIM_SET_COMPARE(motor->timer, motor->CH_B, motor->dutyCycle);
	return 0;

}

/*
 *
 */
void disableMotor(MotorController *motor){
	HAL_TIM_PWM_Stop_IT((motor->timer), motor->CH_A);
	HAL_TIM_PWM_Stop_IT((motor->timer), motor->CH_B);
}

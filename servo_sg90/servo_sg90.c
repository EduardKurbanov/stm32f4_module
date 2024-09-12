/*
 * servo_sg90.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "servo_sg90.h"
#include "servo_sg90_defs.h"


void servo_sg90_init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	TIM2->CCR1 = PULSE_LENGTH_CENTER;
	TIM2->CCR2 = PULSE_LENGTH_CENTER;
}

static int8_t set_servo_position(int8_t axis_angle_value, uint8_t pwm_servo, E_SERVO_STATUS *error_servo)
{
	E_SERVO_STATUS status_servo = E_OK_SERVO;
	uint16_t Pulse_length = PULSE_LENGTH_MIN;
	if (!((axis_angle_value >= -90) && (axis_angle_value <= 90)))
	{
		status_servo = E_ERROR_SERVO;
	}
	Pulse_length = PULSE_LENGTH_MIN + (PULSE_LENGTH_MAX - PULSE_LENGTH_MIN) * ((axis_angle_value + 90) / 180.0);
	if (pwm_servo == AXIS_X_PWM_SERVO) TIM2->CCR1 = Pulse_length;
	else if (pwm_servo == AXIS_Y_PWM_SERVO) TIM2->CCR2 = Pulse_length;
	*error_servo = status_servo;

	return axis_angle_value;
}

int8_t servo_axis_x(int8_t angle, E_SERVO_STATUS *error_servo)
{
	return set_servo_position(angle, AXIS_X_PWM_SERVO, error_servo);
}

int8_t servo_axis_y(int8_t angle, E_SERVO_STATUS *error_servo)
{
	return set_servo_position(angle, AXIS_Y_PWM_SERVO, error_servo);
}

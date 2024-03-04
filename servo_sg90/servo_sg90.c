#include "servo_sg90.h"
#include "servo_sg90_defs.h"
#include "tim.h"


void servo_sg90_init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	TIM2->CCR1 = PULSE_LENGTH_CENTER;
	TIM2->CCR1 = PULSE_LENGTH_CENTER;
}

static int8_t set_servo_position(int8_t axis_angle_value, uint8_t pwm_servo)
{
	uint16_t Pulse_length = PULSE_LENGTH_MIN;
	if (!((axis_angle_value >= -90) && (axis_angle_value <= 90)))
	{
		return 1;
	}
	Pulse_length = PULSE_LENGTH_MIN + (PULSE_LENGTH_MAX - PULSE_LENGTH_MIN) * ((axis_angle_value + 90) / 180.0);
	if (pwm_servo == AXIS_X_PWM_SERVO) TIM2->CCR1 = Pulse_length;
	else if (pwm_servo == AXIS_X_PWM_SERVO) TIM2->CCR2 = Pulse_length;

	return axis_angle_value;
}

int8_t servo_axis_x(int8_t angle)
{
	return set_servo_position(angle, AXIS_X_PWM_SERVO);
}

int8_t servo_axis_y(int8_t angle)
{
	return set_servo_position(angle, AXIS_Y_PWM_SERVO);
}
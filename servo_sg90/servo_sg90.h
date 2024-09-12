/*
 * servo_sg90.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef SERVO_SG90_H
#define SERVO_SG90_H


#include <inttypes.h>
#include "tim.h"

typedef enum
{
	E_OK_SERVO = 100,
	E_ERROR_SERVO = 200,
}E_SERVO_STATUS;

void servo_sg90_init(void);
int8_t servo_axis_x(int8_t angle, E_SERVO_STATUS *error_servo);
int8_t servo_axis_y(int8_t angle, E_SERVO_STATUS *error_servo);


#endif

/*
 * l293d.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef L293D_H
#define L293D_H


#include "gpio.h"


typedef enum
{
	E_FORWARD = 1,
	E_BACK = 2,
	E_RIGHT = 3,
	E_LEFT = 4,
	E_STOP = 5,
}E_MOTOR_COMMAND;

typedef enum
{
	E_OK_MOTOR = 100,
	E_ERROR_MOTOR = 200,
}E_MOTOR_STATUS;

void l293d_driver_port_reset(void);
void l293d_driver_motor(E_MOTOR_COMMAND motorAction, E_MOTOR_STATUS *error_driver);

#endif

#ifndef SERVO_SG90_H
#define SERVO_SG90_H

#include <inttypes.h>

void servo_sg90_init(void);
int8_t servo_axis_x(int8_t angle);
int8_t servo_axis_y(int8_t angle);

#endif
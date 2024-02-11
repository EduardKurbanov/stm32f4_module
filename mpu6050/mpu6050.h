#ifndef MPU6050_H
#define MPU6050_H

#include <math.h>
#include <inttypes.h>


typedef struct {
	float x;
	float y;
	float z;
} GyroData;

void accel_gyro_init(void);

float accel_axis_x(void);

float accel_axis_y(void);

float accel_axis_z(void);

float temp(void);

float gyro_axis_x(void);

float gyro_axis_y(void);

float gyro_axis_z(void);

float axis_rotation_angle_x(void);

float axis_rotation_angle_y(void);

GyroData gyro_calibration(void);

#endif

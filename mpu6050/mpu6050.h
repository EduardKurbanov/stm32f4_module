/*
 * mpu6050.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef MPU6050_H
#define MPU6050_H

#include <math.h>
#include <inttypes.h>
#include "i2c.h"

#define _DEVICE_ADDRESS                0x68
#define _BUS_HANDLER                   &hi2c1

typedef struct {
    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    float Ax;
    float Ay;
    float Az;
    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    float Gx;
    float Gy;
    float Gz;
    float Temperature;
    float Angles_axis_x_raw;
    float Angles_axis_y_raw;
    float KalmanAngleX;
    float KalmanAngleY;
} MPU6050;

typedef struct {
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman;

typedef enum
{
	E_OK_MPU = 100,
	E_ERROR_MPU = 200,
}E_MPU_STATUS;

void status_mpu6050(E_MPU_STATUS *error_mpu);

void mpu6050_init(void);

void mpu6050_read_accel(MPU6050 *DataStruct);

void mpu6050_read_gyro(MPU6050 *DataStruct);

void mpu6050_read_temp(MPU6050 *DataStruct);

void mpu6050_read_gyro_axis_x(MPU6050 *DataStruct);

void mpu6050_read_gyro_axis_y(MPU6050 *DataStruct);

void mpu6050_read_gyro_axis_z(MPU6050 *DataStruct);

void mpu6050_axis_rotation_angle_x_raw(MPU6050 *DataStruct);

void mpu6050_axis_rotation_angle_y_raw(MPU6050 *DataStruct);

void mpu6050_axis_rotation_angle_x_y_kalman(MPU6050 *DataStruct);


#endif


/*
 * #include "mpu6050.h"
 *
 * float ang_x_k, ang_y_k;
 *
 * MPU6050 MPU6050M;
 *
 * int main(void)
 * {
 * 		mpu6050_init();
 *
 * 		while(1)
 * 		{
 * 			  mpu6050_read_accel(&MPU6050M);
			  mpu6050_read_gyro(&MPU6050M);
			  mpu6050_read_temp(&MPU6050M);
			  mpu6050_axis_rotation_angle_x_raw(&MPU6050M);
			  mpu6050_axis_rotation_angle_y_raw(&MPU6050M);
			  mpu6050_axis_rotation_angle_x_y_kalman(&MPU6050M);
			  ang_x_k = MPU6050M.KalmanAngleX;
			  ang_y_k = MPU6050M.KalmanAngleY;
	          HAL_Delay (100);
 * 		}
 * 		return 0;
 * }
 */

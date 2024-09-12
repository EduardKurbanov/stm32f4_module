/*
 * mpu6050_defs.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef MPU6050_DEFS_H
#define MPU6050_DEFS_H


#define _WHO_AM_I                      0x75
// # MPU - 6050 Registers
#define _REGISTER_MPU6050_PWR_MGMT_1   0x6B  //# Primary power / sleep control register
#define _REGISTER_MPU6050_PWR_MGMT_2   0x6C  //# Secondary power / sleep control register
#define _REGISTER_MPU6050_SMPLRT_DIV   0x07
#define _REGISTER_GYRO_CONFIG          0x1B
#define _REGISTER_ACCEL_CONFIG         0x1C
#define _REGISTER_ACCEL_X_OUT_H        0x3B
#define _REGISTER_ACCEL_X_OUT_L        0x3C
#define _REGISTER_ACCEL_Y_OUT_H        0x3D
#define _REGISTER_ACCEL_Y_OUT_L        0x3E
#define _REGISTER_ACCEL_Z_OUT_H        0x3F
#define _REGISTER_ACCEL_Z_OUT_L        0x40
#define _REGISTER_TEMP_OUT_H           0X41
#define _REGISTER_TEMP_OUT_L           0X42
#define _REGISTER_GYRO_X_OUT_H         0x43
#define _REGISTER_GYRO_X_OUT_L         0x44
#define _REGISTER_GYRO_Y_OUT_H         0x45
#define _REGISTER_GYRO_Y_OUT_L         0x46
#define _REGISTER_GYRO_Z_OUT_H         0x47
#define _REGISTER_GYRO_Z_OUT_L         0x48
// Pre - defined ranges
#define _REGISTER_ACCEL_RANGE_2G       0x00
#define _REGISTER_ACCEL_RANGE_4G       0x08
#define _REGISTER_ACCEL_RANGE_8G       0x10
#define _REGISTER_ACCEL_RANGE_16G      0x18
#define _REGISTER_GYRO_RANGE_250DEG    0x00
#define _REGISTER_GYRO_RANGE_500DEG    0x08
#define _REGISTER_GYRO_RANGE_1000DEG   0x10
#define _REGISTER_GYRO_RANGE_2000DEG   0x18
// # earth gravity
#define _STANDARD_GRAVITY              9.80665f
// # Modifiers accel
#define _ACCEL_RANGE_2_G_16384_LSB     16384.0f  //#  + / -2g(default value), 16384 LSB / G(default value)
#define _ACCEL_RANGE_4_G_8192_LSB      8192.0f    //#  + / -4g, 8192 LSB / G
#define _ACCEL_RANGE_8_G_4096_LSB      4096.0f    //#  + / -8g, 4096 LSB / G
#define _ACCEL_RANGE_16_G_2048_LSB     2048.0f   //#  + / -16g, 2048 LSB / G
// # Modifiers gyro
#define _GYRO_RANGE_250_DPS            131.0f  //#  + / -250 deg / s(default value)
#define _GYRO_RANGE_500_DPS            65.5f   //#  + / -500 deg / s
#define _GYRO_RANGE_1000_DPS           32.8f  //#  + / -1000 deg / s
#define _GYRO_RANGE_2000_DPS           16.4f  //#  + / -2000 deg / s


#endif

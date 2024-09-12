/*
 * mpu6050.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "mpu6050.h"
#include "mpu6050_defs.h"

#define CONVERT_DATA(__buffer, idx)   (int16_t)((__buffer[idx] << 8) | __buffer[idx + 1])
#define RAD_TO_DEG(__rad)             ((__rad) * (180.0f / M_PI))

static uint32_t timer;

static Kalman KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

static Kalman KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};

static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static double Kalman_getAngle(Kalman *Kalman, double newAngle, double newRate, double dt) {
    double rate = newRate - Kalman->bias;
    Kalman->angle += dt * rate;

    Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
    Kalman->P[0][1] -= dt * Kalman->P[1][1];
    Kalman->P[1][0] -= dt * Kalman->P[1][1];
    Kalman->P[1][1] += Kalman->Q_bias * dt;

    double S = Kalman->P[0][0] + Kalman->R_measure;
    double K[2];
    K[0] = Kalman->P[0][0] / S;
    K[1] = Kalman->P[1][0] / S;

    double y = newAngle - Kalman->angle;
    Kalman->angle += K[0] * y;
    Kalman->bias += K[1] * y;

    double P00_temp = Kalman->P[0][0];
    double P01_temp = Kalman->P[0][1];

    Kalman->P[0][0] -= K[0] * P00_temp;
    Kalman->P[0][1] -= K[0] * P01_temp;
    Kalman->P[1][0] -= K[1] * P00_temp;
    Kalman->P[1][1] -= K[1] * P01_temp;

    return Kalman->angle;
};

void status_mpu6050(E_MPU_STATUS *error_mpu)
{
	E_MPU_STATUS status_mpu = E_OK_MPU;
	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(_BUS_HANDLER, _DEVICE_ADDRESS << 1, 3, 100); // Пример с 3 попытками и таймаутом 100 мс
	if(result == HAL_OK)
	{
		status_mpu = E_OK_MPU;
	}
	else
	{
		status_mpu = E_ERROR_MPU;
	}

	*error_mpu = status_mpu;
}

void mpu6050_init(void)
{
	uint8_t pwr_mgmt = 0x00;
	uint8_t accel_config = _REGISTER_ACCEL_RANGE_4G;
	uint8_t gyro_config = _REGISTER_GYRO_RANGE_500DEG;
	uint8_t data_config = 0x07;
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_MPU6050_PWR_MGMT_1, &pwr_mgmt, 1);
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_MPU6050_SMPLRT_DIV, &data_config, 1);
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_CONFIG, &accel_config, 1);
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_GYRO_CONFIG, &gyro_config, 1);
}

void mpu6050_read_accel(MPU6050 *DataStruct)
{
	uint8_t buff[6] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_X_OUT_H | 0x80, buff, 6U);
	DataStruct->Accel_X_RAW = CONVERT_DATA(buff, 0);
	DataStruct->Accel_Y_RAW = CONVERT_DATA(buff, 2);
	DataStruct->Accel_Z_RAW = CONVERT_DATA(buff, 4);
	DataStruct->Ax = DataStruct->Accel_X_RAW / _ACCEL_RANGE_4_G_8192_LSB;
	DataStruct->Ay = DataStruct->Accel_Y_RAW / _ACCEL_RANGE_4_G_8192_LSB;
	DataStruct->Az = DataStruct->Accel_Z_RAW / _ACCEL_RANGE_4_G_8192_LSB;
}

void mpu6050_read_temp(MPU6050 *DataStruct)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_TEMP_OUT_H | 0x80, buff, 2U);
	DataStruct->Temperature = ( CONVERT_DATA(buff, 0) / 340.0f) + 36.53f;
}

void mpu6050_read_gyro(MPU6050 *DataStruct)
{
	uint8_t buff[6] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_GYRO_X_OUT_H | 0x80, buff, 6U);
	DataStruct->Gyro_X_RAW = CONVERT_DATA(buff, 0);
	DataStruct->Gyro_Y_RAW = CONVERT_DATA(buff, 2);
	DataStruct->Gyro_Z_RAW = CONVERT_DATA(buff, 4);
	DataStruct->Gx = DataStruct->Gyro_X_RAW / _GYRO_RANGE_500_DPS;
	DataStruct->Gy = DataStruct->Gyro_Y_RAW / _GYRO_RANGE_500_DPS;
	DataStruct->Gz = DataStruct->Gyro_Z_RAW / _GYRO_RANGE_500_DPS;
}

void mpu6050_axis_rotation_angle_x_raw(MPU6050 *DataStruct)
{
	DataStruct->Angles_axis_x_raw = RAD_TO_DEG(atan2f(DataStruct->Ay,sqrt(powf(DataStruct->Ax, 2.0f) + powf(DataStruct->Az, 2.0f))));
}

void mpu6050_axis_rotation_angle_y_raw(MPU6050 *DataStruct)
{
	DataStruct->Angles_axis_y_raw = RAD_TO_DEG(atan2f(DataStruct->Ax, sqrt(powf(DataStruct->Ay, 2.0f) + powf(DataStruct->Az, 2.0f))));
}

void mpu6050_axis_rotation_angle_x_y_kalman(MPU6050 *DataStruct)
{
    float dt = (float)(HAL_GetTick() - timer) / 1000;
    timer = HAL_GetTick();
    float roll;
    float roll_sqrt = sqrt(
            DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
    if (roll_sqrt != 0.0) {
        roll = RAD_TO_DEG(atan(DataStruct->Accel_Y_RAW / roll_sqrt));
    } else {
        roll = 0.0;
    }
    double pitch = RAD_TO_DEG(atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW));
    if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90)) {
        KalmanY.angle = pitch;
        DataStruct->KalmanAngleY = pitch;
    } else {
        DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
    }
    if (fabs(DataStruct->KalmanAngleY) > 90)
        DataStruct->Gx = -DataStruct->Gx;
    DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gy, dt);
}



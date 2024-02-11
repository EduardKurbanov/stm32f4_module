#include "mpu6050.h"
#include "mpu6050_defs.h"
#include "i2c.h"

#define CONVERT_DATA(__buffer)   (int16_t)((__buffer[0] << 8) | __buffer[1])
#define RAD_TO_DEG(__rad)        ((__rad) * (180.0f / M_PI))
#define CALIBRATION_SAMPLES      2000


static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t *pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

void accel_gyro_init(void)
{
	uint8_t pwr_mgmt = 0x00;
	uint8_t accel_config = _REGISTER_ACCEL_RANGE_16G;
	uint8_t gyro_config = _REGISTER_GYRO_RANGE_2000DEG;
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_MPU6050_PWR_MGMT_1, &pwr_mgmt, 1);
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_CONFIG, &accel_config, 1);
	i2c_write_data(_DEVICE_ADDRESS, _REGISTER_GYRO_CONFIG, &gyro_config, 1);
}

float accel_axis_x(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_X_OUT_H, buff, 2U);
	return CONVERT_DATA(buff) / _ACCEL_RANGE_16_G_2048_LSB;
}

float accel_axis_y(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_Y_OUT_H, buff, 2U);
	return CONVERT_DATA(buff) / _ACCEL_RANGE_16_G_2048_LSB;
}

float accel_axis_z(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_ACCEL_Z_OUT_H, buff, 2U);
	return CONVERT_DATA(buff) / _ACCEL_RANGE_16_G_2048_LSB;
}

float temp(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_TEMP_OUT_H, buff, 2U);
	return ( CONVERT_DATA(buff) / 340) + 36.53f;
}

float gyro_axis_x(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_GYRO_X_OUT_H, buff, 2U);
	return ( CONVERT_DATA(buff) / _GYRO_RANGE_2000_DPS);
}

float gyro_axis_y(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_GYRO_Y_OUT_H, buff, 2U);
	return (CONVERT_DATA(buff) / _GYRO_RANGE_2000_DPS);
}

float gyro_axis_z(void)
{
	uint8_t buff[2] = { 0 };
	i2c_read_data(_DEVICE_ADDRESS, _REGISTER_GYRO_Z_OUT_H, buff, 2U);
	return (CONVERT_DATA(buff) / _GYRO_RANGE_2000_DPS);
}

float axis_rotation_angle_x(void)
{
	return RAD_TO_DEG(atan2f(accel_axis_x(),sqrt(powf(accel_axis_x(), 2.0f) + powf(accel_axis_z(), 2.0f))));
}

float axis_rotation_angle_y(void)
{
	return RAD_TO_DEG(atan2f(-accel_axis_x(), sqrt(powf(accel_axis_y(), 2.0f) + powf(accel_axis_z(), 2.0f))));
}

GyroData gyro_calibration(void) {
	GyroData gyro_calibration_data = { 0.0, 0.0, 0.0 };

	for (int i = 0; i < CALIBRATION_SAMPLES; ++i) {
		float gyro_x = gyro_axis_x();
		float gyro_y = gyro_axis_y();
		float gyro_z = gyro_axis_z();

		gyro_calibration_data.x += gyro_x;
		gyro_calibration_data.y += gyro_y;
		gyro_calibration_data.z += gyro_z;
	}

	gyro_calibration_data.x /= CALIBRATION_SAMPLES;
	gyro_calibration_data.y /= CALIBRATION_SAMPLES;
	gyro_calibration_data.z /= CALIBRATION_SAMPLES;

	return gyro_calibration_data;
}


/*
* int main() {
    GyroData calibration_result = gyro_calibration();

    // Print the calibration results
    printf("Calibration Results:\n");
    printf("X: %f\n", calibration_result.x);
    printf("Y: %f\n", calibration_result.y);
    printf("Z: %f\n", calibration_result.z);

    return 0;
}
*/

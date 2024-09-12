/*
 * qmc5883l.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "qmc5883l.h"
#include "qmc5883l_defs.h"

#define CONVERT_DATA(__high_bit, __low_bit)   (int16_t)((__high_bit << 8) | __low_bit)
#define RAD_TO_DEG(__rad)                     (float)((__rad) * (180.0f / M_PI))

typedef struct
{
    float axis_x;
    float axis_y;
    float axis_z;
}mag_raw_axis_data_s_t;

float _declination = 0.0f;
float _calibration[3][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};


static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint16_t mode_conf(void)
{
    return (
        _REG_MODE_CONTROL_CONTINUOUS |
        _REG_DATA_UPDATE_RATE_ODR_50HZ |
        _REG_FULL_SCALE_RNG_2G |
        _REG_OVERSAMPLING_OSR_512
        );
}

void qmc5883l_status(E_QMC_STATUS *error_qmc)
{
	E_QMC_STATUS status_qmc = E_OK_QMC;
	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(_BUS_HANDLER, _DEVICE_ADDRESS << 1, 3, 100); // Пример с 3 попытками и таймаутом 100 мс
	if(result == HAL_OK)
	{
		status_qmc = E_OK_QMC;
	}
	else
	{
		status_qmc = E_ERROR_QMC;
	}
	*error_qmc = status_qmc;
}

void qmc5883l_init(void)
{
    uint8_t soft_reset = _REG_SOFT_RST;
    uint8_t interrupt_pin_enabling = _REG_INT_ENB;
    uint8_t defauld_reg = 0x01;
    uint16_t mode = mode_conf();
    uint8_t buff[2] = {mode & 0xFF, (mode >> 8) & 0xFF};
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_2, &soft_reset, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_2, &interrupt_pin_enabling, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_SET_RESET_PERIOD, &defauld_reg, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_1, buff, 2);
}

static uint8_t *qmc5883l_read_block_data(void)
{
    static uint8_t buff[6] = {0};
    i2c_read_data(_DEVICE_ADDRESS, _REG_QMC5883L_DATA_OUTPUT_X_LSB_L, buff, 6);
    return buff;
}

static void qmc5883l_convert_data_signet_int(mag_raw_axis_data_s_t *p_axis_data)
{
    uint8_t *sensor_data = qmc5883l_read_block_data();
    p_axis_data->axis_x = (float)CONVERT_DATA(sensor_data[1], sensor_data[0]);
    p_axis_data->axis_y = (float)CONVERT_DATA(sensor_data[3], sensor_data[2]);
    p_axis_data->axis_z = (float)CONVERT_DATA(sensor_data[5], sensor_data[4]);
}

uint8_t qmc5883l_set_declination(float degrees)
{
    //"""Set the magnetic declination, in degrees."""
	uint8_t status = 0;
    if (degrees < -180.0f || degrees > 180.0f)
    {
        printf("Declination must be >= -180 and <= 180.");
        status = 1;
    }
    else
    {
         _declination = degrees;
    }
    return status;
}

void qmc5883l_set_calibration(float value[3][3])
{
    //"""Set the 3x3 matrix for horizontal (x, y) magnetic vector calibration."""
    memcpy( _calibration, value, sizeof(_calibration));
}

static float *qmc5883l_get_magnet_field(void)
{
    static float data_axis_x_y[2] = {0.0f};
    mag_raw_axis_data_s_t sensor_data = {0};

    qmc5883l_convert_data_signet_int(&sensor_data);

    if ((sensor_data.axis_x == 0.0f) || (sensor_data.axis_y == 0.0f))
    {
        data_axis_x_y[0] = sensor_data.axis_x;
        data_axis_x_y[1] = sensor_data.axis_y;
    }
    else
    {
        data_axis_x_y[0] = sensor_data.axis_x * _calibration[0][0] + sensor_data.axis_y * _calibration[0][1] + _calibration[0][2];
        data_axis_x_y[1] = sensor_data.axis_x * _calibration[1][0] + sensor_data.axis_y * _calibration[1][1] + _calibration[1][2];
    }
    return data_axis_x_y;
}

float qmc5883l_get_bearing_raw(void)
{
    float degrees = 0.0f;
    mag_raw_axis_data_s_t sensor_data = {0};

    qmc5883l_convert_data_signet_int(&sensor_data);

    if ((sensor_data.axis_x != 0.0f) || (sensor_data.axis_y != 0.0f))
    {
        degrees = RAD_TO_DEG(atan2f(sensor_data.axis_y, sensor_data.axis_x));
        if (degrees < 0)
        {
            degrees += 360.0f;
        }
    }
    return degrees;
}

float qmc5883l_get_bearing(void)
{
    float degrees = 0.0f;

    float *p_axis_data = qmc5883l_get_magnet_field();

    if ((p_axis_data[0] != 0.0f) || (p_axis_data[1] != 0.0f))
    {
        degrees = RAD_TO_DEG(atan2f(p_axis_data[1], p_axis_data[0]));
        if (degrees < 0)
        {
            degrees += 360.0f;
        }
        degrees += _declination;
        if (degrees < 0.0f)
        {
            degrees += 360.0f;
        }
        else if (degrees >= 360.0f)
        {
            degrees -= 360.0f;
        }
    }
    return degrees;
}

#include "qmc5883l.h"
#include "qmc5883l_defs.h"
#include "i2c.h"
#include <stdio.h>

#define CONVERT_DATA(__high_bit, __low_bit)   (int16_t)((__high_bit << 8) | __low_bit)
#define RAD_TO_DEG(__rad)                     (float)((__rad) * (180.0f / M_PI))


float _declination = 0.0f;
float _calibration[3][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};


static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint16_t mode_conf(void)
{
    return (
        _REG_MODE_CONTROL_CONTINUOUS |
        _REG_DATA_UPDATE_RATE_ODR_50HZ |
        _REG_FULL_SCALE_RNG_2G |
        _REG_OVERSAMPLING_OSR_128
        );
}

void qmc5883l_init(void)
{
    uint8_t soft_reset = _REG_SOFT_RST;
    uint8_t interrupt_pin_enabling = _REG_INT_ENB;
    uint8_t defauld_reg = 0x00;
    uint16_t mode = mode_conf();
    uint8_t buff[2] = {mode & 0xFF, (mode >> 8) & 0xFF};
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_2, &soft_reset, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_2, &interrupt_pin_enabling, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_SET_RESET_PERIOD, &defauld_reg, 1);
    i2c_write_data(_DEVICE_ADDRESS, _REG_QMC5883L_CONF_1, buff, 2);
}

static uint8_t *read_block_data(void)
{
    static uint8_t buff[6] = {0};
    i2c_read_data(_DEVICE_ADDRESS, _REG_QMC5883L_DATA_OUTPUT_X_LSB_L, buff, 6);
    return buff;
}

static int16_t *convert_data_signet_int(void)
{
    static int16_t axis_x_y_z[3] = {0};
    axis_x_y_z[0] = CONVERT_DATA(read_block_data()[1], read_block_data()[0]);
    axis_x_y_z[1] = CONVERT_DATA(read_block_data()[3], read_block_data()[2]);
    axis_x_y_z[2] = CONVERT_DATA(read_block_data()[5], read_block_data()[4]);
    return axis_x_y_z;
}

uint8_t set_declination(float degrees)
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

void set_calibration(float value[3][3])
{
    //"""Set the 3x3 matrix for horizontal (x, y) magnetic vector calibration."""
    float c[3][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            c[i][j] = value[i][j];
        }
    }
    // Copy the values from c to _calibration
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            _calibration[i][j] = c[i][j];
        }
    }
}

int16_t get_magnetic_field_axis_x(void)
{
    return convert_data_signet_int()[0];
}

int16_t get_magnetic_field_axis_y(void)
{
    return convert_data_signet_int()[1];
}

int16_t get_magnetic_field_axis_z(void)
{
    return convert_data_signet_int()[2];
}

float *get_magnet_field(void)
{
    float x = get_magnetic_field_axis_x();
    float y = get_magnetic_field_axis_y();
    static float data_axis_x_y[2] = {0.0f};
    if (x == 0.0f || y == 0.0f) 
    {
        data_axis_x_y[0] = x;
        data_axis_x_y[1] = y;
    } 
    else 
    {
        float c[3][3];
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                c[i][j] = _calibration[i][j];
            }
        }
        data_axis_x_y[0] = x * c[0][0] + y * c[0][1] + c[0][2];
        data_axis_x_y[1] = x * c[1][0] + y * c[1][1] + c[1][2];
    }
    return data_axis_x_y;
}

float get_bearing_raw(void)
{
    float degrees = 0.0f;
    float x = get_magnetic_field_axis_x();
    float y = get_magnetic_field_axis_y();
    if (x == 0.0f || y == 0.0f) 
    {
        return 0;
    }
    else
    {
        degrees = RAD_TO_DEG(atan2f(y, x));
        if (degrees < 0)
        {
            degrees += 360.0f;
        }
        return degrees;
    }
}

float get_bearing(void)
{
    float degrees = 0.0f;
    float x = get_magnet_field()[0];
    float y = get_magnet_field()[1];
    if (x == 0.0f || y == 0.0f) 
    {
        return 0;
    }
    else
    {
        degrees = RAD_TO_DEG(atan2f(y, x));
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

/*
k2g = [[1.0086972793142255, -0.04161991734605183, 1788.4219998515782], 
       [-0.04161991734605183, 1.1991677462926738, 586.365808229903], 
                                                    [0.0, 0.0, 1.0]]

mag_declination = 8.22

qmc5883l_init();
set_declination(mag_declination);
set_calibration(k2g);
while (1)
{
    print(get_bearing())
}
*/

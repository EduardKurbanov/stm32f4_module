/*
 * ds3231.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "ds3231.h"
#include "ds3231_defs.h"


static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 1000);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 1000);
}

void ds3231_init(void)
{
}

void ds3231_status_i2c(E_DS3231_STATUS* error_ds3231)
{
	E_MPU_STATUS status_ds3231 = E_OK_DS3231;
	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(_BUS_HANDLER, _DS3231_DEVICE_ADDRESS << 1, 3, 100); // Пример с 3 попытками и таймаутом 100 мс
	if (result == HAL_OK)
	{
		status_mpu = E_OK_DS3231;
	}
	else
	{
		status_mpu = E_ERROR_DS3231;
	}
	*error_ds3231 = status_ds3231;
}

static uint8_t decToBcd(int val)
{
	return (uint8_t)((val / 10 * 16) + (val % 10));
}
// Convert binary coded decimal to normal decimal numbers
static int bcdToDec(uint8_t val)
{
	return (int)((val / 16 * 10) + (val % 16));
}

TIME time;
SYSTEMTIME time;
GetLocalTime(&time);

void ds3231_set_time_auto_windows(void)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd((uint8_t)time.wSecond);
	set_time[1] = decToBcd((uint8_t)time.wMinute);
	set_time[2] = decToBcd((uint8_t)time.wHour);
	set_time[3] = decToBcd((uint8_t)time.wDayOfWeek);
	set_time[4] = decToBcd((uint8_t)time.wDay);
	set_time[5] = decToBcd((uint8_t)time.wMonth);
	set_time[6] = decToBcd((uint8_t)(time.wYear - 2000));

	i2c_write_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_SECOND, set_time, 7);
}

void ds3231_set_time_manual(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	i2c_write_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_SECOND, set_time, 7);
}

void ds3231_get_time(void)
{
	uint8_t get_time[7];
	i2c_read_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_SECOND, get_time, 7);
	time.seconds = bcdToDec(get_time[0]);
	time.minutes = bcdToDec(get_time[1]);
	time.hour = bcdToDec(get_time[2]);
	time.dayofweek = bcdToDec(get_time[3]);
	time.dayofmonth = bcdToDec(get_time[4]);
	time.month = bcdToDec(get_time[5]);
	time.year = bcdToDec(get_time[6]);
}

float ds3231_get_temp(void)
{
	uint8_t temp[2];

	i2c_read_data(_DS3231_DEVICE_ADDRESS, _DS3231_TEMP_MSB, temp, 2);
	return ((temp[0]) + (temp[1] >> 6) / 4.0);
}

void ds3231_force_temp_conv(void)
{
	uint8_t status = 0;
	uint8_t control = 0;
	i2c_read_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_STATUS, &status, 1);
	if (!(status & 0x04))
	{
		i2c_read_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_CONTROL, &control, 1);
		i2c_write_data(_DS3231_DEVICE_ADDRESS, _DS3231_REG_CONTROL, (uint8_t*)(control | (0x20)), 1);
	}
}

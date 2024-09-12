/*
 * ads1115.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "ads1115.h"
#include "ads1115_defs.h"


static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(_BUS_HANDLER, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(_BUS_HANDLER, (DevAddress << 1) | 0x1, MemAddress, 1U, pData, Size, 100);
}

static uint16_t mode_conf(uint16_t channel_adc, uint16_t pga_adc, uint8_t sps_adc)
{
	return (_REG_ADS1115_CONFIG_OS_SINGLE |
		channel_adc |
		pga_adc |
		_REG_ADS1115_CONFIG_MODE_SINGLE |
		sps_adc |
		_REG_ADS1115_COMP_QUE_DISABLE_CONVER |
		_REG_ADS1115_COMP_NON_LAT |
		_REG_ADS1115_COMP_POL_ACTIVE_LOW |
		_REG_ADS1115_COMP_MODE_TRAD);
}

void ads1115_status(E_ADC_STATUS *error_adc)
{
	E_ADC_STATUS status_adc = E_OK_ADC;
	HAL_StatusTypeDef result;
	result = HAL_I2C_IsDeviceReady(_BUS_HANDLER, _DEVICE_ADDRESS << 1, 3, 100); // Пример с 3 попытками и таймаутом 100 мс
	if(result == HAL_OK)
	{
		status_adc = E_OK_ADC;
	}
	else
	{
		status_adc = E_ERROR_ADC;
	}

	*error_adc = status_adc;
}

float ads1115_get_read(uint16_t channel_adc, uint16_t pga_adc, uint8_t sps_adc)
{
	uint16_t val = 0;
	float pga_adc_v = 0;
//	uint16_t sps_adc_v = 0;
	uint16_t mode = mode_conf((uint16_t)channel_adc, (uint16_t)pga_adc, (uint8_t)sps_adc);
	uint8_t buff[2] = { (uint8_t)((mode >> 8) & 0xFF), (uint8_t)(mode & 0xFF) };
	uint8_t buff_rx[2] = { 0 };
	i2c_write_data(_DEVICE_ADDRESS, _REG_ADS1115_ADDRESS_POINTER_CONFIG, buff, 2U);
/*
	switch (sps_adc)
	{
		case DR_8_SPS:
			sps_adc_v = 8;
			break;
		case DR_16_SPS:
			sps_adc_v = 16;
			break;
		case DR_32_SPS:
			sps_adc_v = 32;
			break;
		case DR_64_SPS:
			sps_adc_v = 64;
			break;
		case DR_128_SPS:
			sps_adc_v = 128;
			break;
		case DR_250_SPS:
			sps_adc_v = 250;
			break;
		case DR_475_SPS:
			sps_adc_v = 475;
			break;
		case DR_860_SPS:
			sps_adc_v = 860;
			break;
		default:
			sps_adc_v = 250;
			break;
	}
*/
	switch (pga_adc)
	{
		case PGA_FSR__6_144V:
			pga_adc_v = 6.144;
			break;
		case PGA_FSR__4_096V:
			pga_adc_v = 4.096;
			break;
		case PGA_FSR__2_048V:
			pga_adc_v = 2.048;
			break;
		case PGA_FSR__1_024V:
			pga_adc_v = 1.024;
			break;
		case PGA_FSR__0_512V:
			pga_adc_v = 0.512;
			break;
		case PGA_FSR__0_256V:
			pga_adc_v = 0.256;
			break;
		default:
			pga_adc_v = 6.144;
			break;
	}

	do
	{
		i2c_read_data(_DEVICE_ADDRESS, _REG_ADS1115_ADDRESS_POINTER_CONFIG, buff_rx, 2U);
	}
	while(((((buff_rx[0] << 8) | (buff_rx[1])) & _REG_ADS1115_CONFIG_OS_SINGLE) == 0) != 0 );

//	HAL_Delay((1000/(uint16_t)sps_adc_v) + 4);
	i2c_read_data(_DEVICE_ADDRESS, _REG_ADS1115_POINTER_CONVERSION, buff_rx, 2U);
	val = (buff_rx[0] << 8) | (buff_rx[1]);

	if (val > 0x7FFF)
	{
		return (val - 0xFFFF) * pga_adc_v / 32768.0f;
	}
	else
	{
		return ((buff_rx[0] << 8) | (buff_rx[1])) * pga_adc_v / 32768.0f;
	}
}

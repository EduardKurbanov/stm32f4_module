#include "ads1115.h"
#include "ads1115_defs.h"
#include "i2c.h"

static uint8_t i2c_write_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}

static uint8_t i2c_read_data(uint8_t DevAddress, uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(&hi2c1, DevAddress << 1, MemAddress, 1U, pData, Size, 100);
}


static uint16_t mode_conf(uint8_t channel_adc, uint16_t pga_adc, uint8_t sps_adc)
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


float get_read_adc(uint8_t channel_adc, uint16_t pga_adc, uint8_t sps_adc)
{
	float val = 0.0f;
	uint16_t mode = mode_conf(channel_adc, pga_adc, sps_adc);
	uint8_t buff[2] = {(mode >> 8) & 0xFF, mode & 0xFF};
	uint8_t buff_rx[2] = {0};
	i2c_write_data(_DEVICE_ADDRESS, _REG_ADS1115_ADDRESS_POINTER_CONFIG, buff, 2);
	i2c_read_data(_DEVICE_ADDRESS, _REG_ADS1115_POINTER_CONVERSION, buff_rx, 2);
	val = (buff_rx[0] << 8) | (buff_rx[1]);
	if (val > 0x7FFF)
	{
		return (val - 0xFFFF) * pga_adc / 32768.0f;
	}
	else
	{
		return ((buff_rx[0] << 8) | (buff_rx[1])) * pga_adc / 32768.0f;
	}
}

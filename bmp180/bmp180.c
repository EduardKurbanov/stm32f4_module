/*
 * bmp180.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#include "bmp180_defs.h"
#include "bmp180.h"


// Defines according to the datsheet
short AC1 = 0;
short AC2 = 0;
short AC3 = 0;
unsigned short AC4 = 0;
unsigned short AC5 = 0;
unsigned short AC6 = 0;
short B1 = 0;
short B2 = 0;
short MB = 0;
short MC = 0;
short MD = 0;

/********************/
long UT = 0;
short oss = 0;
long UP = 0;
long X1 = 0;
long X2 = 0;
long X3 = 0;
long B3 = 0;
long B5 = 0;
unsigned long B4 = 0;
long B6 = 0;
unsigned long B7 = 0;

/*******************/
long Press = 0L;
long Temp_long = 0L;
float Temp_float = 0.0F;
float Alt = 0.0f;


//--------------------------------------------------------------------------------------------------
static uint8_t i2c_write_data(uint8_t MemAddress, uint8_t *pData, uint8_t Size)
{
	return HAL_I2C_Mem_Write(_BMP180_I2C, _BMP180_DEVICE_ADDRESS << 1, MemAddress, 1U, pData, Size, 1000);
}
//--------------------------------------------------------------------------------------------------
static uint8_t i2c_read_data(uint8_t MemAddress, uint8_t* pData, uint8_t Size)
{
	return HAL_I2C_Mem_Read(_BMP180_I2C, _BMP180_DEVICE_ADDRESS << 1, MemAddress, 1U, pData, Size, 1000);
}
//--------------------------------------------------------------------------------------------------
static void read_calliberation_data (void)
{
	uint8_t Callib_Data[22] = {0};
	uint16_t Callib_Start = _BMP180_CALIB0;
	i2c_read_data(Callib_Start, Callib_Data, 22U);

	AC1 = ((Callib_Data[0] << 8) | Callib_Data[1]);
	AC2 = ((Callib_Data[2] << 8) | Callib_Data[3]);
	AC3 = ((Callib_Data[4] << 8) | Callib_Data[5]);
	AC4 = ((Callib_Data[6] << 8) | Callib_Data[7]);
	AC5 = ((Callib_Data[8] << 8) | Callib_Data[9]);
	AC6 = ((Callib_Data[10] << 8) | Callib_Data[11]);
	B1 = ((Callib_Data[12] << 8) | Callib_Data[13]);
	B2 = ((Callib_Data[14] << 8) | Callib_Data[15]);
	MB = ((Callib_Data[16] << 8) | Callib_Data[17]);
	MC = ((Callib_Data[18] << 8) | Callib_Data[19]);
	MD = ((Callib_Data[20] << 8) | Callib_Data[21]);

}
//--------------------------------------------------------------------------------------------------
// Get uncompensated Temp
static uint16_t Get_UTemp (void)
{
	uint8_t datatowrite = _BMP180_SET_TEMP_CONV;
	uint8_t Temp_RAW[2] = {0};
	i2c_write_data(_BMP180_CTRL_MEAS, &datatowrite, 1U);
	HAL_Delay (_BMP180_TEMP_CONV_TIME);  // wait 4.5 ms
	i2c_read_data(_BMP180_OUT_MSB, Temp_RAW, 2U);
	return ((Temp_RAW[0] << 8) + Temp_RAW[1]);
}
//--------------------------------------------------------------------------------------------------
float bmp180_get_temp (void)
{
	UT = Get_UTemp();
	X1 = ((UT - AC6) * (AC5 / (pow(2,15))));
	X2 = ((MC * (pow(2,11))) / (X1 + MD));
	B5 = X1 + X2;
	Temp_long = (B5 + 8) / (pow(2,4));
	Temp_float = Temp_long / 10.0;

	if (Temp_float < _BMP180_MIN_TEMP_THRESHOLD)
	{
		return -1000;
	}
	else if (Temp_float > _BMP180_MAX_TEMP_THRESHOLD)
	{
		return 1000;
	}
	else
	{
	    return Temp_float;
	}
}
//--------------------------------------------------------------------------------------------------
// Get uncompensated Pressure
static uint32_t Get_UPress (int oss)   // oversampling setting 0,1,2,3
{
	uint8_t datatowrite = _BMP180_SET_PRESS_CONV + (oss << 6);
	uint8_t Press_RAW[3] = {0};
	i2c_write_data(_BMP180_CTRL_MEAS, &datatowrite, 1U);
	switch (oss)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	i2c_read_data(_BMP180_OUT_MSB, Press_RAW, 3U);
	return (((Press_RAW[0] << 16) + (Press_RAW[1] << 8)+Press_RAW[2]) >> (8 - oss));
}
//--------------------------------------------------------------------------------------------------
float bmp180_get_press (int oss)
{
	UT = Get_UTemp();
	UP = Get_UPress(oss);
	X1 = ((UT - AC6) * (AC5 / (pow(2,15))));
	X2 = ((MC * (pow(2,11))) / (X1 + MD));
	B5 = X1 + X2;
	B6 = B5 - 4000;
	X1 = (B2 * (B6 * B6 / (pow(2,12)))) / (pow(2,11));
	X2 = AC2 * B6 / (pow(2,11));
	X3 = X1 + X2;
	B3 = (((AC1 * 4 + X3) << oss) + 2) / 4;
	X1 = AC3 * B6 / pow(2,13);
	X2 = (B1 * (B6 * B6 / (pow(2,12)))) / (pow(2,16));
	X3 = ((X1 + X2) + 2) / pow(2,2);
	B4 = AC4 * (unsigned long)(X3 + 32768) / (pow(2,15));
	B7 = ((unsigned long)UP - B3) * (50000 >> oss);
	if (B7 < 0x80000000) Press = (B7 * 2) / B4;
	else Press = (B7 / B4) * 2;
	X1 = (Press / (pow(2,8))) * (Press / (pow(2,8)));
	X1 = (X1 * 3038) / (pow(2,16));
	X2 = (-7357 * Press) / (pow(2,16));
	Press = Press + (X1 + X2 + 3791) / (pow(2,4));

	return Press;
}
//--------------------------------------------------------------------------------------------------
float bmp180_get_convert_press_in_millimeter_of_mercury(int oss)
{
	Press = bmp180_get_press(oss);
	return Press * _BMP180_CONST_1Pa_in_mmHg;
}
//--------------------------------------------------------------------------------------------------
float bmp180_get_alt(int oss)
{
	Press = bmp180_get_press(oss);
	Alt = _BMP180_PRESS_CONST_COEFICIENT * (1 - (pow(((float)Press / (float)_BMP180_PRESS_CONST_SEA_LEVEL), (1 / 5.255))));
	if (Alt < _BMP180_MIN_ALT_THRESHOLD)
	{
		return -10000;
	}
	else if (Alt > _BMP180_MAX_ALT_THRESHOLD)
	{
		return 10001;
	}
	else
	{
		return Alt;
	}
}
//--------------------------------------------------------------------------------------------------
void bmp180_start (void)
{
	read_calliberation_data();
}
//--------------------------------------------------------------------------------------------------

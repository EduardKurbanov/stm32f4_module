/*
 * bmp180.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef BMP180_H
#define BMP180_H


#include "i2c.h"
#include <inttypes.h>
#include <math.h>

#define _BMP180_DEVICE_ADDRESS         0x77
#define _BMP180_I2C                    &hi2c1


void bmp180_start (void);

float bmp180_get_temp (void);

float bmp180_get_press (int oss);

float bmp180_get_convert_press_in_millimeter_of_mercury (int oss);

float bmp180_get_alt (int oss);


#endif

/*
#include "bmp180.h"

float alt = 0.0f;
float pre = 0.0f;
float temp = 0.0f;
float mmhg = 0.0f;

int main(void)
{
	bmp180_start (void);

	while (1)
	{
		temp = bmp180_start();
		pre = bmp180_get_press(0);
		alt = bmp180_get_alt(0);
		mmhg = BMP180_GetConvertPressInMillimeterOfMercury(0);
	}
}
*/

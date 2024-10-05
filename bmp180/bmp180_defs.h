/*
 * bmp180_defs.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef BMP180_DEFS_H
#define BMP180_DEFS_H


//Global Memory Map
#define _BMP180_OUT_XLSB                        0xF8
#define _BMP180_OUT_LSB                         0xF7
#define _BMP180_OUT_MSB                         0xF6
#define _BMP180_CTRL_MEAS                       0xF4
#define _BMP180_SOFT_RESET                      0xE0
#define _BMP180_ID                              0xD0
#define _BMP180_CALIB21                         0xBF
#define _BMP180_CALIB0                          0xAA

// Temp. measurement :
#define _BMP180_SET_TEMP_CONV		            0x2E

#define _BMP180_TEMP_CONV_TIME					5U
#define _BMP180_MIN_TEMP_THRESHOLD				-40
#define _BMP180_MAX_TEMP_THRESHOLD				85U

// Pressure measurment :
#define _BMP180_SET_PRESS_CONV		            0x34
#define _BMP180_PRESS_CONST_SEA_LEVEL 	    	101325.0f // pressure in Pa
#define _BMP180_PRESS_CONST_COEFICIENT 	    	44330.0f
#define _BMP180_CONST_1Pa_in_mmHg               0.007500637554192f // coefficient mmHg

// Altitude measurment :
#define _BMP180_MIN_ALT_THRESHOLD			   -500	// m. relating to sea level)
#define _BMP180_MAX_ALT_THRESHOLD				9000U	// m. relating to sea level)


#endif

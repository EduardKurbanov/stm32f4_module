/*
 * ds3231.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef DS3231_H
#define DS3231_H


#include "i2c.h"
#include <inttypes.h>
#include <windows.h>

#define _DS3231_DEVICE_ADDRESS 	    0x68
#define _BUS_HANDLER                &hi2c1

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;

typedef enum
{
	E_OK_DS3231 = 100,
	E_ERROR_DS3231 = 200,
}E_DS3231_STATUS;

extern TIME time;

void ds3231_status_i2c(E_DS3231_STATUS* error_ds3231);
void ds3231_set_time_auto_windows(void);
void ds3231_set_time_manual(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void ds3231_get_time(void);
float ds3231_get_temp(void);
void ds3231_force_temp_conv(void);


#endif

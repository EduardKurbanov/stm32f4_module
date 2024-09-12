/*
 * ds3231_defs.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef DS3231_DEFS_H
#define DS3231_DEFS_H

	
#define _DS3231_REG_SECOND 	    0x00
#define _DS3231_REG_MINUTE 	    0x01
#define _DS3231_REG_HOUR  	    0x02
#define _DS3231_REG_DOW    	    0x03
							    
#define _DS3231_REG_DATE   	    0x04
#define _DS3231_REG_MONTH  	    0x05
#define _DS3231_CENTURY 		7
#define _DS3231_REG_YEAR   	    0x06
							    
#define _DS3231_A1_SECOND	    0x07
#define _DS3231_A1_MINUTE	    0x08
#define _DS3231_A1_HOUR		    0x09
#define _DS3231_A1_DATE		    0x0A
							    
#define _DS3231_A2_MINUTE	    0x0B
#define _DS3231_A2_HOUR		    0x0C
#define _DS3231_A2_DATE		    0x0D
							    
#define _DS3231_REG_CONTROL 	0x0E
#define _DS3231_EOSC			7
#define _DS3231_BBSQW		    6
#define _DS3231_CONV			5
#define _DS3231_RS2			    4
#define _DS3231_RS1			    3
#define _DS3231_INTCN		    2
#define _DS3231_A2IE			1
#define _DS3231_A1IE			0
							    
#define _DS3231_REG_STATUS	    0x0F
#define _DS3231_OSF			    7
#define _DS3231_EN32KHZ		    3
#define _DS3231_BSY			    2
#define _DS3231_A2F			    1
#define _DS3231_A1F			    0
							    
#define _DS3231_AGING		    0x10
							    
#define _DS3231_TEMP_MSB		0x11
#define _DS3231_TEMP_LSB		0x12


#endif

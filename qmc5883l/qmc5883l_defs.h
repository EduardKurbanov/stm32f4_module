/*
 * qmc5883l_defs.c
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef QMC5883L_DEFS_H
#define QMC5883L_DEFS_H


#define _REG_QMC5883L_DATA_OUTPUT_X_LSB_L          0x00
#define _REG_QMC5883L_DATA_OUTPUT_X_MSB_H          0x01
#define _REG_QMC5883L_DATA_OUTPUT_Y_LSB_L          0x02
#define _REG_QMC5883L_DATA_OUTPUT_Y_MSB_H          0x03
#define _REG_QMC5883L_DATA_OUTPUT_Z_LSB_L          0x04
#define _REG_QMC5883L_DATA_OUTPUT_Z_MSB_H          0x05
#define _REG_QMC5886L_STATUS                       0x06
#define _REG_QMC5883L_TEMP_OUT_H                   0x08
#define _REG_QMC5883L_TEMP_OUT_L                   0x07
#define _REG_QMC5883L_CONF_1                       0x09
#define _REG_QMC5883L_CONF_2                       0x0A
#define _REG_QMC5883L_SET_RESET_PERIOD             0x0B
#define _REG_QMC5883L_RESERVED                     0x0C
#define _CHIP_ID                                   0x0D
											       
#define _REG_DATA_UPDATE_RATE_ODR_10HZ             0x00
#define _REG_DATA_UPDATE_RATE_ODR_50HZ             0x04
#define _REG_DATA_UPDATE_RATE_ODR_100HZ            0x08
#define _REG_DATA_UPDATE_RATE_ODR_200HZ            0x0C
#define _REG_OVERSAMPLING_OSR_64                   0xC0
#define _REG_OVERSAMPLING_OSR_128                  0x80
#define _REG_OVERSAMPLING_OSR_256                  0x40
#define _REG_OVERSAMPLING_OSR_512                  0x00
#define _REG_FULL_SCALE_RNG_2G                     0x00
#define _REG_FULL_SCALE_RNG_8G                     0x10
											       
#define _REG_MODE_CONTROL_STANDBY                  0x00
#define _REG_MODE_CONTROL_CONTINUOUS               0x01
//# Flags for Status Register #1.			       
#define _REG_STAT_DRDY                             0x01  //# Data Ready.
#define _REG_STAT_OVL                              0x02  //# Overflow flag.
#define _REG_STAT_DOR                              0x04  //# Data skipped for reading.
//# Flags for Status Register #2.			       
#define _REG_INT_ENB                               0x01  //# Interrupt Pin Enabling.
#define _REG_POL_PNT                               0x40  //# Pointer Roll - over.
#define _REG_SOFT_RST                              0x80  //# Soft Reset.

#define _FIELD_RANGE_SENSITIVITY_2G_12000LSB_G     12000
#define _FIELD_RANGE_SENSITIVITY_8G_3000LSB_G      3000
#define _TEMPERATURE_SENSOR_SENSITIVITY            100


#endif

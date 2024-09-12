/*
 * ads1115_defs.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef ADS1115_DEFS_H
#define ADS1115_DEFS_H


#define _REG_ADS1115_POINTER_CONVERSION                    0x00
#define _REG_ADS1115_ADDRESS_POINTER_CONFIG                0x01
#define _REG_ADS1115_POINTER_LOW_THRESHOLD                 0x02
#define _REG_ADS1115_POINTER_HIGH_THRESHOLD                0x03

#define _REG_ADS1115_CONFIG_OS_SINGLE                      0x8000

#define _REG_ADS1115_CONFIG_MUX_AINP_AIN0_and_AINN_AIN1    0x0000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN0_and_AINN_AIN3    0x1000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN1_and_AINN_AIN3    0x2000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN2_and_AINN_AIN3    0x3000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN0_and_AINN_GND     0x4000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN1_and_AINN_GND     0x5000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN2_and_AINN_GND     0x6000
#define _REG_ADS1115_CONFIG_MUX_AINP_AIN3_and_AINN_GND     0x7000

#define _REG_ADS1115_CONFIG_PGA_FSR__6_144V                0x0000
#define _REG_ADS1115_CONFIG_PGA_FSR__4_096V                0x0200
#define _REG_ADS1115_CONFIG_PGA_FSR__2_048V                0x0400
#define _REG_ADS1115_CONFIG_PGA_FSR__1_024V                0x0600
#define _REG_ADS1115_CONFIG_PGA_FSR__0_512V                0x0800
#define _REG_ADS1115_CONFIG_PGA_FSR__0_256V                0x0A00

#define _REG_ADS1115_CONFIG_MODE_SINGLE                    0x100
#define _REG_ADS1115_CONFIG_MODE_CONT                      0x0000

#define _REG_ADS1115_CONFIG_DR_8_SPS                       0x0000
#define _REG_ADS1115_CONFIG_DR_16_SPS                      0x0020
#define _REG_ADS1115_CONFIG_DR_32_SPS                      0x0040
#define _REG_ADS1115_CONFIG_DR_64_SPS                      0x0060
#define _REG_ADS1115_CONFIG_DR_128_SPS                     0x0080
#define _REG_ADS1115_CONFIG_DR_250_SPS                     0x00A0
#define _REG_ADS1115_CONFIG_DR_475_SPS                     0x00C0
#define _REG_ADS1115_CONFIG_DR_860_SPS                     0x00E0
 
#define _REG_ADS1115_COMP_MODE_TRAD                        0x00
#define _REG_ADS1115_COMP_MODE_WINDOWS                     0x10

#define _REG_ADS1115_COMP_POL_ACTIVE_LOW                   0x00
#define _REG_ADS1115_COMP_POL_ACTIVE_HIGH                  0x08

#define _REG_ADS1115_COMP_NON_LAT                          0x0000
#define _REG_ADS1115_COMP_LAT                              0x0004

#define _REG_ADS1115_COMP_QUE_AFTER_1_CONVER               0x0000
#define _REG_ADS1115_COMP_QUE_AFTER_2_CONVER               0x0001
#define _REG_ADS1115_COMP_QUE_AFTER_3_CONVER               0x0002
#define _REG_ADS1115_COMP_QUE_DISABLE_CONVER               0x0003


#endif

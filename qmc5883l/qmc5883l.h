/*
 * qmc5883l.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef QMC5883L_H
#define QMC5883L_H

#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#define _DEVICE_ADDRESS              0x0D
#define _BUS_HANDLER                 &hi2c1

typedef enum
{
	E_OK_QMC = 100,
	E_ERROR_QMC = 200,
}E_QMC_STATUS;

void qmc5883l_init(void);
uint8_t qmc5883l_set_declination(float degrees);
void qmc5883l_set_calibration(float value[3][3]);
int16_t qmc5883l_get_magnetic_field_axis_x(void);
int16_t qmc5883l_get_magnetic_field_axis_y(void);
int16_t qmc5883l_get_magnetic_field_axis_z(void);
float qmc5883l_get_bearing_raw(void);
float qmc5883l_get_bearing(void);

#endif


/*
float k2g[3][3] = {{1.0086972793142255, -0.04161991734605183, 1788.4219998515782},
       {-0.04161991734605183, 1.1991677462926738, 586.365808229903},
                                                    {0.0, 0.0, 1.0}};

mag_declination = 8.22;

int main()
{
qmc5883l_init();
set_declination(mag_declination);
set_calibration(k2g);
while (1)
{
    printf("%f", get_bearing());
}
	return 0;
}
*/

#ifndef QMC5883L_H
#define QMC5883L_H

#include <math.h>
#include <inttypes.h>

void qmc5883l_init(void);
uint8_t set_declination(float degrees);
void set_calibration(float value[3][3]);
int16_t get_magnetic_field_axis_x(void);
int16_t get_magnetic_field_axis_y(void);
int16_t get_magnetic_field_axis_z(void);
float *get_magnet_field(void);
float get_bearing_raw(void);
float get_bearing(void);

#endif

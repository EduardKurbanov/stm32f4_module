/*
 * hy_srf05.h
 *
 *  Created on: Sep 3, 2024
 *      Author: Edward
 */

#ifndef HY_SRF05_H
#define HY_SRF05_H


#include <inttypes.h>
#include "tim.h"

//float sonar_hy_srf05(void);
void hy_srf05_init(void);
void hy_srf05_read(void);
uint16_t hy_srf05_distance(void);


#endif

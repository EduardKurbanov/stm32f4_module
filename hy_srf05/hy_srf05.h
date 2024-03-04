#ifndef HY_SRF05_H
#define HY_SRF05_H

#include "tim.h"

//float sonar_hy_srf05(void);
void hy_srf05_read(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void delay(uint16_t time);

#endif

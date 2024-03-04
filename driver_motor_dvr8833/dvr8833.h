#ifndef DVR8833_H
#define DVR8833_H


void driver_port_reset(void);
void driver_motor(E_MOTOR_COMMAND motorAction, E_MOTOR_STATUS *error_driver);

#endif
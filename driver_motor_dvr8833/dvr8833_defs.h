#ifndef DVR8833_DEFS_H
#define DVR8833_DEFS_H


#define ENGINE_STANDBY_PORT                     0
#define ENGINE_STANDBY_PORT_PIN                 0
#define ENGINE_RIGHT_MOVE_FORWARD_PORT          0
#define ENGINE_RIGHT_MOVE_FORWARD_PORT_PIN      0
#define ENGINE_RIGHT_MOVE_BACK_PORT             0
#define ENGINE_RIGHT_MOVE_BACK_PORT_PIN         0
#define ENGINE_LEFT_MOVE_FORWARD_PORT           0
#define ENGINE_LEFT_MOVE_FORWARD_PORT_PIN       0
#define ENGINE_LEFT_MOVE_BACK_PORT              0
#define ENGINE_LEFT_MOVE_BACK_PORT_PIN          0

typedef enum
{
	E_FORWARD = 1,
	E_BACK = 2,
	E_RIGHT = 3,
	E_LEFT = 4,
	E_STOP = 5,
}E_MOTOR_COMMAND;

typedef enum
{
	E_OK = 100,
	E_ERROR = 200,
}E_MOTOR_STATUS;


#endif
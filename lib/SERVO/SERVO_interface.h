#ifndef _SERVO_INTERFACE_H_
#define _SERVO_INTERFACE_H_

#include "Std_Types.h"
#include "BitMath.h"

#define SERVO_MOTOR_ANGLE_0 5
#define SERVO_MOTOR_ANGLE_90_VALUE 7.5
#define SERVO_MOTOR_ANGLE_90 7

#define SERVO_MOTOR_ANGLE_180 10

#define SERVO_MOTOR_FREQUENCY_HZ 50

void SERVO_voidInit(void);

void SERVO_voidMotorOn(u8 angle);

void SERVO_voidMotorOff(void);

#endif //_SERVO_INTERFACE_H_
#include "SERVO_interface.h"
#include "PWM_interface.h"
#include "DIO_interface.h"

void SERVO_voidInit(void)
{
    PWM_voidInitChannel1A();
}

void SERVO_voidMotorOn(u8 copy_u8Angle)
{
    switch (copy_u8Angle)
    {
    case SERVO_MOTOR_ANGLE_0:
        PWM_voidGenerateOnChannel1A(SERVO_MOTOR_FREQUENCY_HZ, SERVO_MOTOR_ANGLE_0, PWM_FREQ_DIV_BY_64);

        break;
    case SERVO_MOTOR_ANGLE_90:
        PWM_voidGenerateOnChannel1A(SERVO_MOTOR_FREQUENCY_HZ, SERVO_MOTOR_ANGLE_90_VALUE, PWM_FREQ_DIV_BY_64);

        break;
    case SERVO_MOTOR_ANGLE_180:
        PWM_voidGenerateOnChannel1A(SERVO_MOTOR_FREQUENCY_HZ, SERVO_MOTOR_ANGLE_180, PWM_FREQ_DIV_BY_64);

        break;

    default:
        break;
    }

}

void SERVO_voidMotorOff(void)
{
    PWM_voidStopTimer1A();
}
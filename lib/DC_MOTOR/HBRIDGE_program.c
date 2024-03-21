#include "HBRIDGE_interface.h"
#include "PWM_interface.h"

void HB_voidInit(u8 copy_MotorNumber)
{
#if (HBRIDGE_MODE == ETA32_HBRIDGE)

    DIO_voidSetPinDirection(HB_DIR_PORT, HB_DIR_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(HB_EN_PORT, HB_EN_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(HB_PWM_PORT, HB_PWM_PIN, DIO_PIN_OUTPUT);

#elif (HBRIDGE_MODE == HB_L298)
    switch (copy_MotorNumber)
    {
    case MOTOR1_INDEX:
        DIO_voidSetPinDirection(HB_DIR1_PORT, HB_DIR1_PIN, DIO_PIN_OUTPUT);
        DIO_voidSetPinDirection(HB_DIR2_PORT, HB_DIR2_PIN, DIO_PIN_OUTPUT);
        DIO_voidSetPinDirection(HB_EN1_PORT, HB_EN1_PIN, DIO_PIN_OUTPUT);
        break;

    case MOTOR2_INDEX:
        DIO_voidSetPinDirection(HB_DIR3_PORT, HB_DIR3_PIN, DIO_PIN_OUTPUT);
        DIO_voidSetPinDirection(HB_DIR4_PORT, HB_DIR4_PIN, DIO_PIN_OUTPUT);
        DIO_voidSetPinDirection(HB_EN2_PORT, HB_EN2_PIN, DIO_PIN_OUTPUT);
        break;

    default:
        break;
    }

#endif
}

void HB_voidMotorStart(u8 copy_u8Direction, u8 copy_MotorNumber)
{
#if (HBRIDGE_MODE == ETA32_HBRIDGE)
    DIO_voidSetPinValue(HB_EN_PORT, HB_EN_PIN, DIO_PIN_HIGH);

    if (copy_u8Direction == HB_CLOCKWISE)
    {
        DIO_voidSetPinValue(HB_EN_PORT, HB_EN_PIN, DIO_PIN_HIGH);
        DIO_voidSetPinValue(HB_DIR_PORT, HB_DIR_PIN, DIO_PIN_LOW);
    }
    else if (copy_u8Direction == HB_COUNTER_CLOCKWISE)
    {
        DIO_voidSetPinValue(HB_EN_PORT, HB_EN_PIN, DIO_PIN_HIGH);
        DIO_voidSetPinValue(HB_DIR_PORT, HB_DIR_PIN, DIO_PIN_HIGH);
    }
    else
    {
        // Error
    }

#elif (HBRIDGE_MODE == HB_L298)
    switch (copy_MotorNumber)
    {
    case MOTOR1_INDEX:
        DIO_voidSetPinValue(HB_EN1_PORT, HB_EN1_PIN, DIO_PIN_HIGH);
        if (copy_u8Direction == HB_CLOCKWISE)
        {
            DIO_voidSetPinValue(HB_DIR1_PORT, HB_DIR1_PIN, DIO_PIN_HIGH);
            DIO_voidSetPinValue(HB_DIR2_PORT, HB_DIR2_PIN, DIO_PIN_LOW);
        }
        else if (copy_u8Direction == HB_COUNTER_CLOCKWISE)
        {
            DIO_voidSetPinValue(HB_DIR1_PORT, HB_DIR1_PIN, DIO_PIN_LOW);
            DIO_voidSetPinValue(HB_DIR2_PORT, HB_DIR2_PIN, DIO_PIN_HIGH);
        }
        else
        {
            // Error
        }
        break;

    case MOTOR2_INDEX:
        DIO_voidSetPinValue(HB_EN2_PORT, HB_EN2_PIN, DIO_PIN_HIGH);
        if (copy_u8Direction == HB_CLOCKWISE)
        {
            DIO_voidSetPinValue(HB_DIR3_PORT, HB_DIR3_PIN, DIO_PIN_HIGH);
            DIO_voidSetPinValue(HB_DIR4_PORT, HB_DIR4_PIN, DIO_PIN_LOW);
        }
        else if (copy_u8Direction == HB_COUNTER_CLOCKWISE)
        {
            DIO_voidSetPinValue(HB_DIR3_PORT, HB_DIR4_PIN, DIO_PIN_LOW);
            DIO_voidSetPinValue(HB_DIR4_PORT, HB_DIR3_PIN, DIO_PIN_HIGH);
        }
        else
        {
            // Error
        }
        break;

    default:
        break;
    }

#endif
}

void HB_voidMotorStop(u8 copy_MotorNumber)
{
#if (HBRIDGE_MODE == ETA32_HBRIDGE)

    DIO_voidSetPinValue(HB_EN_PORT, HB_EN_PIN, DIO_PIN_LOW);

#elif (HBRIDGE_MODE == HB_L298)
    switch (copy_MotorNumber)
    {
    case MOTOR1_INDEX:
        DIO_voidSetPinValue(HB_EN1_PORT, HB_EN1_PIN, DIO_PIN_LOW);

        break;

    case MOTOR2_INDEX:
        DIO_voidSetPinValue(HB_EN2_PORT, HB_EN2_PIN, DIO_PIN_LOW);

        break;

    default:
        break;
    }

#endif
}

void HB_voidSetMotorSpeed(u8 copy_u8DutyCycle, u8 copy_u8PWMPrescaler, u8 copy_MotorNumber)
{
    switch (copy_MotorNumber)
    {
    case MOTOR1_INDEX:
        if (copy_u8DutyCycle <= 100)
        {
            PWM_voidInitChannel0();
            PWM_voidGenerateOnChannel0(copy_u8DutyCycle, copy_u8PWMPrescaler);
        }
        else
        {
            // Error
        }
        break;

    case MOTOR2_INDEX:
        if (copy_u8DutyCycle <= 100)
        {
            PWM_voidInitChannel0();
            PWM_voidGenerateOnChannel0(copy_u8DutyCycle, copy_u8PWMPrescaler);
        }
        else
        {
            // Error
        }
        break;

    default:
        break;
    }
}

#ifndef __HBRIDGE_CONFIG_H__
#define __HBRIDGE_CONFIG_H__

#include "DIO_interface.h"

#define ETA32_HBRIDGE 1
#define HB_L298 2
#define HB_L293 3

#define MOTOR1_INDEX 1
#define MOTOR2_INDEX 2

#define MOTOR_VOLTAGE   12V
#define LOGICAL_VOLTAGE   5V

#define HBRIDGE_MODE ETA32_HBRIDGE

#if (HBRIDGE_MODE == ETA32_HBRIDGE)

#define HB_DIR_PORT DIO_PORTB
#define HB_DIR_PIN DIO_PIN5

#define HB_EN_PORT DIO_PORTB
#define HB_EN_PIN DIO_PIN6

#define HB_PWM_PORT DIO_PORTB
#define HB_PWM_PIN DIO_PIN3

#elif (HBRIDGE_MODE == HB_L298)

#define HB_DIR1_PORT DIO_PORTB
#define HB_DIR1_PIN DIO_PIN0

#define HB_DIR2_PORT DIO_PORTB
#define HB_DIR2_PIN DIO_PIN1


#define HB_EN1_PORT DIO_PORTB
#define HB_EN1_PIN DIO_PIN3


//-------------------------


#define HB_DIR3_PORT DIO_PORTB
#define HB_DIR3_PIN DIO_PIN0

#define HB_DIR4_PORT DIO_PORTB
#define HB_DIR4_PIN DIO_PIN0


#define HB_EN2_PORT DIO_PORTB
#define HB_EN2_PIN DIO_PIN0

#elif (HBRIDGE_MODE == HB_L293)
/* pins for motor 1 */
/* pins for motor 2 */
#endif

#endif //__HBRIDGE_CONFIG_H__
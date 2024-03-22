#ifndef __PWM_INTERFACE_H__
#define __PWM_INTERFACE_H__

#include "PWM_config.h"

#define PWM_FREQ_DIV_BY_1 1
#define PWM_FREQ_DIV_BY_8 2
#define PWM_FREQ_DIV_BY_64 3
#define PWM_FREQ_DIV_BY_256 4
#define PWM_FREQ_DIV_BY_1024 5


/**
 * @return void
 * @brief : Initialize PWM module in timer 0
 */
void PWM_voidInitChannel0(void);

/**
 * @return void
 * @param : copy_u8DutyCycle      PWM duty cycle
 * @param : copy_u8PrescalerVal      PWM prescaler 
 * @brief : Generates PWM signal on OC0 pin with given duty cycle on 976Hz 
 */
void PWM_voidGenerateOnChannel0(u8 copy_u8DutyCycle, u8 copy_u8PrescalerVal);

/**
 * @return void
 * @brief Stops timer from working
 */
void PWM_voidStopTimer0(void);

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void PWM_voidStartTimer0(u8 copy_u8PrescalerVal);

//-------------------------------------//


/**
 * @return void
 * @brief : Initialize PWM module in timer 1
 */
void PWM_voidInitChannel1A(void);


/**
 * @return void
 * @param : copy_u16PWMFreqHZ      PWM frequency 
 * @param : copy_f32DutyCycle      PWM duty cycle 
 * @param : copy_u8PrescalerVal      PWM prescaler 
 * @brief : Generates PWM signal on OC1A pin with given duty cycle with specific frequency 
 */
void PWM_voidGenerateOnChannel1A(u16 copy_u16PWMFreqHZ, f32 copy_f32DutyCycle, u8 copy_u8PrescalerVal);

/**
 * @return void
 * @brief Stops timer from working
 */
void PWM_voidStopTimer1A(void);

/**
 * @return void
 * @param copy_u8PrescalerVal prescale Value from Defines
 * @brief start timer with specific prescale
 */
void PWM_voidStartTimer1A(u8 copy_u8PrescalerVal);


#endif //__PWM_INTERFACE_H__
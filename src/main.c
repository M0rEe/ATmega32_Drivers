#include <util/delay.h>
#include "DIO_interface.h"
#include "7SEGMENT_interface.h"
#include "LCD_interface.h"
#include "GLOBAL_INT.h"
#include "INT_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"
#include "TIMER0_interface.h"
#include "TIMER1_interface.h"
#include "PWM_interface.h"
#include "HBRIDGE_interface.h"
#include "SERVO_interface.h"
#include "WDT_interface.h"
#include "ICU_interface.h"

#include "BitMath.h"

#include "string.h"
/* Keypad Matrix */
u8 KeypadMatrix[4][4] = {
    {'7', '8', '9', '9'},
    {'4', '5', '6', '6'},
    {'1', '2', '3', '3'},
    {'*', '0', '#', '#'}};

/***
 * @return Value withen new range
 * @param X value to be mapped
 * @param in_min input range minimumm
 * @param in_max input range maximum
 * @param out_min output range minimum
 * @param out_max output range maximum
 *
 */
u16 map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max)
{
  return (u32)(x - in_min) * (u32)(out_max - out_min) / (u32)(in_max - in_min) + out_min;
}

void func(void)
{
  Tog_Bit(PORTA, PIN5);
}
u8 duty = 0;
u8 freq = 0;
extern volatile u8 State;
int main(void)
{
  /* Initialization seciton */
  DIO_voidInitPins();
  // Green led
  LCD_4_bit_voidInit();
  PWM_voidInitChannel0();
  PWM_voidGenerateOnChannel0(80, PWM_FREQ_DIV_BY_64);
  _delay_ms(2);
  ICU_voidInit();

  while (1)
  {
    ICU_voidGetDuty(&duty);
    ICU_voidGetFreqHz(&freq);
    LCD_4_bit_voidWriteStringAt((u8 *)"state :", 0, 0);
    LCD_4_bit_voidWriteInt(TCNT1);
    LCD_4_bit_voidWriteStringAt((u8 *)"freq :", 1, 0);
    LCD_4_bit_voidWriteInt(freq);
    _delay_ms(100);
    LCD_4_bit_voidSendCommand(_LCD_CLEAR);
    _delay_ms(2);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));

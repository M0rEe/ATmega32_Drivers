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
#include "PWM_interface.h"
#include "HBRIDGE_interface.h"
#include "BitMath.h"
#include "SERVO_interface.h"

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

int main(void)
{
  /* Initialization seciton */
  DIO_voidInitPins();
  LCD_4_bit_voidInit();
  SERVO_voidInit();
  // led on pin port
  // buzzer on pin port
  u8 KeyPressed = '-';
  u8 Trials = 3;
  u16 buffer = 0;
  u16 PassCode = 0;
  u16 Pass = 1234;
  u8 Printed = 0;
  u8 isFinished = 0;
  while (1)
  {
    while (Trials && isFinished == 0)
    {

      LCD_4_bit_voidWriteStringAt((u8 *)"Enter Passcode:", 0, 0);
      KEYPAD_voidGetCharBLOCKING(&KeyPressed, (u8 *)KeypadMatrix);

      if (KeyPressed >= '0' && KeyPressed <= '9')
      { // number
        buffer = (buffer * 10) + (KeyPressed - '0');
        // clearing before number if there where any
        LCD_4_bit_voidWriteStringAt((u8 *)"       ", 1, 0);
        LCD_4_bit_voidSetCursor(1, 0);
        LCD_4_bit_voidWriteInt(buffer);
      }
      else if (KeyPressed == '#')
      { // clear digit
        buffer /= 10;
        // clearing before number if there where any
        LCD_4_bit_voidWriteStringAt((u8 *)"      ", 1, 0);
        LCD_4_bit_voidSetCursor(1, 0);
        LCD_4_bit_voidWriteInt(buffer);
      }
      else if (KeyPressed == '*')
      { // accept the whole number
        PassCode = buffer;
        if (Pass == PassCode) // passcodes matches
        {
          Printed = 1;
          break;
        }
        else
        {
          Trials--;
        }
      }
      // invalidate the keypressed after useing it
      KeyPressed = '-';
    } // End of while(Trials)
    if (Trials > 0)
    {
      if (Printed == 1)
      {
        LCD_4_bit_voidSendCommand(_LCD_CLEAR);
        _delay_ms(2);
        LCD_4_bit_voidWriteStringAt((u8 *)"W PassCode", 2, 2);
        SERVO_voidMotorOn(SERVO_MOTOR_ANGLE_180);
        Printed = 0;
        isFinished = 1;
      }
    }
    else
    {
      LCD_4_bit_voidWriteStringAt((u8 *)"WRONGPASS!!", 3, 0);
      // light led
      DIO_voidSetPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_HIGH);
      // buzz buzzer
      DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);

      _delay_ms(2000);
      // light led
      DIO_voidSetPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_LOW);
      // buzz buzzer
      DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);
    }
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));

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
#include "UART_interface.h"

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

int main(void)
{
  /* Initialization seciton */
  DIO_voidInitPins();
  // Green led
  LCD_4_bit_voidInit();
  u8 ch[100];
  u8 state = 0;
  UART_voidInit(UART_9600_BAUD_RATE);

  while (1)
  {

    UART_voidStrIsReceived(&state);
    if (state == 1)
    {
      UART_voidReceiveStringNON_BLOCKING(ch);
      LCD_4_bit_voidWriteStringAt(ch, 1, 0);
    }else{
      LCD_4_bit_voidWriteChar('-');
    }
    _delay_ms(100);
  }

  return 0;
}

//! MANDATORY to stop compiler from optimizing isr and
//! save this function address into the vector table
// void __vector_2(void) __attribute__((signal));

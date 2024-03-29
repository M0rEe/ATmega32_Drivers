#include "7SEGMENT_interface.h"
#include "7SEGMENT_config.h"
#include <util/delay.h>
/**
 * @return void
 * @brief : Initialize 7Segment
 */
void SSD_voidInit(void)
{

#if BCD == ENABLED
    DIO_voidSetPinDirection(SSD_PIN0_PORT, SSD_PIN0, DIO_PIN_OUTPUT); // A
    DIO_voidSetPinDirection(SSD_PIN1_PORT, SSD_PIN1, DIO_PIN_OUTPUT); // B
    DIO_voidSetPinDirection(SSD_PIN2_PORT, SSD_PIN2, DIO_PIN_OUTPUT); // C
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN3, DIO_PIN_OUTPUT); // D
#else
    DIO_voidSetPinDirection(SSD_PIN0_PORT, SSD_PIN0, DIO_PIN_OUTPUT); // A
    DIO_voidSetPinDirection(SSD_PIN1_PORT, SSD_PIN1, DIO_PIN_OUTPUT); // B
    DIO_voidSetPinDirection(SSD_PIN2_PORT, SSD_PIN2, DIO_PIN_OUTPUT); // C
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN3, DIO_PIN_OUTPUT); // D
    DIO_voidSetPinDirection(SSD_PIN3_PORT, SSD_PIN4, DIO_PIN_OUTPUT); // E
    DIO_voidSetPinDirection(SSD_PIN4_PORT, SSD_PIN5, DIO_PIN_OUTPUT); // F
    DIO_voidSetPinDirection(SSD_PIN5_PORT, SSD_PIN6, DIO_PIN_OUTPUT); // G

#endif
    DIO_voidSetPinDirection(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_OUTPUT); // Enable
    DIO_voidSetPinDirection(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_OUTPUT); // Enable
}

/**
 * @return void
 * @param : copy_u8SSDindex            Index of 7segment display
 * @param : copy_u8Number              Number to be written
 * @brief : Wirite given number on 7segment
 */
void SSD_voidWriteNumber(u8 copy_u8SSDindex, u8 copy_u8Number)
{
    switch (copy_u8SSDindex)
    {
    case 1:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 2:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 3:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    case 4:
#if COMMON_ANODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_LOW); // Enable level for ANODE
#elif COMMON_CATHODE == ENABLED
        DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_HIGH); // Enable level for CATHODE
#endif
        break;

    default:
        break;
    }
#if BCD == ENABLED

    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN0, ((copy_u8Number >> 0) & 0x01)); // A
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN1, ((copy_u8Number >> 1) & 0x01)); // B
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN2, ((copy_u8Number >> 2) & 0x01)); // C
    DIO_voidSetPinValue(SSD_PIN3_PORT, SSD_PIN3, ((copy_u8Number >> 3) & 0x01)); // D

#else
    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN0, ((copy_u8Number >> 0) & 0x01)); // A
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN1, ((copy_u8Number >> 1) & 0x01)); // B
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN2, ((copy_u8Number >> 2) & 0x01)); // C
    DIO_voidSetPinValue(SSD_PIN3_PORT, SSD_PIN3, ((copy_u8Number >> 3) & 0x01)); // D
    DIO_voidSetPinValue(SSD_PIN0_PORT, SSD_PIN4, ((copy_u8Number >> 4) & 0x01)); // E
    DIO_voidSetPinValue(SSD_PIN1_PORT, SSD_PIN5, ((copy_u8Number >> 5) & 0x01)); // F
    DIO_voidSetPinValue(SSD_PIN2_PORT, SSD_PIN6, ((copy_u8Number >> 6) & 0x01)); // G

#endif
}

/**
 * @return void
 * @param : copy_u8SSDindex            Index of 7segment display
 * @param : copy_u8Number              Number to be written
 * @brief : Wirite given number on 7segment
 */
void SSD_voidWriteMultipleNumbers(u8 copy_u8num1, u8 copy_u8num2, u8 copy_u8num3, u8 copy_u8num4, u16 copy_u16SecondsDelay)
{
#if NUMBER_OF_SSDS == 4
    SSD_voidWriteNumber(1, copy_u8num1);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_LOW); // Disable
#endif

    /*************************/
    SSD_voidWriteNumber(2, copy_u8num2);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_LOW); // Disable
#endif

    /*************************/
    SSD_voidWriteNumber(3, copy_u8num3);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_LOW); // Disable
#endif
    /*************************/
    SSD_voidWriteNumber(4, copy_u8num4);
    _delay_us(copy_u16SecondsDelay);
    DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_HIGH); // Disable

#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE3_PORT, SSD_ENABLE3_PIN, DIO_PIN_LOW); // Disable
#endif

#elif NUMBER_OF_SSDS == 3
    SSD_voidWriteNumber(1, copy_u8num1);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_LOW); // Disable
#endif

    /*************************/
    SSD_voidWriteNumber(2, copy_u8num2);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_LOW); // Disable
#endif

    /*************************/
    SSD_voidWriteNumber(3, copy_u8num3);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE2_PORT, SSD_ENABLE2_PIN, DIO_PIN_LOW); // Disable
#endif
    /*************************/

#elif NUMBER_OF_SSDS == 2
    SSD_voidWriteNumber(1, copy_u8num1);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE0_PORT, SSD_ENABLE0_PIN, DIO_PIN_LOW); // Disable
#endif

    /*************************/
    SSD_voidWriteNumber(2, copy_u8num2);
    _delay_us(copy_u16SecondsDelay);
#if COMMON_ANODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_HIGH); // Disable
#elif COMMON_CATHODE == ENABLED
    DIO_voidSetPinValue(SSD_ENABLE1_PORT, SSD_ENABLE1_PIN, DIO_PIN_LOW); // Disable
#endif

#endif
}
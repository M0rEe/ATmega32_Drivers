#include "TIMER1_config.h"
#include "TIMER1_interface.h"

void TIMER1_voidInit(u8 copy_u8PrescalerValue)
{

    // Disable Module
    TIMER1_voidStopTimer();
// Select mode
#if (TIMER1_MODE == TIMER1_NOMRAL_MODE)

    Clr_Bit(TCCR1A, WGM10);
    Clr_Bit(TCCR1A, WGM11);
    Clr_Bit(TCCR1A, WGM12);
    Clr_Bit(TCCR1A, WGM13);
    // Enable interrupt
    TIMER1_OVER_FLOW_INTERRUPT_ENABLE();

#elif (TIMER1_MODE == TIMER1_CTC_MODE)

    Clr_Bit(TCCR1A, WGM10);
    Clr_Bit(TCCR1A, WGM11);
    Set_Bit(TCCR1A, WGM12);
    Clr_Bit(TCCR1A, WGM13);44
    // Enable interrupt
    TIMER1_OUTPUT_COMPARE_MATCH_A_INTERRUPT_ENABLE();

#endif

    // Select clock and start timer
    TIMER1_voidStartTimer(copy_u8PrescalerValue);
}

void TIMER1_voidStartTimer(u8 copy_u8PrescalerValue)
{
    TIMER1_voidStopTimer();
    switch (copy_u8PrescalerValue)
    {
    case TIMER1_FREQ_DIV_BY_1:
        Set_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case TIMER1_FREQ_DIV_BY_8:
        Clr_Bit(TCCR1B, CS10);
        Set_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case TIMER1_FREQ_DIV_BY_64:
        Set_Bit(TCCR1B, CS10);
        Set_Bit(TCCR1B, CS11);
        Clr_Bit(TCCR1B, CS12);
        break;

    case TIMER1_FREQ_DIV_BY_256:
        Clr_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Set_Bit(TCCR1B, CS12);
        break;

    case TIMER1_FREQ_DIV_BY_1024:
        Set_Bit(TCCR1B, CS10);
        Clr_Bit(TCCR1B, CS11);
        Set_Bit(TCCR1B, CS12);
        break;

    default:
        break;
    }
}

void TIMER1_voidStopTimer(void)
{

    Clr_Bit(TCCR1A, COM1A0);
    Clr_Bit(TCCR1A, COM1A1);

    Clr_Bit(TCCR1A, COM1B0);
    Clr_Bit(TCCR1A, COM1B1);
}

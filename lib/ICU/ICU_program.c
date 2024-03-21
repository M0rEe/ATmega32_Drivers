#include "ICU_interface.h"
#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "GLOBAL_INT.h"
#include "avr/interrupt.h"
#include "avr/io.h"

volatile static u8 State = 0;

volatile static u8 Counter = 0;

volatile static u8 TimeOn = 0;
volatile static u8 OnCount = 0;

volatile static u8 TotalTime = 0;
volatile static u8 TotalCount = 0;

void ICU_voidInit(void)
{
    DIO_voidSetPinDirection(ICU_PORT_INDEX, ICU_PIN_INDEX, DIO_PIN_INPUT);
    // Timer1 config to normal mode
    TIMER1_voidInit(TIMER1_FREQ_DIV_BY_64);
    // Select Edge to be detected
#if (ICU_SELECTED_EDGE == ICU_RISING_EDGE_MODE)
    Set_Bit(TCCR1B, ICES1);

#elif (ICU_SELECTED_EDGE == ICU_FALLING_EDGE_MODE)
    Clr_Bit(TCCR1B, ICES1);

#endif

    // Enable ICU interrupt
    Set_Bit(TIMSK, TICIE1);
    // Enable Global interrupt
    SET_GLOBAL_INTERRUPT();
}

void ICU_voidGetFreqHz(u8 *copy_u8FreqPtr)
{
    // TODO handle both modes equations uptill now only on shot mode is handled

#if (ICU_SELECTED_EDGE == ICU_RISING_EDGE_MODE)
    *copy_u8FreqPtr = ICU_1_MILLION_MICRO_TIME_STAMP / ((TotalTime + (u32)(ICU_TIMER1_MAX * TotalCount)) * 4);
    State++;
#elif (ICU_SELECTED_EDGE == ICU_FALLING_EDGE_MODE)

#endif
}
void ICU_voidGetDuty(u8 *copy_u8DutyPtr)
{
    // TODO handle both modes equations uptill now only on shot mode is handled

#if (ICU_SELECTED_EDGE == ICU_RISING_EDGE_MODE)
    *copy_u8DutyPtr = (TimeOn + (u32)(ICU_TIMER1_MAX * OnCount)) / (TotalTime + (u32)(ICU_TIMER1_MAX * TotalCount));
    State++;
#elif (ICU_SELECTED_EDGE == ICU_FALLING_EDGE_MODE)

#endif
}

ISR(TIMER1_CAPT_vect)
{
    Set_Bit(PORTA,PIN5);

    switch (State)
    {
    case 0: // First Edge detected
        TCNT1 = 0;
        ICR1 = 0;
        Counter = 0;
// Select Next Edge
// TODO handle both edges equations uptill now only rising handled
#if (ICU_SELECTED_EDGE == ICU_RISING_EDGE_MODE)
        Clr_Bit(TCCR1B, ICES1);

#elif (ICU_SELECTED_EDGE == ICU_FALLING_EDGE_MODE)
        Set_Bit(TCCR1B, ICES1);
#endif
        State++;
        break;

    case 1: // Secound Edge Detected
        TimeOn = ICR1;
        OnCount = Counter;
        // Select Next Edge
// TODO handle both edges equations uptill now only rising handled
#if (ICU_SELECTED_EDGE == ICU_RISING_EDGE_MODE)
        Set_Bit(TCCR1B, ICES1);

#elif (ICU_SELECTED_EDGE == ICU_FALLING_EDGE_MODE)
        Clr_Bit(TCCR1B, ICES1);

#endif
        State++;
        break;

    case 2: // Last Edge of the clock to be detected
        TotalTime = ICR1;
        TotalCount = Counter;
        // Select Next Edge
// TODO handle both modes equations uptill now only on shot mode is handled
#if (ICU_CONTINIOUS_MODE == ICU_ONE_SHOT_MODE_SELECTED)
        TIMER1_voidStopTimer();

#elif (ICU_CONTINIOUS_MODE == ICU_CONT_MODE_SELECTED)

#endif
        State++;
        break;

    default:
        break;
    }
}
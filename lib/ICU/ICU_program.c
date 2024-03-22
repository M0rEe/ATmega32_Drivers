#include "ICU_interface.h"
#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "GLOBAL_INT.h"
#include "avr/interrupt.h"
#include "avr/io.h"

volatile u8 State = 0;

volatile static u8 Counter = 0;

volatile static u8 TimeOn = 0;
volatile static u8 OnCount = 0;

volatile static u8 TotalTime = 0;
volatile static u8 TotalCount = 0;

void ICU_voidInit(void)
{
    RESET_GLOBAL_INTERRUPT();
    DIO_voidSetPinDirection(ICU_PORT_INDEX, ICU_PIN_INDEX, DIO_PIN_INPUT);
    // Timer1 config to normal mode
    TIMER1_voidInit(TIMER1_FREQ_DIV_BY_64);
    // Select Edge to be detected
    Set_Bit(TCCR1B, ICES1);
    // Enable ICU interrupt
    Set_Bit(TIMSK, TICIE1);
    // Enable Global interrupt
    SET_GLOBAL_INTERRUPT();
}

void ICU_voidGetFreqHz(u8 *copy_u8FreqPtr)
{
    // TODO handle both modes equations uptill now only on shot mode is handled
    if (State > 2)
    {
        *copy_u8FreqPtr = ICU_1_MILLION_MICRO_TIME_STAMP / ((TotalTime + (u32)(ICU_TIMER1_MAX * TotalCount)) * 4);
        State++;
    }
}
void ICU_voidGetDuty(u8 *copy_u8DutyPtr)
{
    // TODO handle both modes equations uptill now only on shot mode is handled
    if (State > 2)
    {
        *copy_u8DutyPtr = (TimeOn + (u32)(ICU_TIMER1_MAX * OnCount)) / (TotalTime + (u32)(ICU_TIMER1_MAX * TotalCount));
        State++;
    }
}

ISR(TIMER1_CAPT_vect)
{

    if (State == 0)
    {
        // First Edge detected
        State = 1;
        TCNT1 = 0;
        ICR1 = 0;
        Counter = 0;
// Select Next Edge
// TODO handle both edges equations uptill now only rising handled
        Clr_Bit(TCCR1B, ICES1);
    }
    else if (State == 1) // Secound Edge Detected
    {
        State = 2;
        TimeOn = ICR1;
        OnCount = Counter;
        // Select Next Edge
// TODO handle both edges equations uptill now only rising handled
        Set_Bit(TCCR1B, ICES1);
    }
    else if (State == 2) // Last Edge of the clock to be detected
    {
        State = 3;
        TotalTime = ICR1;
        TotalCount = Counter;
        // Select Next Edge
// TODO handle both modes equations uptill now only on shot mode is handled
        TIMER1_voidStopTimer();
    }
}

ISR(TIMER0_OVF_vect)
{
    Counter++;
}
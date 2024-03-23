#include "UART_interface.h"
#include "BitMath.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "GLOBAL_INT.h"
#include "LCD_interface.h"

static u8 PRV_TXArr[UART_MAX_BUFFER_SIZE];
static u8 PRV_TXIdx = 0;

static u8 PRV_RXArr[UART_MAX_BUFFER_SIZE];
static u8 PRV_RXIdx = 0;

static u8 PRV_RXStrComplete = 0;

void UART_voidInit(u32 copy_u32BaudRate)
{

    // Enable Transmite and Receive
    Set_Bit(UCSRB, TXEN);
    Set_Bit(UCSRB, RXEN);

    // BaudRate Select
    switch (copy_u32BaudRate)
    {
    case UART_9600_BAUD_RATE:
        UBRRL = UART_9600_BAUD_RATE_UBRRL_VALUE;
        break;
    case UART_115200_BAUD_RATE:
        UBRRL = UART_115200_BAUD_RATE_UBRRL_VALUE;
        break;

    default:
        break;
    }
    // Select AsyncMode
    Set_Bit(UCSRC, URSEL);
#if (UART_MODE == UART_ASYNC_MDOE)
    Clr_Bit(UCSRC, UMSEL);
#elif (UART_MODE == UART_SYNC_MDOE)
    Set_Bit(UCSRC, UMSEL);
    // Polarity if Synchronous only
    Set_Bit(UCSRC, UCPOL);
#endif
// No Parity
#if (UART_PARITY_MODE == UART_WITH_PARITY_MODE)
    Clr_Bit(UCSRC, UPM0);
    Clr_Bit(UCSRC, UPM1);
#elif (UART_PARITY_MODE == UART_WITH_ODD_PARITY_MODE)
    Set_Bit(UCSRC, UPM0);
    Set_Bit(UCSRC, UPM1);
#elif (UART_PARITY_MODE == UART_WITH_EVEN_PARITY_MODE)
    Clr_Bit(UCSRC, UPM0);
    Set_Bit(UCSRC, UPM1);
#endif
// 1 Stop bit
#if (UART_STOP_BITS_MODE == UART_ONE_STOP_MODE)
    Clr_Bit(UCSRC, USBS);
#elif (UART_STOP_BITS_MODE == UART_ONE_STOP_MODE)
    Set_Bit(UCSRC, USBS);
#endif

    // Frame Size
    Set_Bit(UCSRC, UCSZ0);
    Set_Bit(UCSRC, UCSZ1);
    Clr_Bit(UCSRB, UCSZ2);

    // TODO ENABLE GLOBAL INTERRUPT and PERIHERAL INTERRUPT
    SET_GLOBAL_INTERRUPT();
    Set_Bit(UCSRB, RXCIE);
    Set_Bit(UCSRB, TXCIE);
}

void UART_voidSendByteBLOCKING(u8 copy_u8SentByte)
{
    while (UART_SEND_BUFFER_EMPTY != Get_Bit(UCSRA, UDRE))
        ;
    UDR = copy_u8SentByte;
}

void UART_voidSendStringBLOCKING(u8 *copy_u8PtrSentString)
{
    while (*copy_u8PtrSentString != '\0')
    {
        UART_voidSendByteBLOCKING(*copy_u8PtrSentString);
        copy_u8PtrSentString++;
    }
}

void UART_voidSendStringNON_BLOCKING(u8 *copy_u8PtrString)
{
    while (copy_u8PtrString[PRV_TXIdx] != '\0')
    {
        PRV_TXArr[PRV_TXIdx] = copy_u8PtrString[PRV_TXIdx];
    }
    UART_voidSendByteBLOCKING(*copy_u8PtrString);
}

void UART_voidReceiveByteBLOCKING(u8 *copy_u8PtrRecevieByte)
{
    while (UART_DATA_RECEVIED != Get_Bit(UCSRA, RXC))
        ;
    *copy_u8PtrRecevieByte = UDR;
}

void UART_voidReceiveStringBLOCKING(u8 *copy_u8PtrRecevieString)
{
    UART_voidReceiveByteBLOCKING(copy_u8PtrRecevieString);
    while (*copy_u8PtrRecevieString != '\0')
    {
        UART_voidReceiveByteBLOCKING(copy_u8PtrRecevieString);
    }
}

void UART_voidReceiveStringNON_BLOCKING(u8 copy_u8PtrRecevieString[100])
{
    u8 i = 0;
    for (i = 0; (i < UART_MAX_BUFFER_SIZE) && (PRV_RXArr[i] != UART_DELEMITER); i++)
    {
        copy_u8PtrRecevieString[i] = PRV_RXArr[i];
    }
}

void UART_voidStrIsReceived(u8 *copy_u8PtrBool)
{
    if (PRV_RXStrComplete)
    {
        *copy_u8PtrBool = 1;
        PRV_RXStrComplete = 0;
    }
    else
    {
        *copy_u8PtrBool = 0;
    }
}

ISR(USART_TXC_vect)
{
    PRV_TXIdx++;
    if (PRV_TXArr[PRV_TXIdx] != '\0')
    {
        UDR = PRV_TXArr[PRV_TXIdx];
    }
    else
    {
        PRV_TXIdx = 0;
    }
}

ISR(USART_RXC_vect)
{
    PRV_RXArr[PRV_RXIdx] = UDR;
    if (PRV_RXArr[PRV_RXIdx] == UART_DELEMITER)
    {
        PRV_RXArr[PRV_RXIdx] = '\0';
        PRV_RXIdx = 0;
        PRV_RXStrComplete = 1;
    }
    else
    {
        PRV_RXIdx++;
    }
}
#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__

#include "Std_Types.h"
#include "UART_config.h"

void UART_voidInit(u32 copy_u16BaudRate);

void UART_voidSendByteBLOCKING(u8 copy_u8SentByte);
void UART_voidSendStringNON_BLOCKING(u8 *copy_u8PtrString);
void UART_voidSendStringBLOCKING(u8 *copy_u8PtrSentString);

void UART_voidReceiveByteNON_BLOCKING(u8 *copy_u8PtrRecevieByte);
void UART_voidReceiveByteBLOCKING(u8 *copy_u8PtrRecevieByte);
void UART_voidReceiveStringBLOCKING(u8 *copy_u8PtrRecevieString);
void UART_voidReceiveStringNON_BLOCKING(u8 copy_u8PtrRecevieString[]);

void UART_voidStrIsReceived(u8 *copy_u8PtrBool);
#endif // __UART_INTERFACE_H__

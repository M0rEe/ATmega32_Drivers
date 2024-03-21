#ifndef _WDT_INTERFACE_H_
#define _WDT_INTERFACE_H_

#include "Std_Types.h"
#include "BitMath.h"
#include "avr/io.h"

#define WDT_VCC_5V 1
#define WDT_VCC_3V3 2
#define WDT_WORKING_VCC WDT_VCC_5V

#if (WDT_WORKING_VCC == WDT_VCC_5V)
/*
#define WDT_TIMEOUT_16_3MS 0
#define WDT_TIMEOUT_32_5MS 1
#define WDT_TIMEOUT_65MS 2
#define WDT_TIMEOUT_0_13S 3
#define WDT_TIMEOUT_0_26S 4
#define WDT_TIMEOUT_0_52S 5
#define WDT_TIMEOUT_1_0MS 6
#define WDT_TIMEOUT_2_1MS 7

*/
typedef enum
{
    t16_3,
    WDT_timeout_16_3ms,
    WDT_timeout_32_5ms,
    WDT_timeout_65ms,
    WDT_timeout_0_13s,
    WDT_timeout_0_26s,
    WDT_timeout_0_52s,
    WDT_timeout_1s,
    WDT_timeout_2_1s
} WDT_timeout_t;

#elif (WDT_WORKING_VCC == WDT_VCC_3V3)
typedef enum
{
    t16_3,
    WDT_timeout_17_1ms,
    WDT_timeout_34_3ms,
    WDT_timeout_68_5ms,
    WDT_timeout_0_14s,
    WDT_timeout_0_27s,
    WDT_timeout_0_55s,
    WDT_timeout_1_1s,
    WDT_timeout_2_2s
} WDT_timeout_t;

#endif

void WDT_voidEnable(WDT_timeout_t copy_EnumWDTtimeout);
void WDT_voidDisable();
#endif //_WDT_INTERFACE_H_
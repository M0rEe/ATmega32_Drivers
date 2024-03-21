#include "WDT_interface.h"

void WDT_voidEnable(WDT_timeout_t copy_EnumWDTtimeout)
{
#if (WDT_WORKING_VCC == WDT_VCC_5V)
    switch (copy_EnumWDTtimeout)
    {
    case WDT_timeout_16_3ms:

        Clr_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_32_5ms:

        Set_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_65ms:

        Clr_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_13s:

        Set_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_26s:

        Clr_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_52s:

        Set_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_1s:

        Clr_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_2_1s:

        Set_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;

    default:
        break;
    }
#elif (WDT_WORKING_VCC == WDT_VCC_3V3)
    switch (copy_EnumWDTtimeout)
    {
    case WDT_timeout_17_1ms:

        Clr_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_34_3ms:

        Set_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_68_5ms:

        Clr_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_14s:

        Set_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Clr_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_27s:

        Clr_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_0_55s:

        Set_Bit(WDTCR, WDP0);
        Clr_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_1_1s:

        Clr_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;
    case WDT_timeout_2_2s:

        Set_Bit(WDTCR, WDP0);
        Set_Bit(WDTCR, WDP1);
        Set_Bit(WDTCR, WDP2);
        break;

    default:
        break;
    }
#endif
    // Enable
    Set_Bit(WDTCR, WDE);
}

void WDT_voidDisable(void)
{
    WDTCR |= (1 << WDTOE) | (1 << WDE);
    WDTCR = 0x00;
}
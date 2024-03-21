#ifndef _ICU_INTERFACE_H_
#define _ICU_INTERFACE_H_
#include "Std_Types.h"
#include "ICU_config.h"

void ICU_voidInit(void);
void ICU_voidGetFreqHz(u8 * copy_u8FreqPtr);
void ICU_voidGetDuty(u8 * copy_u8FreqPtr);

#endif //_ICU_INTERFACE_H_
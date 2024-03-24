#ifndef __EEPROM_INTERFACE_H__
#define __EEPROM_INTERFACE_H__

#include "Std_Types.h"
#include "BitMath.h"
#include "avr/io.h"
#define I2C_FIXED_ADDRESS_MASK 0b01010000

void EEPROM_voidInit(void);
void EEPROM_voidWriteByte(u16 copy_u16MemAddress , u8 copy_u8Data);
void EEPROM_voidReadByte(u16 copy_u16MemAddress , u8 *copy_pu8Data);
void EEPROM_voidWritePage(u16 copy_u16MemAddress , u8 copy_u8DataArr [16],u8 copy_u8DataSize);
void EEPROM_voidReadPage(u16 copy_u16MemAddress , u8 copy_u8DataArr [16],u8 copy_u8DataSize);

#endif // __EEPROM_INTERFACE_H__

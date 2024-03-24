#include "EEPROM_interface.h"
#include "I2C_interface.h"
#include "util/delay.h"

void EEPROM_voidInit(void)
{
    I2C_voidInitMaster();
}
void EEPROM_voidWriteByte(u16 copy_u16MemAddress, u8 copy_u8Data)
{

    u8 l_u8SlaveAddress = (u8)(I2C_FIXED_ADDRESS_MASK | (copy_u16MemAddress >> 8));

    I2C_voidSendStartCondition();

    I2C_voidSendSlaveAddWithWrite(l_u8SlaveAddress);

    I2C_voidTransmitMasterDataByte((u8)copy_u16MemAddress);

    I2C_voidTransmitMasterDataByte((u8)copy_u8Data);

    I2C_voidSendStopCondition();

    _delay_ms(5);
}

void EEPROM_voidReadByte(u16 copy_u16MemAddress, u8 *copy_pu8Data)
{
    if (NULL == copy_pu8Data)
    {
        // Error
    }
    else
    {

        u8 l_u8SlaveAddress = (u8)(I2C_FIXED_ADDRESS_MASK | (copy_u16MemAddress >> 8));

        I2C_voidSendStartCondition();

        I2C_voidSendSlaveAddWithWrite(l_u8SlaveAddress);

        I2C_voidTransmitMasterDataByte((u8)copy_u16MemAddress);

        I2C_voidSendRepeatedStartCondition();

        I2C_voidSendSlaveAddWithRead(l_u8SlaveAddress);

        I2C_voidReceiveMasterDataByteWithNack(copy_pu8Data);

        I2C_voidSendStopCondition();

        _delay_ms(5);
    }
}

void EEPROM_voidWritePage(u16 copy_u16MemAddress, u8 copy_u8DataArr[], u8 copy_u8DataSize)
{
    if (copy_u8DataArr == NULL || copy_u8DataSize > 16)
    {
        // Error
    }
    else
    {

        u8 l_u8SlaveAddress = (u8)(I2C_FIXED_ADDRESS_MASK | (copy_u16MemAddress >> 8));

        I2C_voidSendStartCondition();

        I2C_voidSendSlaveAddWithWrite(l_u8SlaveAddress);

        I2C_voidTransmitMasterDataByte((u8)copy_u16MemAddress);

        for (u8 i = 0; i < copy_u8DataSize; i++)
        {
            I2C_voidTransmitMasterDataByte((u8)copy_u8DataArr[i]);
        }

        I2C_voidSendStopCondition();

        _delay_ms(5);
    }
}

void EEPROM_voidReadPage(u16 copy_u16MemAddress, u8 copy_u8DataArr[16], u8 copy_u8DataSize)
{
    if (copy_u8DataArr == NULL || copy_u8DataSize > 16)
    {
        // Error
    }
    else
    {

        u8 l_u8SlaveAddress = (u8)(I2C_FIXED_ADDRESS_MASK | (copy_u16MemAddress >> 8));

        I2C_voidSendStartCondition();

        I2C_voidSendSlaveAddWithWrite(l_u8SlaveAddress);

        I2C_voidTransmitMasterDataByte((u8)copy_u16MemAddress);

        I2C_voidSendRepeatedStartCondition();

        I2C_voidSendSlaveAddWithRead(l_u8SlaveAddress);

        for (u8 i = 0; i < copy_u8DataSize - 1; i++)
        {
            I2C_voidReceiveMasterDataByteWithAck(&(copy_u8DataArr[i]));
        }

        I2C_voidReceiveMasterDataByteWithNack(&(copy_u8DataArr[copy_u8DataSize - 1]));

        I2C_voidSendStopCondition();

        _delay_ms(5);
    }
}
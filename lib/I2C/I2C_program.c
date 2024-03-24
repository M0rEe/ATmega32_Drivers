#include "I2C_interface.h"

void I2C_voidInitMaster(void)
{
    // Set Prescaller = 1 >> Set Freq. = 400KHZ
    TWBR = 12;
    Clr_Bit(TWSR, TWPS0);
    Clr_Bit(TWSR, TWPS1);

    // Enable TWI Peripheral
    Set_Bit(TWCR, TWEN);
}

void I2C_voidSendStartCondition(void)
{

    // Request Start Condition
    Set_Bit(TWCR, TWSTA);

    // Clear flag to start current job
    Set_Bit(TWCR, TWINT);

    // Busy Wait for the flag
    while (0 == Get_Bit(TWCR, TWINT))
        ;

    // Check ACK = SC ACK
    while (TWI_STATUS_VALUE != I2C_START_CONDITION_ACK)
        ;
}

void I2C_voidSendRepeatedStartCondition(void)
{
    // Request Start Condition
    Set_Bit(TWCR, TWSTA);

    // Clear flag to start current job
    Set_Bit(TWCR, TWINT);

    // Busy Wait for the flag
    while (0 == Get_Bit(TWCR, TWINT))
        ;

    // Check ACK = Repeated SC ACK
    while (TWI_STATUS_VALUE != I2C_REP_START_CONDITION_ACK)
        ;
}

void I2C_voidSendStopCondition(void)
{
    // Request Stop Condition
    Set_Bit(TWCR, TWSTO);

    // Clear flag to start current job
    Set_Bit(TWCR, TWINT);
}

void I2C_voidSendSlaveAddWithWrite(u8 copy_u8SlaveAdd)
{
    if (copy_u8SlaveAdd < 128)
    {
        TWDR = (copy_u8SlaveAdd << 1);

        // Select write operation
        Clr_Bit(TWDR, 0);

        // Clear start condition bit
        Clr_Bit(TWCR, TWSTA);

        // Clear flag to start current job
        Set_Bit(TWCR, TWINT);

        // Busy Wait for the flag
        while (0 == Get_Bit(TWCR, TWINT))
            ;

        // Check ACK = Master transmit ( slave address + Write request )
        while (TWI_STATUS_VALUE != I2C_SLAVE_ADDRESS_WRITE_ACK)
            ;
    }
    else
    {
        // return Error State
    }
}

void I2C_voidSendSlaveAddWithRead(u8 copy_u8SlaveAdd)
{
    if (copy_u8SlaveAdd < 128)
    {
        TWDR = (copy_u8SlaveAdd << 1);

        // Select read operation
        Set_Bit(TWDR, 0);

        // Clear start condition bit
        Clr_Bit(TWCR, TWSTA);

        // Clear flag to start current job
        Set_Bit(TWCR, TWINT);

        // Busy Wait for the flag
        while (0 == Get_Bit(TWCR, TWINT))
            ;

        // Check ACK = Master transmit ( slave address + read request )
        while (TWI_STATUS_VALUE != I2C_SLAVE_ADDRESS_READ_ACK)
            ;
    }
    else
    {
        // return Error State
    }
}

void I2C_voidTransmitMasterDataByte(u8 copy_u8TxData)
{

    // Write Data into data register
    TWDR = copy_u8TxData;

    // Clear flag to start current job
    Set_Bit(TWCR, TWINT);

    // Busy Wait for the flag
    while (0 == Get_Bit(TWCR, TWINT))
        ;

    // Check ACK = Master transmit data ACK
    while (TWI_STATUS_VALUE != I2C_MASTER_DATA_TRANSMIT_ACK)
        ;
}

void I2C_voidReceiveMasterDataByteWithAck(u8 *copy_pu8RxData)
{
    if (copy_pu8RxData != NULL)
    {
        // Enable ACK
        Set_Bit(TWCR, TWEA);

        // Clear flag to start current job
        Set_Bit(TWCR, TWINT);

        // Busy Wait for the flag
        while (0 == Get_Bit(TWCR, TWINT))
            ;

        // Check ACK = Master received data with ACK
        while (TWI_STATUS_VALUE != I2C_MASTER_DATA_RECIEVE_ACK)
            ;

        *copy_pu8RxData = TWDR;

        // Disable ACK
        Clr_Bit(TWCR, TWEA);
    }
    else
    {
        // return Error State
    }
}

void I2C_voidReceiveMasterDataByteWithNack(u8 *copy_pu8RxData)
{
    if (copy_pu8RxData != NULL)
    {
        // Clear flag to start current job
        Set_Bit(TWCR, TWINT);

        // Busy Wait for the flag
        while (0 == Get_Bit(TWCR, TWINT))
            ;

        // Check ACK = Master received data with NACK
        while (TWI_STATUS_VALUE != I2C_MASTER_DATA_RECIEVE_NACK)
            ;

        *copy_pu8RxData = TWDR;
    }
    else
    {
        // return Error State
    }
}
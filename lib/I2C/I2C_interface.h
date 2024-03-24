#ifndef __I2C_INTERFACE_H__
#define __I2C_INTERFACE_H__

#include "Std_Types.h"
#include "BitMath.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define I2C_BYTE_RATE 0x0C
#define I2C_PRESCALER_VALUE 0x00

#define TWI_STATUS_VALUE (TWSR & 0xF8)

#define I2C_START_CONDITION_ACK 0x08
#define I2C_REP_START_CONDITION_ACK 0x10
#define I2C_SLAVE_ADDRESS_WRITE_ACK 0x18
#define I2C_SLAVE_ADDRESS_READ_ACK 0x40
#define I2C_MASTER_DATA_TRANSMIT_ACK 0x28
#define I2C_MASTER_DATA_RECIEVE_ACK 0x50
#define I2C_MASTER_DATA_RECIEVE_NACK 0x58

// Master APIS
void I2C_voidInitMaster(void);
void I2C_voidSendStartCondition(void);
void I2C_voidSendRepeatedStartCondition(void);
void I2C_voidSendStopCondition(void);
void I2C_voidSendSlaveAddWithWrite(u8 copy_u8SlaveAdd);
void I2C_voidSendSlaveAddWithRead(u8 copy_u8SlaveAdd);
void I2C_voidTransmitMasterDataByte(u8 copy_u8TxData);
void I2C_voidReceiveMasterDataByteWithAck(u8 *copy_pu8RxData);
void I2C_voidReceiveMasterDataByteWithNack(u8 *copy_pu8RxData);

#endif // __I2C_INTERFACE_H__

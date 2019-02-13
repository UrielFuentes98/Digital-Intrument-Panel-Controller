/*
 * i2c.h
 *
 * Created: 02/10/2018 12:31:29 a. m.
 *  Author: Asus X556U
 */ 


#ifndef I2C_H_
#define I2C_H_
#define SLAVE_ADDR 0x49

uint8_t i2cSReceive();
void i2cSSend( uint8_t send_buff);
void i2cSSendID( uint16_t send_buff);
void SAcknowledge( uint32_t ack );
uint8_t i2cSReceive8bit( );
/*Send*/

void i2cSSend8bit( uint8_t temp );
void i2cSSend16bit( uint16_t temp );




#define myI2CSReceive i2cSReceive
#define myI2CSSend i2cSSend
#define myI2CSSendID i2cSSendID

#endif /* I2C_H_ */
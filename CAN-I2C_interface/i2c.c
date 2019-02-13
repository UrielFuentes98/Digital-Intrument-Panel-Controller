/*
 * i2c.c
 *
 * Created: 02/10/2018 12:31:15 a. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"

#include "i2c.h"


uint8_t i2cSReceive() {
	uint8_t data_rx;
	//CASE 2. Address packet is accepted - Write flag set
	SAcknowledge( 0 ); //configure for acknowledge
	while(!SERCOM3->I2CS.STATUS.bit.CLKHOLD){}//waits until slave hold message
	if( SERCOM3->I2CS.STATUS.bit.DIR == 0 ) { //if MASTER is transmitting
			//Acknowledge for packet is send automatically because AACKEN is enabled
		data_rx = i2cSReceive8bit( ); //receive data packet(s)
		
			//After receiving data, ack is send automatically because SMART MODE is enabled
	}
	return data_rx;
	SERCOM3->I2CS.INTFLAG.bit.AMATCH |= 1;
	SERCOM3->I2CS.INTFLAG.bit.DRDY |= 1; 
	
}
void i2cSSend(uint8_t send_buff){
	SAcknowledge( 0 ); //configure for acknowledge
	while(!SERCOM3->I2CS.STATUS.bit.CLKHOLD){}
	if( SERCOM3->I2CS.STATUS.bit.DIR == 1 ) { //if MASTER is transmitting
		//Acknowledge for packet is send automatically because AACKEN is enabled
		i2cSSend8bit(send_buff); //receive data packet(s)
		//After receiving data, ack is send automatically because SMART MODE is enabled
	}
	SERCOM3->I2CS.INTFLAG.bit.AMATCH |= 1;
	SERCOM3->I2CS.INTFLAG.bit.DRDY |= 1;
}
void i2cSSendID(uint16_t send_buff){
	SAcknowledge( 0 ); //configure for acknowledge
	while(!SERCOM3->I2CS.STATUS.bit.CLKHOLD){}
	if( SERCOM3->I2CS.STATUS.bit.DIR == 1 ) { //if MASTER is transmitting
		//Acknowledge for packet is send automatically because AACKEN is enabled
		i2cSSend16bit(send_buff); //receive data packet(s)
		//After receiving data, ack is send automatically because SMART MODE is enabled
	}
	SERCOM3->I2CS.INTFLAG.bit.AMATCH |= 1;
	SERCOM3->I2CS.INTFLAG.bit.DRDY |= 1;
}

uint8_t i2cSReceive8bit( ) {
	uint8_t valor;
	valor = SERCOM3->I2CS.DATA.reg; //read character received
	while( !SERCOM3->I2CS.INTFLAG.bit.DRDY ) { } //wait until data packet is received
	return valor;
}

void SAcknowledge( uint32_t ack ) {
	SERCOM3->I2CS.CTRLB.bit.ACKACT |= ack;
}


/*Send*/

void i2cSSend8bit(uint8_t temp){
	SERCOM3->I2CS.DATA.reg=SERCOM_I2CS_DATA_DATA(temp);
	while(!SERCOM3->I2CS.INTFLAG.bit.DRDY){
		
	}
}
void i2cSSend16bit(uint16_t temp){
	SERCOM3->I2CS.DATA.reg=SERCOM_I2CS_DATA_DATA(temp);
	while(!SERCOM3->I2CS.INTFLAG.bit.DRDY){
		
	}
}
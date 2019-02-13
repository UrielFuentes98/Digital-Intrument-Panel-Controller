/*
 * config_sercomI2C.c
 *
 * Created: 25/09/2018 07:43:27 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"
#include "config_sercomI2C.h"

void sercomI2CSInit( ) {
	sercomI2CSCTRLA( NULL, NULL, 0x0, NULL, 0x3, NULL, NULL, SERCOM_I2CM_CTRLA_MODE_I2C_SLAVE_Val, 0, NULL );
	sercomI2CSCTRLB( NULL, NULL, 0x1, 1, NULL, 1 );
	sercomI2CSADDR( SLAVE_ADDR, NULL, NULL, NULL );
}

void sercomI2CSEnable( ) {
	SERCOM3->I2CS.INTFLAG.reg = SERCOM_I2CS_INTFLAG_MASK; //clear the FLAGS
	SERCOM3->I2CS.CTRLA.reg |= SERCOM_I2CS_CTRLA_ENABLE; //I2C enabled
	while( SERCOM3->I2CS.SYNCBUSY.bit.ENABLE ){ } //wait until I2C is enabled		
}

void sercomI2CSCTRLA( uint32_t time_out, uint32_t stretch, uint32_t speed, uint32_t s_extend_time, uint32_t sda_hold, 
                     uint32_t pin_usage, uint32_t standby, uint32_t mode, uint32_t enable, uint32_t reset ) {				     
	//Main configurations
	SERCOM3->I2CS.CTRLA.reg |= SERCOM_I2CS_CTRLA_MODE( mode );
	SERCOM3->I2CS.CTRLA.bit.LOWTOUTEN |= time_out;
	SERCOM3->I2CS.CTRLA.reg |= SERCOM_I2CS_CTRLA_SDAHOLD( sda_hold ) | SERCOM_I2CS_CTRLA_SPEED( speed );	
	//Other configurations
	SERCOM3->I2CS.CTRLA.bit.SCLSM |= stretch;
	SERCOM3->I2CS.CTRLA.bit.SEXTTOEN |= s_extend_time;
	SERCOM3->I2CS.CTRLA.bit.PINOUT |= pin_usage;
	SERCOM3->I2CS.CTRLA.bit.RUNSTDBY |= standby;
	SERCOM3->I2CS.CTRLA.bit.SWRST |= reset;
	//SERCOMx must stay disabled until all its configured
	SERCOM3->I2CS.CTRLA.bit.ENABLE |= enable;
}

void sercomI2CSCTRLB( uint32_t acknowledge,  uint32_t command, uint32_t amode, uint32_t automatic_ack, uint32_t group, 
                      uint32_t smart ) {
	//Main configurations
	SERCOM3->I2CS.CTRLB.reg |= SERCOM_I2CS_CTRLB_AMODE( amode );
	SERCOM3->I2CS.CTRLB.bit.AACKEN |= automatic_ack;
	SERCOM3->I2CS.CTRLB.bit.SMEN |= smart;		
	//Other configurations
	SERCOM3->I2CS.CTRLB.bit.ACKACT |= acknowledge;
	SERCOM3->I2CS.CTRLB.reg |= SERCOM_I2CS_CTRLB_CMD( command );
	SERCOM3->I2CS.CTRLB.bit.GCMD |= group;	
}

void sercomI2CSADDR( uint32_t mask, uint32_t ten_bit, uint32_t address, uint32_t gen_call ) {
	//Main configurations
	SERCOM3->I2CS.ADDR.reg |= SERCOM_I2CS_ADDR_ADDRMASK( mask ) | SERCOM_I2CS_ADDR_ADDR( address );
	//Other configurations
	SERCOM3->I2CS.ADDR.bit.TENBITEN |= ten_bit;
	SERCOM3->I2CS.ADDR.bit.GENCEN |= gen_call;
}


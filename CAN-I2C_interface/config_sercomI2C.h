/*
 * config_sercomI2C.h
 *
 * Created: 25/09/2018 07:43:50 p. m.
 *  Author: Asus X556U
 */ 


#ifndef CONFIG_SERCOMI2C_H_
#define CONFIG_SERCOMI2C_H_

#define NULL 0
#define SLAVE_ADDR 0x49

void sercomI2CSInit( );
void sercomI2CSEnable( );
void sercomI2CSCTRLA( uint32_t time_out, uint32_t stretch, uint32_t speed, uint32_t s_extend_time, uint32_t sda_hold,
                      uint32_t pin_usage, uint32_t standby, uint32_t mode, uint32_t enable, uint32_t reset );
void sercomI2CSCTRLB( uint32_t acknowledge,  uint32_t command, uint32_t mode, uint32_t automatic_ack, uint32_t group,
                      uint32_t smart );
void sercomI2CSADDR( uint32_t mask, uint32_t ten_bit, uint32_t address, uint32_t gen_call );

#define mySercomI2CSInit sercomI2CSInit
#define mySercomI2CSEnable sercomI2CSEnable

#endif /* CONFIG_SERCOMI2C_H_ */
/*
 * config_port.h
 *
 * Created: 20/09/2018 11:10:26 p. m.
 *  Author: Asus X556U
 */ 
#ifndef CONFIG_PORT_H_
#define CONFIG_PORT_H_

void portInit( );
void portProps( uint8_t group, uint8_t pin, uint8_t value, uint8_t type );
void portDir( uint32_t group, uint32_t offset, uint32_t value);
void portOut( uint32_t group, uint32_t offset, uint32_t value );

#define myPortInit portInit
#define myPortOut portOut

#endif /* CONFIG_PORT_H_ */
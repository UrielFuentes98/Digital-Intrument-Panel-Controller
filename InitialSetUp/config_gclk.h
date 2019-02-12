/*
 * config_gclk.h
 *
 * Created: 20/09/2018 11:45:19 p. m.
 *  Author: Asus X556U
 */ 

#ifndef CONFIG_GCLK_H_
#define CONFIG_GCLK_H_

#define NULL 0

void gclkInit( );
void gclkGENDIV( uint32_t factor, uint32_t id );
void gclkGENCTRL( uint32_t _U_( standby ), uint32_t _U_( selection ), uint32_t _U_( output_en ),
				  uint32_t _U_( output_off ), uint32_t _U_( duty ), uint32_t _U_( enable ), uint32_t source,
				  uint32_t id );
void gclkCLKCTRL( uint16_t _U_( lock ),  uint16_t _U_( enable ), uint16_t generator, uint16_t id );

#define myGclkInit gclkInit

#endif /* CONFIG_GCLK_H_ */
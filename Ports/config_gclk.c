/*
 * config_gclk.c
 *
 * Created: 20/09/2018 11:45:02 p. m.
 *  Author: Asus X556U
 */
#include "sam.h"
#include "config_gclk.h"

void gclkInit( ) {
	
	//GCLK0 for I2C
	gclkGENCTRL( NULL, NULL, NULL, NULL, NULL, 1, GCLK_GENCTRL_SRC_OSC8M_Val, 0x1 );
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK1_Val, GCLK_CLKCTRL_ID_SERCOM3_CORE_Val );

	//GCLK1 for EIC
	gclkGENCTRL( NULL, NULL, NULL, NULL, NULL, 1, GCLK_GENCTRL_SRC_OSC8M_Val, 0x1 );
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK1_Val, GCLK_CLKCTRL_ID_EIC_Val );

	gclkGENCTRL( NULL, NULL, NULL, NULL, NULL, 1, GCLK_GENCTRL_SRC_OSC8M_Val, 0x2);
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK2_Val, GCLK_CLKCTRL_ID_TCC2_TC3_Val);
	//GCLK3 for PWM
	gclkGENCTRL( NULL, NULL, NULL, NULL, NULL, 1, GCLK_GENCTRL_SRC_OSC8M_Val, 0x3);
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK3_Val, GCLK_CLKCTRL_ID_TC4_TC5_Val);
}

void gclkGENDIV( uint32_t factor, uint32_t id ) {
	//Single 32-bit write
	GCLK->GENDIV.reg = GCLK_GENDIV_DIV( factor ) | GCLK_GENDIV_ID( id );
}

void gclkGENCTRL( uint32_t _U_( standby ), uint32_t _U_( selection ), uint32_t _U_( output_en ), 
				  uint32_t _U_( output_off ), uint32_t _U_( duty ), uint32_t _U_( enable ), uint32_t source, 
				  uint32_t id ) {
	//Single 32-bit write
	GCLK->GENCTRL.reg =  ( _U_( standby ) << GCLK_GENCTRL_RUNSTDBY_Pos ) 
					  | ( _U_( selection ) << GCLK_GENCTRL_DIVSEL_Pos ) 
	                  | ( _U_( output_en ) << GCLK_GENCTRL_OE_Pos ) | ( _U_( output_off ) << GCLK_GENCTRL_OOV_Pos )
					  | ( _U_( duty ) << GCLK_GENCTRL_IDC_Pos ) | ( _U_( enable ) << GCLK_GENCTRL_GENEN_Pos )
					  | GCLK_GENCTRL_SRC( source ) | GCLK_GENCTRL_ID( id );		
	while( GCLK->STATUS.bit.SYNCBUSY ) {}		  
}

void gclkCLKCTRL( uint16_t _U_( lock ),  uint16_t _U_( enable ), uint16_t generator, uint16_t id ) {
	//Single 16-bit write
	GCLK->CLKCTRL.reg = ( _U_( lock ) << GCLK_CLKCTRL_WRTLOCK_Pos ) | ( _U_( enable ) << GCLK_CLKCTRL_CLKEN_Pos )
				      | GCLK_CLKCTRL_GEN( generator ) | GCLK_CLKCTRL_ID( id ); 
} 

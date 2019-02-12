/*
 * CFile1.c
 *
 * Created: 20/09/2018 11:07:52 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"
#include "config_port.h"

void portInit( ) {
	//portProps(0, PIN_PA09, 0, 0);
	//PROPERTIES: pin configuration and peripheral function
	portProps (0,PIN_PA02, 0x3,PORT_PMUX_PMUXE_B); //Termistor input - A0
	//portProps (0, PIN_PA03, 0x3, PORT_PMUX_PMUXO_B); //Aref ADC reference.
	portProps( 0, PIN_PA22, 0x1, PORT_PMUX_PMUXE_C ); //SDA
	portProps( 0, PIN_PA23, 0x1, PORT_PMUX_PMUXO_C ); //SCL
	portProps( 0, PIN_PA15, 0x7, PORT_PMUX_PMUXO_A); //EncoderA - D5
	portProps(0,PIN_PA14,0x1,PORT_PMUX_PMUXE_E); //PWM - 2
	portProps( 0, PIN_PA08, 0x6, 0); //EncoderB - D4
	portProps (0, PIN_PA09,0x7,PORT_PMUX_PMUXO_A); //Encoder Button - D3
	portProps( 0, PIN_PA27, 0x0, 0 ); //TX_LED
	portProps(0, PIN_PA07, 0x6, 0); //Handbreak switch - D9
	portProps(0, PIN_PA02, 0x3, PORT_PMUX_PMUXE_B); // Input voltage -thermistor - A0
	portProps(0, PIN_PA04, 0x3, PORT_PMUX_PMUXE_B); // Reference 3.3 voltage - A3
	portProps(0,PIN_PA21,0x06,0); // Door open switch - D7
	portProps(0,PIN_PA06,0x0,0); //Gas level LED - D8
	portProps(0, PIN_PA20,0x0,0); // Door open LED - D6
	portProps(0, PIN_PA21,0x0,0); // Handbreak LED - D7
	
	
	//DIRECTION: data flow as input or output
	portDir(0,PORT_DIRSET_OFFSET,PORT_PA14); //PWM - 10
	portDir( 0, PORT_DIRSET_OFFSET, PORT_PA27 ); //TX_LED
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA15 ); //EncoderA
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA08 ); //EncoderB
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA09 ); //Encoder Button
	portDir (0, PORT_DIRCLR_OFFSET, PORT_PA21); //Door open switch
	portDir (0, PORT_DIRCLR_OFFSET, PORT_PA09); //Handbreak switch
	portDir (0, PORT_DIRSET_OFFSET, PORT_PA06); //Gas level LED
	portDir (0, PORT_DIRSET_OFFSET, PORT_PA20); //Door open LED
	portDir (0, PORT_DIRSET_OFFSET, PORT_PA21); //Handbreak LED
	//DATAOUTPUT: data logic level for output
	portOut( 0, PORT_OUTCLR_OFFSET, PORT_PA27 ); //TX_LED on
	portOut( 0, PORT_OUTSET_OFFSET, PORT_PA15 ); //EncoderA
	portOut( 0, PORT_OUTSET_OFFSET, PORT_PA08 ); //EncoderB
	portOut (0, PORT_OUTSET_OFFSET, PORT_PA09); //Encoder Button
	portOut(0, PORT_OUTSET_OFFSET, PORT_PA21); //Door open switch
	portOut(0, PORT_OUTSET_OFFSET, PORT_PA09); //Handbreak switch
}

void portProps( uint8_t group, uint8_t pin, uint8_t value, uint8_t type ) {
	//GROUP: PuertoA = 0, PIN position = PINCFG register
	PORT->Group[ group ].PINCFG[ pin ].reg = value; //configuration
	//PERIPHERAL FUNCTION if needed
	if( PORT->Group[ group ].PINCFG[ pin ].bit.PMUXEN == 1 ) {
		pin = ( pin >> 1 ); //obtain MUX register
		PORT->Group[ group ].PMUX[ pin ].reg |= type; //odd or even
	}
}

void portDir( uint32_t group, uint32_t offset, uint32_t value ) {
	if( offset == PORT_DIRSET_OFFSET ) {
		PORT->Group[ group ].DIRSET.reg = value; //output direction
	} else if( offset == PORT_DIRCLR_OFFSET ) {
		PORT->Group[ group ].DIRCLR.reg = value; //input direction
	}	
}

void portOut( uint32_t group, uint32_t offset, uint32_t value ) {
	if( offset == PORT_OUTSET_OFFSET ) {
		PORT->Group[ group ].OUTSET.reg = value; //logic level "1"
		} else if( offset == PORT_OUTCLR_OFFSET ) {
		PORT->Group[ group ].OUTCLR.reg = value; //logic level "0"
	}
}
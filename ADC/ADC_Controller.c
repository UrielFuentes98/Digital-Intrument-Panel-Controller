/*
 * ADC_Controller.c
 *
 * Created: 11/10/2017 9:44:35 AM
 * Author : Javier
 */ 
#include "sam.h"
uint16_t adcresult;
uint16_t resistance;
uint8_t pinADC;
uint16_t temperature;

void initADC( uint8_t GenericCLK, uint8_t REF)
{

REG_GCLK_GENCTRL |= GCLK_GENCTRL_GENEN |
GCLK_GENCTRL_ID(GenericCLK) |
GCLK_GENCTRL_IDC|
GCLK_GENCTRL_SRC_OSC8M;

while (GCLK -> STATUS.bit.SYNCBUSY);

//CONFIGURACION DE DIVISION DE RELOJ FUENTE (Numero de divisiones y reloj)
REG_GCLK_GENDIV |= GCLK_GENDIV_DIV(0) |
GCLK_GENDIV_ID(GenericCLK);

while (GCLK -> STATUS.bit.SYNCBUSY);

//CONFIGURACION Y HABILITACION DE RELOJ DE RECEPCION
//Accedemos al registro CLKCTRL (Clock control) que nos permite
//indicarle al Generic clock a donde apuntar
//Habiltamos el generic clock
//Seleccionamos el clock generator que queremos usar (en nuestro caso el 0)
//Seleccionamos el Clock correspondiente a una instancia, que en nusestro caso es el ADC
REG_GCLK_CLKCTRL |= GCLK_CLKCTRL_CLKEN |
GCLK_CLKCTRL_GEN(GenericCLK) |
GCLK_CLKCTRL_ID_ADC;

while (GCLK -> STATUS.bit.SYNCBUSY);
	//CONFIGURACION DE POWER MANAGEMENT
	REG_PM_APBCMASK |= PM_APBCMASK_ADC;
	REG_PM_APBCSEL |= PM_APBCSEL_APBCDIV_DIV1;

	//CONFIGURACIONES INTERNAS DEL ADC
	//Accedemos al bit ENABLE y lo deshabilitamos (Esto nos permite configurarlo)
	ADC -> CTRLA.bit.ENABLE &= ~ADC_CTRLA_ENABLE;
	
	while (ADC -> STATUS.bit.SYNCBUSY);
	
	//Habilitamos el bit REFCOMP(Aumenta la presicion de la ganancia decreciendo la impedancia)
	//Le damos el valor AREFA al registro REFSEL el cual nos indica la referencia, AREFA es la referencia externa A 
	switch (REF){
		case 1:
			ADC -> REFCTRL.reg |= ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_AREFA;
			break;
		case 2:
			ADC -> REFCTRL.reg |= ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_AREFB;
			break;
		case 3:
			ADC -> REFCTRL.reg |= ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_INTVCC1;
			break;
		case 4:
			ADC -> REFCTRL.reg |= ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_INTVCC0;
			break;
		case 5:
			ADC -> REFCTRL.reg |= ADC_REFCTRL_REFCOMP | ADC_REFCTRL_REFSEL_INT1V;
			break;
	}			
																
	ADC -> AVGCTRL.reg |= ADC_AVGCTRL_SAMPLENUM_1;

	ADC -> SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(0x00);

	ADC -> CTRLB.reg |= ADC_CTRLB_PRESCALER_DIV256 | ADC_CTRLB_RESSEL_12BIT | ADC_CTRLB_FREERUN;
	while (ADC -> STATUS.bit.SYNCBUSY);
	
	//Accedemos a WINCTRL y lo deshanilitamos
	ADC -> WINCTRL.reg = ADC_WINCTRL_WINMODE_DISABLE;

	ADC -> INPUTCTRL.reg |= ADC_INPUTCTRL_GAIN_1X | ADC_INPUTCTRL_INPUTSCAN(0x0) | ADC_INPUTCTRL_MUXPOS(4) | ADC_INPUTCTRL_MUXNEG_GND;
	while(ADC -> STATUS.bit.SYNCBUSY);

	ADC -> INTENCLR.reg	|= ADC_INTENCLR_RESRDY;

	ADC -> INTENSET.reg |= ADC_INTENCLR_RESRDY;

	ADC -> CTRLA.reg = ADC_CTRLA_ENABLE;
	while(ADC -> STATUS.bit.SYNCBUSY);
	
	//El FLUSH borra el valor que tiene el ADC y lo inicia en cero
	ADC -> SWTRIG.reg = ADC_SWTRIG_FLUSH; //REVISAR
	while(ADC -> STATUS.bit.SYNCBUSY);
	
	//El ADC inicializa el FLUSH
	ADC -> SWTRIG.reg = ADC_SWTRIG_START;
	while(ADC -> STATUS.bit.SYNCBUSY);
}
void readADC(void)
{
	//Igualamos la variable ADC result a la que se encuentra en el registro
	adcresult = ADC -> RESULT.reg;
	//while(ADC -> STATUS.bit.SYNCBUSY);
	//Habilitamos la interrupcion
	ADC -> INTENCLR.reg = ADC_INTENCLR_RESRDY;
	resistance = - ((10000 * adcresult)/(- 4096 + adcresult));
	temperature = (-0.00263 * resistance + 324.45) - 273.15;
}
void ChangeMuxADC(uint8_t PIN){
	
	PORT -> Group[0].PINCFG[pinADC].bit.PMUXEN = 0;
	
	//Deshabilitamos el ADC para poder configurarlos
	ADC -> CTRLA.bit.ENABLE &= ~ADC_CTRLA_ENABLE;
	//Limpiamos el registro
	ADC -> INPUTCTRL.bit.MUXPOS = 00000;
	//Cargamos un nuevo valor al registro
	ADC -> INPUTCTRL.reg |= ADC_INPUTCTRL_MUXPOS(0);
	//Habilitamos el ADC de nuevo
	ADC -> CTRLA.reg = ADC_CTRLA_ENABLE;
	while(ADC -> STATUS.bit.SYNCBUSY);
	
	PORT -> Group[0].PINCFG[PIN].bit.PMUXEN = 1;
	if(PIN%2 == 0){
		PORT -> Group[0].PMUX[2].bit.PMUXE = PORT_PMUX_PMUXE_B_Val;
	}
	else{
		PORT -> Group[0].PMUX[2].bit.PMUXO = PORT_PMUX_PMUXE_B_Val;
	}
	
	pinADC = PIN;
}
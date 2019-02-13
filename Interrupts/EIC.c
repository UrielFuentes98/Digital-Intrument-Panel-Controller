/*
 * EIC.c
 *
 * Created: 11/7/2018 1:19:55 PM
 *  Author: Uriel Fuentes
 */ 
#include "sam.h"
#include "EIC.h"

void EIC_SetUp (){
	EIC->CONFIG[1].bit.SENSE7 = 2;						//Configurar la interrupción como falling edge
	EIC->INTENSET.bit.EXTINT15 = 1;						//Habilitar la interrupción
	EIC->INTFLAG.bit.EXTINT15 = 1;						//Limpiar la bandera de interrupción
	EIC->CONFIG[1].bit.SENSE1 = 2;
	EIC->INTENSET.bit.EXTINT9 = 1;
	EIC ->INTFLAG.bit.EXTINT9 = 1;
	EIC->CTRL.bit.ENABLE = 1;							//Habilitar el periférico
	while((EIC->STATUS.bit.SYNCBUSY));					//Esperar sincronización
}


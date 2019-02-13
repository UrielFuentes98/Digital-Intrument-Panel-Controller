/*
 * Timers.c
 *
 * Created: 11/14/2018 9:06:22 AM
 *  Author: Uriel Fuentes
 */ 

#include "sam.h"
#include "Timers.h"

void TimersSetup(){
	//Configure delay
	TC4->COUNT16.CTRLA.bit.MODE = 0;
	TC4->COUNT16.CTRLA.bit.PRESCALER = 4;
	TC4->COUNT16.INTFLAG.bit.OVF = 1;					//Limpiar la bandera de overflow
	TC4->COUNT16.COUNT.bit.COUNT = 60536 + (baseCycle * 15 );					//Inicializar el COUNT
	TC4->COUNT16.CTRLA.bit.PRESCSYNC = 1;				//Configurar la sincronización del prescalador y el counter
	TC4->COUNT16.CTRLA.bit.ENABLE = 1;					//Habilitar el timer
	while(TC4->COUNT16.STATUS.bit.SYNCBUSY);		
	//Configure PWM
	TC3->COUNT16.CTRLA.bit.PRESCSYNC = 2;
	TC3->COUNT16.CTRLA.bit.WAVEGEN = 2;
	TC3->COUNT16.CTRLA.bit.PRESCALER = 0;
	TC3->COUNT16.CTRLA.bit.MODE = 0;
	TC3->COUNT16.CC[0].reg = baseCycle - (55 * dutyChange);
	TC3->COUNT16.CTRLA.bit.ENABLE = 1;					//Habilitar el timer
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY);
}

void delay (uint16_t millis){
	uint16_t count = count20ms + ((20 - millis) * 500);
	TC4->COUNT16.COUNT.bit.COUNT = count;
	TC4->COUNT16.CTRLA.bit.ENABLE = 1;					//Habilitar el timer
	while(TC4->COUNT16.STATUS.bit.SYNCBUSY);
	while(!TC4->COUNT16.INTFLAG.bit.OVF);
	TC4->COUNT16.INTFLAG.bit.OVF = 1;
	TC4->COUNT16.CTRLA.bit.ENABLE = 0;
	while(TC4->COUNT16.STATUS.bit.SYNCBUSY);
}

void IncreaseDuty () {
	TC3->COUNT16.CTRLA.bit.ENABLE = 0;
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY);
	uint16_t duty = TC3->COUNT16.CC[0].reg;
	if (TC3->COUNT16.CC[0].reg < 52427){
		duty = duty + dutyChange;
		TC3->COUNT16.CC[0].reg = duty;
	}
	TC3->COUNT16.CTRLA.bit.ENABLE = 1;
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY);
}

void DecreaseDuty () {
	TC3->COUNT16.CTRLA.bit.ENABLE = 0;
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY);
	uint16_t duty = TC3->COUNT16.CC[0].reg;
	if (TC3->COUNT16.CC[0].reg > 49152){
		duty = duty - dutyChange;
		TC3->COUNT16.CC[0].reg = duty;
	}
	TC3->COUNT16.CTRLA.bit.ENABLE = 1;
	while(TC3->COUNT16.STATUS.bit.SYNCBUSY);
}
/*
 * ADC_Controller.h
 *
 * Created: 11/10/2017 9:51:12 AM
 *  Author: Javier
 */ 

#ifndef ADC_CONTROLLER_H_
#define ADC_CONTROLLER_H_

//Variables
uint16_t adcresult;
uint8_t pinADC;
uint16_t resistance;
uint16_t temperature;

//FUNCIONES
void initADC(uint8_t GenericCLK, uint8_t REF);
void readADC(void);
void ChangeMuxADC(uint8_t PIN);
//DEFINES
#define AREFA   1
#define AREFB   2
#define INTVCC1 3
#define INTVCC0 4
#define INT1V   5

#endif /* ADC_CONTROLLER_H_ */
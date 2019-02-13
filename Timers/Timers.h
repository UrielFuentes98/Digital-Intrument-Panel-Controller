/*
 * Timers.h
 *
 * Created: 11/14/2018 9:06:35 AM
 *  Author: Uriel Fuentes
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#define count20ms 55536
#define dutyChange 655
#define baseCycle 49152
void TimersSetup();
void delay (uint16_t millis);
void DecreaseDuty ();
void IncreaseDuty ();


#endif /* TIMERS_H_ */
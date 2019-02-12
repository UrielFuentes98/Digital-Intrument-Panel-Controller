/*
 * config_pm.h
 *
 * Created: 20/09/2018 11:20:40 p. m.
 *  Author: Asus X556U
 */ 
#ifndef CONFIG_PM_H_
#define CONFIG_PM_H_

void pmInit();
void pmAPBCMASK( uint32_t value );
void pmAPBAMASK( uint32_t value );
#define myPmInit pmInit

#endif /* CONFIG_PM_H_ */
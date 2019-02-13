This folder contain the files with the code needed to implement
the ADC to read the temperature from the TFT display using its internal thermistor.

To obtain the temperature we need to know the resistance of the thermistor. Because I used 12 bit resolution and
the ADC value was obtain with a voltage divider  of the termistor with a 10k resistance. The resistance of the thermistor is obtain by 
= resistance = - ((10 000 * adcresult)/(- 4096 + adcresult));

The temperature of the thermistor is given by the following formula:
B = (ln(R1) - ln(r2))/((1/T1) - (1/T2))

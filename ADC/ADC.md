This folder contain the files with the code needed to implement
the ADC to read the temperature from the TFT display using its internal thermistor.

To obtain the temperature we need to know the resistance of the thermistor. Because I used a 12 bit resolution and
the ADC value was obtained with a voltage divider  of the termistor with a 10k resistance, the resistance of the thermistor is obtain by: resistance = - ((10 000 * adcresult)/(- 4096 + adcresult));

The temperature of the thermistor is given by the following formula:
B = (ln(R1) - ln(R2))/((1/T1) - (1/T2))

Substituting the thermistor values for 25 ºC we obtain: 3380 = (ln(R1) - ln(10 000))/((1/T1) - (1/298.15))

If we solve for temperature we obtain T = 3380 / (ln(R) + 2.1262)

To avoid having to compute the natural logarithm in the microcontroller I realized a linear aproximation around R = 10 000 and obtain:
T = -0.00263 * R + 324.25

The equation to obtain the thermistor resistance and the equation to obtain the temperature were implemented in the code. 

# Digital-Intrument-Panel-Controller
This repository contains the code for the prototype of a digital instrument panel controller of a car using an ATSAMD21G18A. Part of a semester long school project developed in collaboration with Yazaki Corporation. https://www.yazaki-group.com/global/

The controller is in charge of extract car parameters to be displayed in a TFT LCD display (speed, rpm, gas level) from CAN messages, and send them to a SBC (SAMA5D2) via I2C, that is in charge of refreshing the display. 

Other fucntions of the controller:
- To read the inputs of a rotary encoder using external interrupts and change the display brightness according to them (push the encoder to enable/disable brightness adjustment, turn left to decrease brightness, turn right to increase it).
- Read temperature of the TFT screen using and ADC (voltage divider using thermistor of display).
- Generate a PWM signal to control  display brightness.
- Control witnesses LEDs (low gas (gas < 10%), hand break-on).
- Delay function implementation for rotary encoder inputs debouncing. 

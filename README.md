# Digital-Intrument-Panel-Controller
This repository contains the code for the prototype of a digital instrument panel controller of a car using an ATSAMD21G18A. Part of a school project developed in collaboration with Yazaki Corporation. https://www.yazaki-group.com/global/

The controller is in charge of extract car parameters to be displayed in a TFT LCD display (speed, rpm, gas level) from CAN messages, and send them to a SBC (SAMA5D2) that is in charge of refresh the display via I2C. 

Other fucntions of the controller:
- Read inputs from a rotary encoder using external interruptions.
- Read temperature of the TFT screen using and ADC.
- Generate a PWM signal to control the dimming of the screen.
- Control witnesses LEDs (low gas, hand break-on).

#include "sam.h"
#include "mcp_can.h"
#include "spi.h"
#include "uart.h"
#include "myprintf.h"
#include "mcp_can_dfs.h"
#include "config_port.h"
#include "config_pm.h"
#include "config_gclk.h"
#include "config_sercomI2C.h"
#include "i2c.h"
#include "datapool.h"
#include "EIC.h"
#include "Timers.h"
#include "ADC_Controller.h"
#include <string.h>

#define CAN0_SPEED CAN_500KBPS
#define CAN1_SPEED CAN_100KBPS
uint8_t stmp[8] = {11, 0, 0, 0, 0, 11, 5, 0};
uint16_t id=0;
uint8_t len=0;
uint8_t test,valor,counter;
uint16_t ADCvalue;
uint8_t button = 0;

message CanMessages [poolSize];
int main(void)
{
	/* Initialize the SAM system */
	SystemInit();
	SYSCTRL->OSC8M.bit.PRESC=0;
	NVIC_EnableIRQ(EIC_IRQn);	//Habilita la interrupción externa
	NVIC_SetPriority(EIC_IRQn, 1); //Asigna la prioridad a la interrupción externa
	__enable_irq();
	//Initialization of peripherals
	portInit();
	gclkInit();
	pmInit();
	sercomI2CSInit( );
	sercomI2CSEnable( );
	TimersSetup();
	initUART();
	initSPI();
	EIC_SetUp();
	initADC(4,1);
	ChangeMuxADC(PIN_PA02);
	canBegin(SLAVE_SD_CARD, CAN0_SPEED);
	InitDataPool(CanMessages);
	
	//Main loop. Read CAN bu, send i2c data, and the other functions
	
while (1) {
	
	
	readMsgBufID(&id, &len, stmp);
	test = FillDataBase(id,stmp,CanMessages, button);
		
		for (uint8_t index =0; index<8; index++)
		{
			for (uint8_t pos =0; pos<6; pos++){
				valor=myI2CSReceive();
				if (valor==0)
				{
					myI2CSSendID(CanMessages[index].ID);
				}
				else{
					if (valor>0 && valor<6)
					{
						valor=valor-1;
						myI2CSSend(CanMessages[index].data[valor]);
					}
				}
			}
		}
}
}

//Handler for the External interruption when a turn of the rotary encoder is detected
void EIC_Handler ( void ) {
	if (EIC->INTFLAG.bit.EXTINT15 && button){
		if (PORT ->Group[0].IN.reg & 1 << PIN_PA08){
			DecreaseDuty();
			myprintf("Turn Left\n");
		delay(100);}
		else{
			myprintf("Turn Right\n");
			IncreaseDuty();
		delay(100);}
		EIC->INTFLAG.bit.EXTINT15 = 1;	//Limpia la bandera del interruptor
		counter ++;
		
	}
	else if (EIC->INTFLAG.bit.EXTINT9 && !button){
		EIC->INTENSET.bit.EXTINT15 = 1;
		EIC->INTFLAG.bit.EXTINT9 = 1;
		EIC->CTRL.bit.ENABLE = 1;
		while((EIC->STATUS.bit.SYNCBUSY));
		button = ~button;
		delay(100);
		myprintf("On\n");
		} else if (EIC ->INTFLAG.bit.EXTINT9 && button){
		EIC->INTENCLR.reg = 1<<15;
		EIC->INTFLAG.bit.EXTINT9 = 1;
		EIC->CTRL.bit.ENABLE = 1;
		while((EIC->STATUS.bit.SYNCBUSY));
		button = !button;
		delay(100);
		delay(100);
		myprintf("Off\n");
	}
	EIC->INTFLAG.bit.EXTINT9 = 1;
}

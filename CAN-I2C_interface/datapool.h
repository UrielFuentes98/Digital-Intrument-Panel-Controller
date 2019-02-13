/*
 * datapool.h
 *
 * Created: 11/10/2018 11:12:38 PM
 *  Author: Uriel Fuentes
 */ 

#include "sam.h"

#ifndef DATAPOOL_H_
#define DATAPOOL_H_

#define true 1
#define false 0
typedef int bool;

typedef struct {
	uint16_t ID;
	uint8_t data[5];
	uint8_t maskdata;
}message;

#define Eng_Speed_Id 0x15
#define Eng_RPM_Id 0x16
#define Eng_OilLevel_Id 0x20
#define Eng_OilPressure_Id 0x21
#define Eng_Gas_Id 0x22
#define Eng_Temp_Id 0x25
#define Eng_Gear_Pos_Id 0x26
#define Bd_Id 0x30
#define Saf_Id 0x32
#define Inf_OT_Id 0x64
#define poolSize 8
#define dataSize 5
#define byte1 0
#define byte2 1
#define byte3 2
#define byte4 3
#define byte5 4
#define size 2
#define maskbytes1_2 3
#define maskbyte1 1
#define maskbytes5_3 20  

void InitDataPool (message *CanMessages);
void FillZeros(message CanMessagee);
void StoreMessage (message *CanMessage, uint8_t index, uint8_t *dataCan);
uint8_t FillDataBase (uint16_t CanID, uint8_t *dataCan, message *CanMessage);
void FillTest (message *CanMessages);
void printDatapool (message *CanMessages);
uint8_t compareId(message *CanMessages, uint16_t id);
uint16_t extractSpeed(message *CanMessages);
uint16_t extractRPM(message *CanMessages);
uint16_t extractOilLevel(message *CanMessages);
uint16_t extractEngTemp(message *CanMessages);
uint8_t extractGearPos(message *CanMessages);
uint8_t* extractBd(message *CanMessages);
uint8_t* extractSafety(message *CanMessages);
uint16_t extractOutTemp(message *CanMessages);
uint8_t extractEngGas(message *CanMessages);
#endif /* DATAPOOL_H_ */
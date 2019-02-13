/*
 * datapool.c
 *
 * Created: 11/10/2018 11:12:26 PM
 *  Author: Uriel Fuentes
 */ 

#include "sam.h"
#include "datapool.h"
#include "myprintf.h"


void InitDataPool (message *CanMessages){
	CanMessages[0].ID = Eng_Speed_Id;
	CanMessages[0].maskdata = maskbytes1_2;
	FillZeros(CanMessages[1]);
	CanMessages[1].ID = Eng_RPM_Id;
	CanMessages[1].maskdata = maskbytes1_2;
	FillZeros(CanMessages[1]);
	CanMessages[2].ID = Eng_Temp_Id;
	CanMessages[2].maskdata = maskbytes1_2;
	FillZeros(CanMessages[2]);
	CanMessages[3].ID = Eng_Gear_Pos_Id;
	CanMessages[3].maskdata = maskbyte1;
	FillZeros(CanMessages[3]);
	CanMessages[4].ID = Bd_Id;
	CanMessages[4].maskdata = maskbytes5_3;
	FillZeros(CanMessages[4]);
	CanMessages[5].ID = Saf_Id;
	CanMessages[5].maskdata = maskbytes5_3;
	FillZeros(CanMessages[5]);
	CanMessages[6].ID = Inf_OT_Id;
	CanMessages[6].maskdata = maskbytes1_2;
	FillZeros(CanMessages[6]);
	CanMessages[7].ID = Eng_Gas_Id;
	CanMessages[7].maskdata = maskbyte1;
	FillZeros(CanMessages[7]);
}

void FillZeros(message CanMessagee){
	for (uint8_t i = 0; i < 4; i++){
		CanMessagee.data[i] = 0;
	}
}



uint8_t FillDataBase (uint16_t CanID, uint8_t *dataCan, message *CanMessage){
	uint8_t index = 0;
	bool cycle = true;
	do {
				//myprintf("ID message = %x\n", CanID);
				//myprintf("ID datapool = %x\n", CanMessage[index].ID);
		if (CanID == CanMessage[index].ID){
			StoreMessage(CanMessage,index,dataCan);
			myprintf("Saving\n");
			myprintf("CanID = %x\n",CanID);
			myprintf("index = %x\n",index);
		cycle = false;}
		else{
		index++;}
	}while(cycle && index < poolSize);
	return index;
}

void StoreMessage (message *CanMessage, uint8_t index, uint8_t *dataCan){
	for (uint8_t i = 0; i < 4; i++){
			CanMessage[index].data[i] = dataCan[i];
	 }
}

void FillTest (message *CanMessages){
    CanMessages[0].data[0] = 0x35;
    CanMessages[0].data[1] = 0x00;

    CanMessages[1].data[0] = 0x40;
    CanMessages[1].data[1] = 0x1F;

    CanMessages[2].data[0] = 0x32;
    CanMessages[2].data[1] = 0x00;
	
    CanMessages[3].data[0] = 0x32;
    CanMessages[3].data[1] = 0x00;
    
    CanMessages[4].data[0] = 0x5A;
    CanMessages[4].data[1] = 0x00;
    
    CanMessages[5].data[0] = 0x02;
    
    CanMessages[6].data[2] = 0x2; //right
    CanMessages[6].data[4] = 0x1; //set
    
    CanMessages[7].data[2] = 0x3; //booth
    CanMessages[7].data[4] = 0x1; //door 1

	CanMessages[8].data[0] = 0x20;
	
    CanMessages[9].data[0] = 0x32;
}

void printDatapool (message *CanMessages){
	for (int i = 0; i < 10; i++){
		myprintf ("Message %d.\n", i);
		myprintf ("ID = %x.\n",CanMessages[i].ID);
		myprintf ("Data = %x %x %x %x %x.\n\n", CanMessages[i].data[0],CanMessages[i].data[1],CanMessages[i].data[2],CanMessages[i].data[3],CanMessages[i].data[4]);
	}
}
	
	uint16_t extractSpeed(message *CanMessages){
		uint16_t speed = 0; 
		uint8_t index = compareId(CanMessages, Eng_Speed_Id);
		speed = CanMessages[index].data[byte1] << 8 | CanMessages[index].data[byte2];
		speed = speed / 10;
		myprintf("The speed value is %x \n", speed);
		return speed;
	}

	uint16_t extractRPM(message *CanMessages){
		uint16_t RPM = 0;
		uint8_t index = compareId(CanMessages, Eng_RPM_Id);
		RPM = CanMessages[index].data[byte1] << 8 | CanMessages[index].data[byte2];
		myprintf("The RPM value is %x \n", RPM);
		return RPM;
	}

	uint16_t extractOilLevel(message *CanMessages){
		uint16_t oilLevel;
		uint8_t index = compareId(CanMessages, Eng_OilLevel_Id);
		oilLevel = CanMessages[index].data[byte1] << 8 | CanMessages[index].data[byte2];
		myprintf("The oil Level  value is %x \n",  oilLevel);
		return oilLevel;
	}
	
	uint16_t extractEngTemp(message *CanMessages){
		uint16_t EngTemp;
		uint8_t index = compareId(CanMessages, Eng_Temp_Id);
		EngTemp = CanMessages[index].data[byte1] << 8 | CanMessages[index].data[byte2];
		myprintf("The temperature  value is %x \n",  EngTemp);
		return EngTemp;
	}

	uint8_t extractGearPos(message *CanMessages){
		uint8_t GearPos;
		uint8_t index = compareId(CanMessages, Eng_Temp_Id);
		GearPos = CanMessages[index].data[byte1];
		myprintf("Gear position = %x \n",  GearPos);
		return GearPos;
	}

uint8_t* extractBd(message *CanMessages){
	uint8_t Body[2];
	uint8_t index = compareId(CanMessages, Bd_Id);
	Body[0] = CanMessages[index].data[byte3];
	Body[1] = CanMessages[index].data[byte5];
	myprintf ("Body values = %x and %x", Body[0],Body[1]);
	return Body;
} 

uint8_t* extractSafety(message *CanMessages){
	uint8_t Safety[2];
	uint8_t index = compareId(CanMessages, Saf_Id);
	Safety[0] = CanMessages[index].data[byte3];
	Safety[1] = CanMessages[index].data[byte5];
	myprintf ("Safety values = %x and %x", Safety[0],Safety[1]);
	return Safety;	
}

uint16_t extractOutTemp(message *CanMessages){
		uint16_t OutTemp;
		uint8_t index = compareId(CanMessages, Inf_OT_Id);
		OutTemp = CanMessages[index].data[byte1] << 8 | CanMessages[index].data[byte2];
		myprintf("The temperature  value is %x \n",  OutTemp);
		return OutTemp;	
}

uint8_t extractEngGas(message *CanMessages){
		uint8_t GasLevel;
		uint8_t index = compareId(CanMessages, Inf_OT_Id);
		GasLevel = CanMessages[index].data[byte1];
		myprintf("Gas level %x \n",  GasLevel);
		return GasLevel;
}
	
	uint8_t compareId(message *CanMessages, uint16_t id){
		uint8_t index = 0;
		for (uint8_t i = 0 ; i < poolSize ; i++){
			if(CanMessages[i].ID == id){
				index = i;
				break;
			}
		}
		return index;
	}
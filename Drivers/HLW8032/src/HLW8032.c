/*
 * test.c
 *
 *  Created on: Nov 16, 2023
 *      Author: kirill
 */
#include "HLW8032.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

uint32_t	VolPar;
uint32_t	VolData;
uint32_t	PowerPar;
uint32_t	PowerData;
uint32_t	CurrentPar;
uint32_t	CurrentData;
float		Voltage;
float		VoltageAnalog;
float		VF = 1;
float		CF = 1;
uint32_t	PFData = 0;
uint32_t	PulsCountFor1kWh;
uint16_t 	PF_reg, PF_reg_old;
uint32_t	test_flag = 0;

void InitHLW8032(uint32_t VolR1, uint32_t VolR2, float CurrentShuntR){

	//VolR1 - Resistanse on OM for first resistor
	//VolR2 - Resistanse on OM for second resistor
	//ShuntR - Resistanse in OM for current shunt resistor

	VF = VolR1 / (VolR2 * 1000.0);
	CF = 1.0 / (CurrentShuntR * 1000.0);
}

void SetVF(float Data){

	VF = Data;

}

uint8_t Checksum(char * string){
	uint8_t i, tmp;
	char byte;

	byte = 0;
	for ( i = 2; i <= 22; i++){
		tmp = string[i];
		byte = byte + string[i];
	}
	if (byte == string[23])
	{
		return 1;
	}
	return 0;
}


int RecvRawString(const unsigned char * string){

	if (!strcmp(string+1, 0x5A)){
		return -1; //error code
	}
	//if(string[1] =! 0x5A){
	//	return -1; //error code
	//}

	if (!Checksum(string)){
		return -2; //Checksum Error
	}

	VolPar = ((uint32_t)string[2] << 16) + ((uint32_t)string[3] << 8) + string[4];

	if(bitRead(string[20],6) == 1){
		VolData = ((uint32_t)string[5]  <<16) + ((uint32_t)string[6] <<8) + string[7];
		VoltageAnalog = VolPar / VolData;

	}

	CurrentPar = ((uint32_t)string[8]  <<16) + ((uint32_t)string[9] <<8) + string[10];

	if(bitRead(string[20], 5) == 1)
	{
		CurrentData = ((uint32_t)string[11]  <<16) + ((uint32_t)string[12] <<8) + string[13];
	}
	PowerPar = ((uint32_t)string[14]  <<16) + ((uint32_t)string[15] <<8) + string[16];

	if(bitRead(string[20], 4) == 1)
	{
		PowerData = ((uint32_t)string[17]  <<16) + ((uint32_t)string[18] <<8) + string[19];
	}

	PF_reg = ((uint32_t)string[21] <<8) + string[22];

	if(bitRead(string[20], 7) == 1)
	{
		PFData++;
	}

	//TODO Когда переполняется регистр, выставляется флаг и обнудяется регистр, проверить, можем ли мы ловить этот флаг еще и не совпадением старого и нового значения регистров.
	if(PF_reg_old > PF_reg){
		test_flag++;
	}

	PF_reg_old = PF_reg;

	return 0;
}

float GetVolRaw(void){

	if ( VolData == 0){
		return 0;
	}

	return VolPar / (float)VolData;
}

float GetVoltage(void){

	float tmp;
	float RealVolt;

	tmp = GetVolRaw();
	RealVolt = tmp * VF;
	return RealVolt;
}

float GetCurrentRaw(void){

	if ( CurrentData == 0){
		return 0;
	}

	return CurrentPar / (float)CurrentData;
}

float GetCurrent(void){

	float tmp;
	float RaelCurrent;

	tmp = GetCurrentRaw();
	RaelCurrent = tmp * CF;
	return RaelCurrent;
}

float GetActivePower(void){
	float tmp;

	if (PowerData == 0){
		return 0;
	}
	tmp = (float)(PowerPar / PowerData) * VF * CF;
	return tmp;
}

float GetApparentPower(void){

	float voltage;
	float current;
	float ApparentPower;

	voltage = GetVoltage();
	current = GetCurrent();
	ApparentPower = voltage * current;

	return ApparentPower;
}

float PowerFactor(void){

	float ActivePower;
	float ApparentPower;
	float PowerFactor;

	ActivePower 	= GetActivePower();
	ApparentPower	= GetApparentPower();
	if (ApparentPower == 0) return 1;
	if (ActivePower > ApparentPower) return 1.000000000000;
	PowerFactor		= ActivePower / ApparentPower;

	return PowerFactor;
}

uint32_t GetPulsCnF1kWh(){

}

float GetKWh(void){
	float apparentPower;
	float pulseCountFor1kWh;
	float kWh;
	int PFcount;


	apparentPower		= GetApparentPower();
	pulseCountFor1kWh	= (1.0/PowerPar) * (1.0/(VF * CF)) * 1000000000.0 * 3600.0;
	PFcount				= PFData * 65536 + PF_reg;
	//kWh					= (PFData * PF_reg) / (float)pulseCountFor1kWh;
	kWh					= PFcount / (float)pulseCountFor1kWh;

	return kWh;
}

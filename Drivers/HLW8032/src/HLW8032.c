/*
 * test.c
 *
 *  Created on: Nov 16, 2023
 *      Author: kirill
 */
#include "HLW8032.h"
#include "definition.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

uint32_t	VolPar;
uint32_t	VolData;
uint32_t	PowerPar;
uint32_t	PowerData;
uint32_t	CurrentPar;
uint32_t	CurrentData;
float		Voltage;
float		VoltageAnalog;
float		CurrentAnalog;
float		PowerAnalog;
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

//Byte 1 (1 byte) string[0] - indication of data state
//Byte 2 (1 byte) string[1] - Default value	0x5A
//Byte 3		  string[2]
//byte 4		  string[3]
//byte 5 (3 byte) string[4] - Valtage parameter reg (default)
//byte 6		  string[5]
//byte 7		  string[6]
//byte 8 (3 byte) string[7] - Voltage register
//byte 9		  string[8]
//byte 10		  string[9]
//byte 11(3 byte) string[10]- Current parameter register (default)
//byte 12		  string[11]
//byte 13		  string[12]
//byte 14(3 byte) string[13]- Current register
//byte 15		  string[14]
//byte 16		  string[15]
//byte 17(3 byte) string[16] - Power parameter register
//byte 18		  string[17]
//byte 19		  string[18]
//byte 20(3 byte) string[19] - Power register
//byte 21(1 byte) string[20] - Indication of power, voltage, current state
//byte 22		  string[21]
//byte 23(2 byte) string[22] - PF pulse numbers, used in conjunction with state register, not saved after power-fail
//byte 24(1 byte) string[23] - Data check sum, used to verify whether data package is complete in communication

int RecvRawString(const unsigned char * string){

	if (!strcmp(string + 1, 0x5A)){
		return -1; //error code
	}
//	if(string[1] =! 0x5A){
//		return -1; //error code
//	}

	if (Checksum(string) == 0){
		return -2; //Checksum Error
	}

	VolPar = ((uint32_t)string[2] << 16) + ((uint32_t)string[3] << 8) + string[4];

	if(bitRead(string[20],6) == 1){

		VolData = ((uint32_t)string[5] << 16) + ((uint32_t)string[6] << 8) + string[7];

	}

	CurrentPar = ((uint32_t)string[8] << 16) + ((uint32_t)string[9] << 8) + string[10];

	if(bitRead(string[20], 5) == 1)
	{
		CurrentData = ((uint32_t)string[11] << 16) + ((uint32_t)string[12] << 8) + string[13];

	}

	PowerPar = ((uint32_t)string[14]  << 16) + ((uint32_t)string[15] << 8) + string[16];

	if(bitRead(string[20], 4) == 1)
	{
		PowerData = ((uint32_t)string[17]  << 16) + ((uint32_t)string[18] << 8) + string[19];

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
	if (RealVolt < 0) RealVolt = 0.000000001;
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

	if(RaelCurrent < 0)RaelCurrent = 0.000000001;

	return RaelCurrent;
}

float GetActivePower(void){
	float tmp;

	if (PowerData == 0){
		return 0;
	}
	tmp = (float)(PowerPar / PowerData) * VF * CF;

	if (tmp < 0) tmp = 0.000000001;

	return tmp;
}

float GetApparentPower(void){

	float voltage;
	float current;
	float ApparentPower;

	voltage = GetVoltage();
	current = GetCurrent();
	ApparentPower = voltage * current;

	if (ApparentPower < DETECT_POWER_TRASHOLD_W )ApparentPower = 0.000000001;

	return ApparentPower;
}

float PowerFactor(void){

	float ActivePower;
	float ApparentPower;
	float PowerFactor;

	ActivePower 	= GetActivePower();
	ApparentPower	= GetApparentPower();
	if (ApparentPower 	== 0) return 1;
	if (ActivePower 	== 0) return 1;
	if (ActivePower > ApparentPower) return 1.000000000000;
	PowerFactor		= ActivePower / ApparentPower;

	return PowerFactor;
}

uint32_t GetPulsCnF1kWh(){
}

uint32_t GetTestPulse(){
	return test_flag;
}

uint32_t GetCountedPulse(){
	return PFData;
}

uint32_t GetPFReg(){
	return PF_reg;
}

float GetKWh(void){
	float apparentPower;
	float pulseCountFor1kWh;
	float kWh;
	int PFcount;


	apparentPower		= GetApparentPower();
	pulseCountFor1kWh	= (1.0/PowerPar) * (1.0/(VF * CF)) * 1000000000.0 * 3600.0;
	PFcount				= GetTestPulse() * 65536 + GetPFReg();
	//kWh					= (PFData * PF_reg) / (float)pulseCountFor1kWh;
	kWh					= PFcount / (float)pulseCountFor1kWh;
	//     // energy = total_cf_pulses/((1/power_reg)*(1/(VF*CF))*1000000000*3600);
    //energy = total_cf_pulses/((1/(float)power_coefficient)*(1/1.88)*3600000000000);

	if (kWh < 0) kWh = 0.000000001;

	return kWh;
}



/*
 * test.h
 *
 *  Created on: Nov 16, 2023
 *      Author: kirill
 */

#ifndef HLW8032_INC_HLW8032_H_
#define HLW8032_INC_HLW8032_H_

#include "stdint.h"

void InitHLW8032(uint32_t VolR1, uint32_t VolR2, float CurrentShuntR);
void SetVF(float Data);
//uint8_t Checksum(char * string);
int RecvRawString(const unsigned char * string);
float GetVoltage(void);
float GetCurrent(void);
float GetActivePower(void);
float GetApparentPower(void);
float PowerFactor(void);
float GetKWh(void);


//float GetKWh();
uint32_t GetTestPulse();
uint32_t GetCountedPulse();
uint32_t GetPFReg();

#endif /* HLW8032_INC_HLW8032_H_ */

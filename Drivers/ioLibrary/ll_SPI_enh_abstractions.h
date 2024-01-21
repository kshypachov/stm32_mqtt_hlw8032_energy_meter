/*
 * ll_SPI_enh_abstractions.h
 *
 *  Created on: Jan 11, 2024
 *      Author: kirill
 */

#ifndef IOLIBRARY_LL_SPI_ENH_ABSTRACTIONS_H_
#define IOLIBRARY_LL_SPI_ENH_ABSTRACTIONS_H_

#include "stm32f4xx_hal.h"

void Eth_reset_on(void);
void Eth_reset_off(void);
void Eth_spi_select(void);
void Eth_spi_deselect(void);
void Reg_eth_spi(SPI_HandleTypeDef c);
void Eth_spi_send_byte(uint8_t byte);
uint8_t Eth_spi_resv_byte(void);



#endif /* IOLIBRARY_LL_SPI_ENH_ABSTRACTIONS_H_ */

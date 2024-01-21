/*
 * SPI_flash_io.h
 *
 *  Created on: Jan 8, 2024
 *      Author: kirill
 */
#include "stm32f4xx_hal.h"


#ifndef SPI_FLASH_INC_SPI_FLASH_IO_H_
#define SPI_FLASH_INC_SPI_FLASH_IO_H_

void SPI_flash_set(SPI_HandleTypeDef hspi);
uint8_t SPI_flash_read_byte(void);
void SPI_flash_send_byte(uint8_t byte);
void SPI_flash_select(void);
void SPI_flash_deselect(void);

#endif /* SPI_FLASH_INC_SPI_FLASH_IO_H_ */

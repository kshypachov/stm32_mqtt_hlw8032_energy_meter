/*
 * SPI_flash_io.c
 *
 *  Created on: Jan 8, 2024
 *      Author: kirill
 */


#include "SPI_flash_io.h"


SPI_HandleTypeDef spi_interface;

void SPI_flash_set(SPI_HandleTypeDef hspi){
	spi_interface = hspi;
}

uint8_t SPI_flash_read_byte(void){
	uint8_t byte;

	HAL_SPI_Receive(&spi_interface, &byte, 1, 5000);
	return byte;
}


void SPI_flash_send_byte(uint8_t byte){

	HAL_SPI_Transmit(&spi_interface, &byte, 1, 5000);

}

void SPI_flash_select(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
}

void SPI_flash_deselect(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}
/**/

/*
 * ll_SPI_enh_abstractions.c
 *
 *  Created on: Jan 11, 2024
 *      Author: kirill
 */

#include "ll_SPI_enh_abstractions.h"

SPI_HandleTypeDef spi_handler;


void Eth_reset_on(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
}

void Eth_reset_off(void){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
}

void Eth_spi_select(void){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
}

void Eth_spi_deselect(void){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
}

void Reg_eth_spi(SPI_HandleTypeDef hspi){
	spi_handler = hspi;
}

void Eth_spi_send_byte(uint8_t byte){
	HAL_SPI_Transmit(&spi_handler, &byte, 1, 5000);
}

uint8_t Eth_spi_resv_byte(void){
	uint8_t byte;

	HAL_SPI_Receive(&spi_handler, &byte, 1, 5000);
	return byte;
}

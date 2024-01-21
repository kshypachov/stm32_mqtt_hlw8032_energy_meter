/**
  ******************************************************************************
  * @file    spi_flash.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   This file contains all the functions prototypes for the spi_flash
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_spi.h"
//#include "gpio.h"
//#include "spi.h"

//#define USE_SPI_MUTEX

/* Exported types ------------------------------------------------------------*/
 //configuration of spi flash memory
struct SPI_flash_config{

	uint32_t flash_id;

	uint8_t (*receive_byte)(void);

	void (*send_byte)(uint8_t byte);

	void (*select_chip)(void);

	void (*deselect_chip)(void);

#ifdef USE_SPI_MUTEX
	void (*give_mutex)(void);

	void (*release_mutex)(void);
#endif

};

struct SPI_flash_info{

	// Product id of chip
	uint32_t flash_id;
	//Minimum size of a block read in bytes.
	uint16_t read_size;
	//Minimum size of a block program in bytes.
	uint16_t write_size;
	//Size of an erasable block in bytes.
	uint16_t erase_size;
	//Size of page in bytes, max size of bytes for write.
	uint16_t page_size;
	//Number of erasable blocks on the device.
	uint16_t block_count;

};
 /* Exported constants --------------------------------------------------------*/

/* M25P SPI Flash supported commands */
#define sFLASH_CMD_ENABLE_RESET   0x66
#define sFLASH_CMD_RESET          0x99
#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */
#define sFLASH_CMD_SE             0x20  /* Sector 4K Erase instruction */
#define sFLASH_CMD_B32kE          0x52  /* Block 32K Erase instruction */
#define sFLASH_CMD_B64kE		  0xD8	/* Block 64K Erase inctruction */
#define sFLASH_CMD_CE			  0xC7

#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100

#define sFLASH_W25Q16BV_ID		0xef4015
#define sFLASH_W25Q32BV_ID		0xef4016
#define sFLASH_W25Q64BV_ID		0xef4017
#define sFLASH_M25P128_ID		0x202018
#define sFLASH_M25P64_ID        0x202017
#define sFLASH_MX25L32xxx_ID	0xc22016  //not recomended, Macronix use the same JEDEC ID for different chips
#define sFLASH_UNNOUN_ID		0x000000



/* High layer functions  */

void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_EraseBlock32k(uint32_t SectorAddr);
void sFLASH_EraseBulk(void);
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
void sFLASH_StartReadSequence(uint32_t ReadAddr);
struct SPI_flash_info sFLASH_GetInfo(void);

/* Low layer functions */
void SPI_flash_reg_cb(void (*chip_select)(void), void (*chip_deselect)(void), uint8_t (*receive_byte)(void), void (*send_byte)(uint8_t));
void SPI_flash_io_init(void);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);
void flash_reg_cb_mutex_functions(void(*mutex_give_f)(void), void(*mutex_release_f)(void));

#ifdef __cplusplus
}
#endif

#endif /* __SPI_FLASH_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

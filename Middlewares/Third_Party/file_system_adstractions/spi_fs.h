/*
 * spi_fs.h
 *
 *  Created on: 15 ���. 2023 �.
 *      Author: kirill
 */

#ifndef HIGH_LEVEL_ABSTRACTIONS_FILE_SYSTEM_ADSTRACTIONS_SPI_FS_H_
#define HIGH_LEVEL_ABSTRACTIONS_FILE_SYSTEM_ADSTRACTIONS_SPI_FS_H_

#define PATH_BUF_SIZE 128

#include "stdio.h"
#include "stdint.h"

void spi_fs_init_mutex(void (*get_mutex)(void), void (*release_mutex)(void));
int spi_fs_init(uint8_t * lfsReadBuff, uint8_t * lfsWriteBuff, uint8_t * lfslookaheadBuff, uint16_t buffers_size);
int spi_fs_mount(void);
int spi_fs_read_file(const char *path, void *buffer, uint32_t read_size);
int spi_fs_read_file_offset(const char *path, void *buffer, uint32_t offset, uint32_t read_size);
int spi_fs_over_write_file(const char *path, void *buffer, uint32_t write_size);
void spi_fs_format(void);
int spi_fs_file_size(const char *path);
int spi_fs_write_file_to_end(const char *path, void *buffer, uint32_t write_size);
int spi_fs_serch_file_in_dir(const char * dir_path, const char * filename);
int spi_fs_mkdir(const char *path);
int spi_fs_read_dir(const char *path);
void list_files_and_directories(const char *path);
void spi_fs_remove_recurcuve_in (const char *path);
int spi_fs_mv(const char *oldpath, const char *newpath);

#endif /* HIGH_LEVEL_ABSTRACTIONS_FILE_SYSTEM_ADSTRACTIONS_SPI_FS_H_ */

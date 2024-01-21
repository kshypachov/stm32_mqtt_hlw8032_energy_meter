/*
 * lfs_config.c
 *
 *  Created on: 10 ���. 2023 �.
 *      Author: kir
 */
#include "lfs_config.h"
#include "lfs.h"
#include "SPI_flash.h"
//#include "definition.h"

#ifndef FLASH_BLOCK_CYCLES
	#define FLASH_BLOCK_CYCLES 10000
#endif

int block_device_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int block_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int block_device_erase(const struct lfs_config *c, lfs_block_t block);
int block_device_sync(const struct lfs_config *c);

int (* lfs_lock)(const struct lfs_config *c);
int (* lfs_unlock)(const struct lfs_config *c);

#ifdef LFS_THREADSAFE

void reg_dev_lock_unlock(void * lock(void), void * unlock(void)){

}

#endif

int io_fs_init(uint8_t * lfsReadBuff, uint8_t * lfsWriteBuff, uint8_t * lfslookaheadBuff, uint16_t buffers_size, struct lfs_config *cfg)
{
	struct SPI_flash_info  flash_info;

	flash_info = sFLASH_GetInfo();

    cfg->read_size   = flash_info.read_size;
    cfg->prog_size   = flash_info.write_size;

    cfg->block_size  = flash_info.erase_size;
    cfg->block_count = flash_info.block_count;

    cfg->lookahead_size = buffers_size;
    cfg->cache_size     = buffers_size;
    cfg->read_buffer = lfsReadBuff;
    cfg->prog_buffer = lfsWriteBuff;
 //   cfg.file_buffer = lfsReadBuff;
    cfg->lookahead_buffer = lfslookaheadBuff;

    cfg->read   = block_device_read;
    cfg->prog   = block_device_prog;
    cfg->erase  = block_device_erase;
    cfg->sync   = block_device_sync;

#ifdef LFS_THREADSAFE
	cfg.lock 	= lfs_lock;
	cfg.unlock	= lfs_unlock;
#endif

    cfg->block_cycles 	= FLASH_BLOCK_CYCLES;
    cfg->name_max  		= LFS_NAME_MAX;
    cfg->file_max		= LFS_FILE_MAX;
    cfg->attr_max		= LFS_ATTR_MAX;
    cfg->metadata_max	= flash_info.erase_size;

    return 0;
}

int block_device_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size){
#ifndef LFS_NO_ASSERT
	assert(block < c->block_count);
#endif
	sFLASH_ReadBuffer((uint8_t*)buffer, ((block) * (c->block_size) + off), size);
	return 0;
}

int block_device_erase(const struct lfs_config *c, lfs_block_t block){
#ifndef LFS_NO_ASSERT
	assert(block < c->block_count);
#endif
	sFLASH_EraseSector(block * (c -> block_size));
	return 0;
}

int block_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size){
#ifndef LFS_NO_ASSERT
	assert(block < c->block_count);
#endif
	sFLASH_WriteBuffer((uint8_t*)buffer, ((block) * (c->block_size) + off), size);
	return 0;
}

int block_device_sync(const struct lfs_config *c){
	return 0;
}

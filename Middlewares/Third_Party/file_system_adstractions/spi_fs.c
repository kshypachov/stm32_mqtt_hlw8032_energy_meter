/*
 * spi_fs.c
 *
 *  Created on: 15 ���. 2023 �.
 *      Author: kirill
 */

#include "spi_fs.h"

#include "SPI_flash.h"
#include "lfs_config.h"
#include "definition.h"

#ifndef LFS_BUF_SIZE
#define LFS_BUF_SIZE 512
#endif

uint8_t							lfs_file_buf[LFS_BUF_SIZE]; 					// buffer for file W/R
uint8_t 						fs_mount_flag = 0;
lfs_t 							lfs;
lfs_file_t						file;
lfs_dir_t 						dir;
struct lfs_info 				file_info;
struct lfs_config				cfg;
struct SPI_flash_info			flash_parameters;
static struct lfs_file_config	fileConf;
uint8_t 						temp_buf[PATH_BUF_SIZE] = {0x00, };


//int (* lfs_lock)(const struct lfs_config *c);
//int (* lfs_unlock)(const struct lfs_config *c);

void (* FSMutexGet)		(void);
void (* FSMutexRelease)	(void);

void spi_fs_init_mutex(void (*get_mutex)(void), void (*release_mutex)(void)){

	if (get_mutex) FSMutexGet = get_mutex;
	if (release_mutex) FSMutexRelease = release_mutex;

};

int spi_fs_init(uint8_t * lfsReadBuff, uint8_t * lfsWriteBuff, uint8_t * lfslookaheadBuff, uint16_t buffers_size){

	flash_parameters = sFLASH_GetInfo();
	if (flash_parameters.flash_id == 0x0) return -1;

	io_fs_init(lfsReadBuff, lfsWriteBuff, lfslookaheadBuff, buffers_size, &cfg);

	memset(&fileConf, 0, sizeof(struct lfs_file_config));
	fileConf.buffer = lfs_file_buf;  						// use the static buffer
	fileConf.attr_count = 0;

	return 0;
}

int spi_fs_mount(void){
	int err;

#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif
	err = lfs_mount(&lfs, &cfg);
	if (err) {
		fs_mount_flag = 0;
	}else{
		fs_mount_flag = 1;
	}
#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif

	return err;
}

int spi_fs_mount_status(void){

	return fs_mount_flag;
}

void spi_fs_format(void){
	lfs_format(&lfs, &cfg);
}

int spi_fs_read_file(const char *path, void *buffer, uint32_t read_size){
	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err =	lfs_file_opencfg(&lfs, &file, path, LFS_O_RDONLY | LFS_O_CREAT, &fileConf);
	if (err < 0) goto func_end;
	err =	lfs_file_read(&lfs, &file, buffer, read_size);
	if (err < 0) goto func_end;

	func_end:
	lfs_file_close(&lfs, &file);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

int spi_fs_read_file_offset(const char *path, void *buffer, uint32_t offset, uint32_t read_size){
	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif
	err =	lfs_file_opencfg(&lfs, &file, path, LFS_O_RDONLY | LFS_O_CREAT, &fileConf);
	if (err < 0) goto func_end;
	err =	lfs_file_seek(&lfs, &file, offset, LFS_SEEK_SET);
	if (err < 0) goto func_end;
	err =	lfs_file_read(&lfs, &file, buffer, read_size);
	if (err < 0) goto func_end;

	func_end:
	lfs_file_close(&lfs, &file);
#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;

}

int spi_fs_over_write_file(const char *path, void *buffer, uint32_t write_size){
	int err = 0;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_file_opencfg(&lfs, &file, path, LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC, &fileConf);
	if (err < 0) goto func_end;
	err = lfs_file_write(&lfs, &file, buffer, write_size);
	if (err < 0) goto func_end;

	func_end:
	lfs_file_close(&lfs, &file);
#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

int spi_fs_file_size(const char *path){
	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_stat(&lfs, path, &file_info);
	if (err == 0){
		err = file_info.size;
	}

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

int spi_fs_write_file_to_end(const char *path, void *buffer, uint32_t write_size){
	int err = 0;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_file_opencfg(&lfs, &file, path, LFS_O_RDWR | LFS_O_CREAT | LFS_O_APPEND, &fileConf);
	if (err < 0) goto func_end;
	err = lfs_file_write(&lfs, &file, buffer, write_size);
	if (err < 0) goto func_end;

	func_end:
	lfs_file_close(&lfs, &file);
#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

int spi_fs_serch_file_in_dir(const char * dir_path, const char * filename){


	int err;
	memset(temp_buf, 0x0, PATH_BUF_SIZE);
	strcpy((char *)temp_buf, dir_path);
	strcat((char *)temp_buf, filename);
	err = spi_fs_file_size((const char *)temp_buf);
	return err;

}

int spi_fs_mkdir(const char *path){
	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_mkdir(&lfs, path);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif

	return err;
}

int spi_fs_read_dir(const char *path){
	lfs_dir_open(&lfs, &dir, path);
	lfs_dir_read(&lfs, &dir, &file_info);
	lfs_dir_close(&lfs, &dir);

}

int spi_fs_file_exist(const char *path){

}

int spi_fs_file_cr_emp(const char *path){


}

int spi_fs_file_info(const char *path, struct lfs_info *info){
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif

}

int spi_fs_remove(const char *path){
	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_remove(&lfs, path);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

int spi_fs_get_file_size(const char *path){

	int err;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err =	lfs_file_opencfg(&lfs, &file, path, LFS_O_RDONLY , &fileConf);
	err =	lfs_file_size(&lfs, &file);
	lfs_file_close(&lfs, &file);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}

void list_files_and_directories(const char *path) {

    struct lfs_info info;
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif
    if (lfs_dir_open(&lfs, &dir, path) == 0) {
        // Iterate through the directory entries
        while (lfs_dir_read(&lfs, &dir, &info) > 0) {
            if (info.type == LFS_TYPE_DIR) {
            	if ( (strcmp(info.name, ".")==0)||(strcmp(info.name, "..")==0)) continue;
                printf("Directory: %s\n", info.name);
                char sub_path[256];  // Adjust the size based on your needs
                snprintf(sub_path, sizeof(sub_path), "%s/%s", path, info.name);
                lfs_dir_close(&lfs, &dir);
                list_files_and_directories(sub_path);  // Recursive call for subdirectories
            } else {
                printf("File: %s\n", info.name);
            }
        }
        lfs_dir_close(&lfs, &dir);
    }
#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
}

void remove_recursively_files_and_directories(const char *path) {

    struct lfs_info info;

    if (lfs_dir_open(&lfs, &dir, path) == 0) {
        // Iterate through the directory entries
        while (lfs_dir_read(&lfs, &dir, &info) > 0) {
            if (info.type == LFS_TYPE_DIR) {
            	if ( (strcmp(info.name, ".")==0)||(strcmp(info.name, "..")==0)) continue;
                printf("Directory: %s\n", info.name);
                char sub_path[256];  // Adjust the size based on your needs
                snprintf(sub_path, sizeof(sub_path), "%s/%s", path, info.name);
                lfs_dir_close(&lfs, &dir);
                remove_recursively_files_and_directories(sub_path);  // Recursive call for subdirectories
            } else {
            	char sub_path2[256];
                printf("File: %s\n", info.name);
                snprintf(sub_path2, sizeof(sub_path2), "%s/%s", path, info.name);
                lfs_remove(&lfs, sub_path2);
            }
        }
        lfs_dir_close(&lfs, &dir);
        lfs_remove(&lfs, path);
    }

}

void spi_fs_remove_recurcuve_in (const char *path){
#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	remove_recursively_files_and_directories(path);
	remove_recursively_files_and_directories(path);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
}

int spi_fs_mv(const char *oldpath, const char *newpath){
	int err;

#ifdef LFS_USE_MUTEX
	FSMutexGet();
#endif

	err = lfs_rename(&lfs, oldpath, newpath);

#ifdef LFS_USE_MUTEX
	FSMutexRelease();
#endif
	return err;
}


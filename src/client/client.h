#pragma once

#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

#include "../shared.h"

#define mkeyPressed(k) (*bd.keys & k)

struct bd {
	uint8_t * buffer;
	uint8_t * keys;
	int	      width;
	int       height;
	int       pages;
	size_t    size;
};

static inline uint8_t bindisInit(struct bd * bd){
	int mainfd, keyfd;
	
	if (bd->width == 0 || bd->height == 0){
		printf("Please set a non-zero value to width and height equal to the ones on your config file\n");
		return 1;
	} 

	mainfd = shm_open(SHM_MAIN,	O_RDWR,	0);
	if (mainfd == -1){
		perror("Shared memmory (main)"); 
		return 1;
	} 

	keyfd =  shm_open(SHM_KEYS, O_RDWR, 0);
	if (keyfd == -1){
		perror("Shared memmory (keys)");
		return 1;
	} 
	
	bd->pages = bd->height / CHAR_BIT;
	bd->size = bd->width * bd->pages;

	bd->buffer = (uint8_t *) mmap(
								NULL,
								bd->size,
								PROT_READ | PROT_WRITE,
								MAP_SHARED,
								mainfd, 0
								);
	bd->keys = 	 (uint8_t *) mmap(
								NULL,
								1,
								PROT_READ | PROT_WRITE,
								MAP_SHARED,
								keyfd, 0
								);

	close(mainfd);
	close(keyfd);
	return 0;
}

static inline uint8_t keyPressed(uint8_t key, struct bd bd){
	if (*bd.keys & key) return 1;
	else return 0;
}


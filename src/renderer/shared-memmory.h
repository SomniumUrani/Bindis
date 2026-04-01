#pragma once


#include "../common/user.h"

#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//shared memory

static inline int memshareInit(int * mainfd, int * keysfd){

main:
	*mainfd = shm_open(
			SHM_MAIN,
			O_CREAT | O_EXCL | O_RDWR,
//			S_IRUSR | S_IWUSR);
			0666);

	if (*mainfd == -1){
		if (errno == EEXIST){
			shm_unlink(SHM_MAIN); 
			goto main;
		}
		else return 1;
	}

keys:

	*keysfd = shm_open(
			SHM_KEYS,
			O_CREAT | O_EXCL | O_RDWR,
//			S_IRUSR | S_IWUSR);
			0666);
	if (*keysfd == -1){
		if (errno == EEXIST){
			shm_unlink(SHM_KEYS);
			goto keys;
		}
		else return 1;
	}

	return 0;

}




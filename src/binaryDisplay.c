#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <termios.h>
#include <pthread.h>


#include "headers/defs.h"
#include "headers/dataTrans.h"
#include "headers/renderer.h"
#include "headers/mini.h"
#include "headers/config.h"

int main(int agrc, char * argv[]){
	int isError = 0;
	struct config config;
	struct termios newt, oldt;
	struct winsize wnsize;
	uint8_t keysBuffer = 0;
	config.InputInterval = config.Updateinterval;
	int mainfd, keysfd;


	//Init things
	isError =  		configure(&config);
	if (isError) goto end;
	off_t size = config.width * config.height / CHAR_BIT;

	isError = (! 	isatty(STDOUT_FILENO));
	if (isError) goto end;

	isError = 		memshareInit(&mainfd, &keysfd);
	if (isError) goto end;

	isError = 		ftruncate(mainfd, size);
	if (isError) goto end;

	isError = 		ftruncate(keysfd, 1);
	if (isError) goto end;

	isError = 		initTerminal(&newt, &oldt);
	if (isError) goto end;
	
	//memory mapping
	uint8_t * buffer = 
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			mainfd, 0
			);
	uint8_t * keysMemory = 
		mmap(
			NULL,
			1,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			keysfd, 0
			);

	//thread stuff
	keyManagerArgs keyManagerArgs = {
		keysMemory,
		&config.binds,
		&config.InputInterval
	};
	pthread_t keyManagementThread;
	isError = 		pthread_create(&keyManagementThread, NULL, keysManager, (void*) &keyManagerArgs);
	if (isError) goto end;

	uint8_t xdtest[] = {0xC2, 0xff, 0b11111101};


	while (!(*keysMemory & KEY_Q)){
		isError = updateTerminal(
				buffer,
				config,
				size,
				&wnsize
				);

		if (isError){
			pthread_cancel(keyManagementThread);
			goto end;
		} 
		nanosleep(&config.Updateinterval, NULL);
	}



end:
	pthread_join(keyManagementThread, NULL);
	shm_unlink(SHM_MAIN);
	if ( (isError != 2) || (isError != 3) ) finishTerminal(&oldt);
	finishTerminal(&oldt);

	close(mainfd);
	close(keysfd);




	switch (isError) {
		case 1:
			printf("something failed :(\n");
			break;
		case 2:
			printf("Check your config file\n");
			break;
		case 3:
			printf("Do u have a config file?\n");
			break;
		case 4:
			printf("Not enough space in terminal for your dimentions\n");
			printf("\tTerminal\tConfig\n"
					"Width\t%i\t\t%u\n"
					"Height\t%i\t\t%u\n",
					wnsize.ws_col, config.width,
					wnsize.ws_row*2, config.height
					);
			break;
	
	}
	return isError;
}

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "renderer.h"


int8_t updateTerminal(
			uint8_t * buffer,
			struct config config,
			uint32_t bufferBytes,
			struct winsize * wnsize
			){

	ioctl(STDOUT_FILENO, TIOCGWINSZ, wnsize);

	if (
			wnsize->ws_col < config.width 
			||
			wnsize->ws_row < (config.height/2) 
			){
		return 4;
	}

	printf("\033[2J"); 		//cleans screen
	printf(ANSIESC_HOME);
	
	int xd = 1, tmp = 0;
	int top, bott;
	

	for (uint32_t i = 0; i < bufferBytes; i++){
		tmp = buffer[i];

		for (uint8_t a = 0; a < BYTE_SIZE / 2; a++){
			top  = 	(tmp & 0b01);
			bott = 	(tmp & 0b10);
			tmp >>= 2;

			//box drawing characters
			if 	    ( top  &&  bott) 	printf(UNIC_BLOCKFULL 	ANSIESC_CLEFT);
			else if ( top  && !bott)	printf(UNIC_BLOCKUP 	ANSIESC_CLEFT);
			else if (!top  &&  bott) 	printf(UNIC_BLOCKLOW 	ANSIESC_CLEFT);
			printf(ANSIESC_CDOWN);

			fflush(stdout);
//			usleep(40000);/*debug*/
		}

		switch (config.adrsmode) {
 			case ADR_H:
				if (i % config.width == 0 && i != 0) {
					printf(ANSIESC_HABSOLUTE);
				} else {
					printf(ANSIESC_CRIGHT);
					printf(ANSIESC_CUPX4);
				}
				break;
			case ADR_V:
				if ( ( (i+1)*BYTE_SIZE) % config.height == 0 && i != 0) {
					printf("\033[%iA", i*BYTE_SIZE);
					printf(ANSIESC_CRIGHT);
//					printf("\033[2J"); 		/*debug*/
				}
				break;
		}
		fflush(stdout);


	}

	return 0;
}

int8_t initTerminal(
		struct termios * newt,
		struct termios * oldt
		){
	printf(
			"\033[?1049h" 		//alternate buffer
			"\033[?25l" 		//hide cursor
			ANSIESC_HOME
			);
	fflush(stdout);

	//disable echo & canon
	tcgetattr(STDIN_FILENO, oldt);
	*newt = *oldt;
	newt->c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, newt);
	tcflush(STDIN_FILENO, TCIFLUSH);
	
	//disable input blockin
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (flags == -1) return 1;
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	return 0;
}

void finishTerminal(
			struct termios * oldt
			){

	printf(
			"\033[?1049l"		//back to normal buffer
			"\033[?25h" 		//show cursor
			);
	fflush(stdout);
	tcsetattr( STDIN_FILENO, TCSANOW, oldt);
	tcflush(STDIN_FILENO, TCIFLUSH);
}

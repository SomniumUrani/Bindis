#pragma once

#include <stdint.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "user.h"

//I gotta check if there are more adressing modes, for now this is for SSD1306

#define ADR_H 0
#define ADR_V 1

#define ANSIESC_CUP 		"\033[1A"
#define ANSIESC_CDOWN 		"\033[1B"
#define ANSIESC_CRIGHT		"\033[1C"
#define ANSIESC_CLEFT 		"\033[1D"

#define ANSIESC_CUPX4 		"\033[4A"
#define ANSIESC_CDOWNX4		"\033[4B"
#define ANSIESC_CRIGHTX4	"\033[4C"
#define ANSIESC_CLEFTX4		"\033[4D"

#define ANSIESC_HABSOLUTE	"\033[1G"
#define ANSIESC_VABSOLUTE	"\033[1d"

#define ANSIESC_HOME 		"\033[H"


#define UNIC_BLOCKUP 		"\u2580"
#define UNIC_BLOCKLOW 		"\u2584"
#define UNIC_BLOCKFULL 		"\u2588"


int8_t updateTerminal(
			uint8_t * buffer,
			struct config config,
			uint32_t bufferBytes,
			struct winsize * wnsize);
int8_t initTerminal(
		struct termios * newt,
		struct termios * oldt
		);
void finishTerminal(
			struct termios * oldt
			);

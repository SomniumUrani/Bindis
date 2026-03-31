#pragma once
#include <stdint.h>
#include <time.h>

#include "../shared.h"



struct binds {
	char keyQ;
	char keyA;
	char keyB;
	char keyC;
	char keyD;
	char keyE;
	char keyF;
	char keyG;
};

struct config {
	uint32_t width;
	uint32_t height;
	uint8_t  adrsmode;	
	struct timespec Updateinterval;
	struct timespec InputInterval;
	struct binds binds;
};

typedef struct {
	uint8_t * keys;
	struct binds * binds;
	struct timespec * inputInterval;
} keyManagerArgs;


#define FCONFIG "config"

void * keysManager(void * arguments);
int8_t configure(struct config * config);

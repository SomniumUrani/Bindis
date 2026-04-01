#pragma once
#include <stdint.h>
#include <time.h>

#include "shared.h"



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
	int width;
	int height;
	int  adrsmode;	
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
int configure(struct config * config);

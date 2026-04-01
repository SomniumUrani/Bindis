#pragma once
#include <stdint.h>
#include "gui.h"

struct gkeys{
	int key_q;
	int key_a;
	int key_b;
	int key_c;
	int key_d;
	int key_e;
	int key_f;
	int key_g;
};

void gkeymanager(struct gkeys keys, uint8_t * shkeys);
void localConfig(struct gkeys * keys, struct guiconfig * guiconfig);
void update(void);
void setup(void);

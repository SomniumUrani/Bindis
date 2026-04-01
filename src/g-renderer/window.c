#include <raylib.h>
#include <stdint.h>
#include "window.h"
#include "../renderer/user.h"
#include "deambiguation.h"

void gkeymanager(struct gkeys keys, uint8_t * shkeys){
	*shkeys = 0;
	if (IsKeyDown(keys.key_q)) *shkeys |= BD_KEY_Q;
	if (IsKeyDown(keys.key_a)) *shkeys |= BD_KEY_A;
	if (IsKeyDown(keys.key_b)) *shkeys |= BD_KEY_B;
	if (IsKeyDown(keys.key_c)) *shkeys |= BD_KEY_C;
	if (IsKeyDown(keys.key_d)) *shkeys |= BD_KEY_D;
	if (IsKeyDown(keys.key_e)) *shkeys |= BD_KEY_E;
	if (IsKeyDown(keys.key_f)) *shkeys |= BD_KEY_F;
	if (IsKeyDown(keys.key_g)) *shkeys |= BD_KEY_G;
}

void localConfig(struct gkeys * keys){
	keys->key_q = KEY_X;
}

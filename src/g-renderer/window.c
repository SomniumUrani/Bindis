#include <raylib.h>
#include <stdint.h>
#include "window.h"
#include "../common/user.h"

#include "gui.h"

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

void localConfig(struct gkeys * keys, struct guiconfig * guiconfig){
	keys->key_q = KEY_Q;
	keys->key_a = KEY_A;
	keys->key_b = KEY_B;
	keys->key_c = KEY_C;
	keys->key_d = KEY_D;
	keys->key_e = KEY_E;
	keys->key_f = KEY_F;
	keys->key_g = KEY_G;

	guiconfig->scale = 3;
}

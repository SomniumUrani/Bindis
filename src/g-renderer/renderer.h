#pragma once
#include <stdint.h>
#include "gui.h"

#define ADR_H 0
#define ADR_V 1


void updateRenderer(long size, uint8_t * buffer, struct config config, struct guiconfig guiconfig);

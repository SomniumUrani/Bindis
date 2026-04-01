#pragma once

#include <raylib.h>

struct guiconfig{
	int scale;
};

void drawGUI(struct guiconfig * guiconfig);

#pragma once

#include <raylib.h>
#include "../common/user.h"


struct guiconfig{
	int scale;
	Color vdisColor;
};

void drawGUI(struct guiconfig * guiconfig, struct config * config);
Rectangle getElementDimensions(int index, int panelWidth, int elementH);

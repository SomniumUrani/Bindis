#include <raylib.h>

#include "raygui/src/raygui.h"
#include "gui.h"



void drawGUI(struct guiconfig * guiconfig){
	int screenW = GetScreenWidth();
	int screenH = GetScreenHeight();
	int panelhOffset = screenW*0.01;
	int panelWidth = screenW * 0.2;

	int elementHeight = screenH / 40;

	GuiPanel( (Rectangle){0, 0, panelWidth, screenH} , "Options");
	GuiSpinner( (Rectangle){panelWidth / 3, 30, panelWidth * 0.66, elementHeight} , "Scale", &guiconfig->scale, 1, 10, 1);

}

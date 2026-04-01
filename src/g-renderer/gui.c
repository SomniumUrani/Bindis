#include <raylib.h>

#include "raygui/src/raygui.h"
#include "gui.h"
#include "../common/user.h"

void drawGUI(struct guiconfig * guiconfig, struct config * config){
	int screenW = GetScreenWidth();
	int screenH = GetScreenHeight();
	int panelhOffset = screenW*0.01;
	int panelWidth = screenW * 0.2;

	int elementHeight = screenH / 40;
	char * adrString;

	GuiPanel( (Rectangle){0, 0, panelWidth, screenH} , "Options");
	GuiSpinner( 
			getElementDimensions(0, panelWidth, elementHeight) , 
			"Scale", &guiconfig->scale, 1, 10, 1);
	if (
			GuiButton(getElementDimensions(1, panelWidth, elementHeight), "Toggle adressing")) 
	{
		config->adrsmode = !config->adrsmode;
	}
	if (config->adrsmode){
		adrString = "Vertical";
	} else {
		adrString = "Horizontal";
	}
	GuiLabel(getElementDimensions(2, panelWidth, elementHeight), adrString);
	GuiLabel(getElementDimensions(3, panelWidth, elementHeight), "Light Color");
	GuiColorPicker( (Rectangle) {panelhOffset, screenH / 2, panelWidth * 0.7, elementHeight*6}
			, "Light Color", &guiconfig->vdisColor);

}

Rectangle getElementDimensions(int index, int panelWidth, int elementH){
	int x = panelWidth / 3;
	int y = 
		//First offset
		30 +
		//Element x height
		(elementH + 10) * index;
	int w = panelWidth * 0.66;
	int h = elementH;

	return (Rectangle) {x, y, w, h};


}


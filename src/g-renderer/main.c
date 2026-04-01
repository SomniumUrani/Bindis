#include <raylib.h>
#include <unistd.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"

#include "../common/user.h"
#include "../renderer/shared-memmory.h"
#include "window.h"
#include "renderer.h"
#include "gui.h"


int main(void){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(200, 200, "BINDIS GRAPHICAL");
	SetTargetFPS(60);


	struct config config;
	struct guiconfig guiconfig;
	RenderTexture2D virtualDisplay;
	struct gkeys realkeys;

	configure(&config);
	virtualDisplay = LoadRenderTexture(config.width, config.height);
	localConfig(&realkeys, &guiconfig);
	off_t size = config.width * config.height / 8 /*byte size*/;


	int mainfd, keysfd;
	memshareInit(&mainfd, &keysfd);
	ftruncate(mainfd, size);
	ftruncate(keysfd, 1);

	//memory mapping
	uint8_t * buffer = 
		mmap(
			NULL,
			size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			mainfd, 0
			);
	uint8_t * keysMemory = 
		mmap(
			NULL,
			1,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			keysfd, 0
			);

	while(!WindowShouldClose()) {
		gkeymanager(realkeys, keysMemory);
		BeginTextureMode(virtualDisplay);
		ClearBackground(BLACK);

		updateRenderer(size, buffer, config);

		EndTextureMode();
		//----------------
		BeginDrawing();
		ClearBackground(WHITE);
		Rectangle origin = { 
	            0.0f, 
	            0.0f, 
	            (float)virtualDisplay.texture.width, 
	            (float)-virtualDisplay.texture.height 
	        };
		Rectangle target = { 
	            (GetScreenWidth()  - config.width * guiconfig.scale) / 2.0f, 
	            (GetScreenHeight() - config.height * guiconfig.scale) / 2.0f, 
	            (float)config.width  * guiconfig.scale, 
	            (float)config.height * guiconfig.scale 
	        };
		DrawTexturePro(virtualDisplay.texture, origin, target, (Vector2){ 0, 0 }, 0.0f, WHITE);


		drawGUI(&guiconfig, &config);
	
		EndDrawing();
	}

	shm_unlink(SHM_MAIN);
	shm_unlink(SHM_KEYS);
	close(mainfd);
	close(keysfd);

	return 1;
}




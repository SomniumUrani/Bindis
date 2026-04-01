#include <raylib.h>
#include <unistd.h>
#include <string.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"

#include "../renderer/user.h"
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


	memcpy(buffer, (uint8_t[]){0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00, 0xF9, 0x00, 0x00, 0xFE, 0x04, 0x0C, 0x08, 0x18, 0xF0, 0x00, 0x00, 0xFF, 0x81, 0x81, 0x42, 0x3C, 0x00, 0x00, 0xF9, 0x00, 0x00, 0x86, 0x89, 0x89, 0x71}, 32);


	while(!WindowShouldClose()) {
		gkeymanager(realkeys, keysMemory);
		BeginTextureMode(virtualDisplay);
		ClearBackground(BLACK);

		updateRenderer(size, buffer, config);

		DrawPixel(20, 20, WHITE);
		DrawCircle(20, 20, 5, RED);




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


		drawGUI(&guiconfig);
	
		EndDrawing();
	}

	shm_unlink(SHM_MAIN);
	shm_unlink(SHM_KEYS);
	close(mainfd);
	close(keysfd);

	return 1;
}




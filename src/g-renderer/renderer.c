#include <raylib.h>
#include <stdint.h>

#include "../renderer/user.h"

#include "renderer.h"

void updateRenderer(long size, uint8_t * buffer, struct config config){
	int pages = 8;
	int x = 0, y = 0;



	for (int a = 0; a < size; a++){
		uint8_t byteBuffer = buffer[a];
		for (int b = 0; b < 8; b++){
			if (byteBuffer & 0b1) DrawPixel(x, y, WHITE);
			y++;
			byteBuffer >>= 1;
		}

		switch(config.adrsmode){
			case(ADR_H):
				if (a % config.width == 0 && a != 0){
					x=0;
				} else{
					y = y-8;
					x = x+1;
				}
				break;
			case(ADR_V):
				if ( ( (a+1)* 8) % config.height == 0 && a != 0){
					x = x+1;
					y = 0;
				}
		}
		
	}

}

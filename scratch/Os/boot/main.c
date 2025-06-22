#include "graphics.h"

int start(){
	char string[]= "this is test";
	char* ptr = string;
	while(1){
		ClearScreen(181.0f/255.0f*16.0f,232.0f/255.0f*32.0f,255.0f/255.0f*16.0f);
		DrawString(getArialCharacter,font_arial_width,font_arial_height,ptr,10,10,0,0,0);
		Flush();
	};
}



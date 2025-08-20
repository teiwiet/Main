#include "graphics.h" 

int start(){
	char s[] = "TURN INTO SOMETHING BEAUTIFUL";
	char *p = s;
	while(1){
		ClearScreen1(255,0,0);
		DrawString(getArialCharacter,0,0,s,font_arial_width,font_arial_height,0,255,0);
		Flush();
	};
}


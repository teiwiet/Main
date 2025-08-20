#include "graphics.h"

int rgb(int r,int g,int b){
	r = r/3;
	g = g/2;
	b = b/3;
	return r<<11|g<<5|b;
};

void Draw(int x,int y,int r,int g,int b){
	VBEInfoBlock* VBE = VBEInfoAddress;
	int index = y*VBE->width + x;
	*((unsigned short*)VBE->framebuffer + index) = rgb(r,g,b);
};

void ClearScreen(int r,int g,int b){
	
};

void DrawRect(int x,int y,int width,int height,int r,int g,int b);
void DrawCharacter();
void DrawString();

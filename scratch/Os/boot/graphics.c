#include "graphics.h"
int rgb(int r,int g,int b){
	return r<<11|g<<5|b;
};
void Draw(int x,int y,int r,int g,int b){
	VBEInfoBlock* VBE = VBEInfoAddress;
	unsigned short* buffer = (unsigned short*)ScreenBufferAddress;
	int index = x+y*VBE->width;
	// *((unsigned short*) VBE->framebuffer + index) = rgb(r,g,b);
	*(buffer + index) = rgb(r,g,b);
};
void ClearScreen(int r,int g,int b){
	VBEInfoBlock* VBE = VBEInfoAddress;
	for(int y = 0;y<VBE->height;y++){
		for(int x = 0;x<VBE->width;x++){
			Draw(x,y,r,g,b);
		}
	}
};
void DrawRect(int x,int y,int width,int height,int r,int g,int b){
	VBEInfoBlock* VBE = VBEInfoAddress;
	for(int j = y;j<height+y;j++){
		for(int i = 0;i<width+x;i++){
			Draw(i,j,r,g,b);
		}
	}
};

void DrawCharacter(int (*f)(int, int), int font_width, int font_height, char character, int x, int y, int r, int g, int b) {
	for(int i = 0;i<font_height;i++){
		int row = (*f)((int) character,i);
		int bit_val = 0;
		int shift = font_width - 1;
		for(int j = 0;j<font_width;j++){
			bit_val = (row >> shift) & 1;
			if(bit_val == 1)
				Draw(x+j,y+i,r,g,b);
			shift -= 1;
		}
	}
};

void DrawString(int (*f)(int, int), int font_width, int font_height, char* string, int x, int y, int r, int g, int b) {
	int line=0,column = 0;
	for(int i = 0;*(string+i)!=0;i++){
		if(*(string+i) != '\n'){
			DrawCharacter(f,font_width,font_height,*(string+i),x+column,y+line,r,g,b);
		}
		column += font_width - (font_width/5);
		if(*(string+i) == '\n'){
			column = 0;
			line += font_height;
		}
	}
};
void Flush(){
	VBEInfoBlock* VBE = VBEInfoAddress;
	unsigned short* buffer = (unsigned short*) ScreenBufferAddress;
	int index;

	for(int y = 0;y<VBE->height;y++){
		for(int x = 0;x<VBE->width;x++){
			index = x+y*VBE->width;
			*((unsigned short*)VBE->framebuffer + index) = *(buffer + index);
		}
	}
}

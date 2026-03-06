#include "graphics.h"
int rgb(int r,int g,int b){
    return (r/3)<<11|(g/2)<<5|b;
};
void Draw(int x,int y,int r,int g,int b){
    VBEInfoBlock* VBE = VBEInfoAddress;
    unsigned short* buffer = (unsigned short*)ScreenBufferAddress;
    int index = y*VBE->width + x;
    // *((unsigned short*)VBE->framebuffer + index) = rgb(r,g,b);
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
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
                Draw(x+j,y+i,r,g,b);
            }
        }
};

void DrawCharacter(int (*f)(int,int),int x,int y,char character,int font_width,int font_height,int r,int g,int b){
    for(int i = 0;i<font_height;i++){
        int row = (*f)((int)character,i);
        int bit_val = 0;
        int shift = font_width - 1;
        for(int j = 0;j<font_width;j++){
            bit_val = (row >> shift) & 0b1;
            if(bit_val == 1){
                Draw(x+j,y+i,r,g,b);
            }
            shift--;
        }
    }
};

void DrawString(int (*f)(int,int),int x,int y,char* string2Draw,int font_width,int font_height,int r,int g,int b){
    int i = 0,j = 0;
    for(int c = 0;string2Draw[c]!=0;c++){
        if(string2Draw[c]!='\n'){
            DrawCharacter(f,x+i,y+j,string2Draw[c],font_width,font_height,r,g,b);
        }
        i+=font_width*2/3;
        if(string2Draw[c]=='\n'){
            i = 0;
            j+=font_height;
        }
    }
};

void* memcopy(void* dest,void* src,int size){
    unsigned char* d = (unsigned char*) dest;
    unsigned char* s = (unsigned char*) src;
    while(size--){
        *d++ = *s++;
    }
    return dest;
}

void Flush(){
    VBEInfoBlock* VBE = VBEInfoAddress;
    unsigned short* buffer = (unsigned short*)ScreenBufferAddress;
    memcopy((unsigned short*)VBE->framebuffer,buffer,VBE->height*VBE->width*sizeof(unsigned short));
}

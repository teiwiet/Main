#include "graphics.h"
int start(){
    char str[] = "Turn into something beautiful";
    char* p = str;
    //DrawRect(0,0,50,50,255,0,0);
    while(1){
        ClearScreen(0,255,0);
        DrawCharacter(getArialCharacter,0,0,'A',font_arial_width,font_arial_height,255,0,0);
        DrawString(getArialCharacter,0,font_arial_height,p,font_arial_width,font_arial_height,255,0,0);
        Flush();
    };
    return 0;
}

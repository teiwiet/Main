#include "graphics.h"
#include "keyboard.h"
int start(){

    char text[256];
    int len = 0;

    while(1){

        char c = keyboard_getchar();

        if(c){
            text[len++] = c;
            text[len] = 0;
        }

        ClearScreen(0,255,0);

        DrawString(getArialCharacter,0,0,
                   text,
                   font_arial_width,
                   font_arial_height,
                   255,0,0);

        Flush();
    }

    return 0;
}

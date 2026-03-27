#include "keyboard.h"

static inline unsigned char inb(unsigned short port){
    unsigned char ret;
    __asm__ volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
    return ret;
}

char keymap[128] = {
0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
'a','s','d','f','g','h','j','k','l',';','\'','`',0,
'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' '
};

char keyboard_getchar(){

    unsigned char scancode = inb(0x60);

    if(scancode > 127)
        return 0;

    return keymap[scancode];
}

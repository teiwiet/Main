#include "kernel.h"
void kernel_main(void) {
    volatile char* vga = (volatile char*)0xB8000;

    vga[0] = 'l';
    vga[1] = 0x0F;   // trắng trên nền đen
	
	vga[2] = 'r';
    vga[3] = 0x0F;   // trắng trên nền đen
    for (;;);
}


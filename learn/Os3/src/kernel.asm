[bits 32]
global _start
extern kernel_main

code_seg equ 0x08
data_seg equ 0x10
_start:
	mov ax,data_seg 
	mov ss,ax 
	mov ds,ax 
	mov es,ax 
	mov fs,ax 
	mov gs,ax 

	mov ebp,0x90000 
	mov esp,ebp 
	
	call kernel_main
	jmp $
times 512-($-$$) db 0 

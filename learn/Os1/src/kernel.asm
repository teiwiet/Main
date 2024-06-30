[BITS 32]
section .asm
global _start 
extern kernel_start
data_seg equ 0x08 
code_seg equ 0x10

_start:
	mov ax,data_seg 
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov ebp,0x00200000
	mov esp,ebp
    ; enable a20 line
    in al,0x92 
    or al,2 
    out 0x92,al
    call kernel_start
	jmp $ 

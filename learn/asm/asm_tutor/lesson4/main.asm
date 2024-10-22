[BITS 32]
section .text
global _start
_start:
	mov eax,0xb
	mov ebx,msg
	int 0x80 

	mov al,1 
	xor ebx,ebx 
	int 0x80 
section .data:
msg : db "/bin/sh" 

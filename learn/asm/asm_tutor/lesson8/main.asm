%include "func.asm"

section .data
msg1 db "Hello World",0
msg2 db "My name is teiwiet",0
section .text 
global _start
_start:
	pop ecx 
nextArg:
	cmp ecx,0x0 
	jz noArg
	pop eax 
	call printLF
	dec ecx 
	jmp nextArg
noArg:
	call exit

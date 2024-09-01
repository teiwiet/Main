%include "func.asm"

section .data
msg1 db "Hello World",0 
msg2 db "My name is teiwiet",0 
section .text 
global _start
_start:
	mov eax,msg1
	call printLF 

	mov eax,msg2
	call printLF

	call exit

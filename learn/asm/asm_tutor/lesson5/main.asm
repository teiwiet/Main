%include 'func.asm'

section .data
msg1 db "Hello world!",0xa,0
msg2 db "My name is teiwiet",0xa,0



section .text 
global _start
_start:
	mov eax,msg1 
	call print
	
	mov eax,msg2 
	call print

	call exit

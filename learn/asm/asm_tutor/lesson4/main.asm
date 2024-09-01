section .data
msg db "Hello World",0xa,0

section .text
global _start
_start:
	mov ebx,1
	mov eax,msg 
	push eax
	mov ecx,esp
	mov eax,4 
	mov edx,14
	int 0x80 
exit: ;the exit() func
	mov eax,1 
	mov ebx,0 
	int 0x80 




section .data:
	message db "Hello world",0,0xA
section .text:
	global _start

_start:
	mov eax,4
	mov ebx,1
	mov ecx,message
	mov edx,15
	int 0x80 

	mov ebx,0 
	mov eax,1 
	int 0x80 



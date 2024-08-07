section .data 
message db "Hello World!, my name is Viet",0xA,0

section .text 
global _start

_start:
	mov eax,message 
	mov ebx,eax ;this is some thing else

update:
	cmp byte [eax],0
	jz write_char 
	inc eax 
	jmp update
write_char:
	sub eax,ebx
	mov edx,eax
	mov eax,4
	mov ebx,1
	mov ecx,message
	int 0x80
	mov eax,1
	mov ebx,0
	int 0x80

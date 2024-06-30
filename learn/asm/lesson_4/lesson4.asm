section .data
message db "Hello, brave new world",0xA 

section .text
	global _start

_start:
	mov eax,message
	call strlen
	
	mov edx,eax
	mov ecx,message
	mov ebx,1
	mov eax,4
	int 0x80

exit:
	mov eax,1
	mov ebx,0 
	int 0x80

strlen:
	push ebx 
	mov ebx,eax 

next_char:
	cmp byte [eax],0 
	jz finish
	inc eax 
	jmp next_char

finish:
	sub eax,ebx 
	pop ebx 
	ret


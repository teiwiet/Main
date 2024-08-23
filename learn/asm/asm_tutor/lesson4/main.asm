section .data 
msg db "Hello World",0xa,0

section .text
global start
start:
	mov eax,msg 
	call strlen 

	mov edx,eax 
	mov ecx,msg
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
	cmp byte[eax],0 
	jz finished 
	inc eax 
	jmp next_char 
finished:
	sub eax,ebx 
	pop ebx 
	ret 

print:
	push edx 
	push ecx 
	push ebx 
	push eax 
	call strlen 
	
	mov edx,eax 
	pop eax 
	mov ecx,eax 
	mov ebx,1 
	mov eax,4 
	int 0x80
; void calc str length 
strlen:
	push ebx 
	mov ebx,eax 
update_char:
	cmp byte [eax],0
	jz finish 
	inc eax
	jmp update_char
finish:
	sub eax,ebx 
	pop ebx 
	ret

quit:
	mov eax,1 
	mov ebx,0 
	int 0x80 
	ret

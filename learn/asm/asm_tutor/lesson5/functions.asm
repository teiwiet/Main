; exit() function
exit:
	mov eax,1
	mov ebx,0 
	int 0x80 
	ret 

;strlen(char* msg) 
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

;print(char* msg) 
print:
	push edx 
	push ebx 
	push ecx 
	push eax 
	call strlen

	mov edx,eax 
	pop eax 
	mov ecx,eax 
	mov ebx,1 
	mov eax,4 
	int 0x80 

	pop ecx 
	pop ebx 
	pop edx 
	ret


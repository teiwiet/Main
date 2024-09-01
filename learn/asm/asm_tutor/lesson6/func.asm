;exti() func 
exit:
	mov eax,1
	mov ebx,0 
	int 0x80 
	ret
;print(char* message)
print:
	push edx
	push ecx
	push ebx 
	push eax 
	mov ecx,eax 
	call strlen 
	mov edx,eax 
	mov ebx,1 
	mov eax,4 
	int 0x80 
	pop eax 
	pop ebx 
	pop ecx 
	pop edx 
	ret
printLF:
	call print 
	push eax 
	mov eax,0xa 
	push eax 
	mov eax,esp 
	call print
	pop eax 
	pop eax 
	ret
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

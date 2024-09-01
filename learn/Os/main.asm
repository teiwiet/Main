	mov ah,0xe 
noend:
	mov al,'a'
	int 0x10 
	jmp noend 
times 510-($-$$) db 0 
dw 0xaa55
